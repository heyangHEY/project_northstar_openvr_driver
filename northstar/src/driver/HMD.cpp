#include "driver/HMD.hpp"
#include <iostream>

using namespace northstar::driver::settings::keys;
using namespace northstar::driver::settings::values;

northstar::driver::CHMD::CHMD(
    vr::IVRSettings* pVRSettings, 
    vr::IVRServerDriverHost* pVRServerDriverHost,
    std::shared_ptr<northstar::openvr::IVRProperties> pVRProperties,
    std::shared_ptr<northstar::math::IVectorFactory> pVectorFactory,
    std::shared_ptr<northstar::utility::ILogger> pLogger) {
    m_pVRSettings = pVRSettings;
    m_pVRServerDriverHost = pVRServerDriverHost;
    m_pVRProperties = pVRProperties;
    m_pLogger = pLogger;
    m_pVectorFactory = pVectorFactory;
    m_sOpenVRState.unObjectId = vr::k_unTrackedDeviceIndexInvalid;
    m_sOpenVRState.ulPropertyContainer = vr::k_ulInvalidPropertyContainer;
    m_bFlag = false; // hey

    LoadConfiguration();
}

void northstar::driver::CHMD::LoadConfiguration() {
    // TODO: use vector factory
    m_sConfiguration.bUseFakeScreenConfig = m_pVRSettings->GetBool(debug::k_svRoot.data(), debug::k_svUseFakeScreenConfig.data());
    m_sConfiguration.bUseFakeProjection = m_pVRSettings->GetBool(debug::k_svRoot.data(), debug::k_svUseFakeProjection.data());
    m_sConfiguration.dIPD = m_pVRSettings->GetFloat(display::k_svRoot.data(), display::k_svIPD.data());
    m_sConfiguration.sDisplayConfiguration.dFrequency = m_pVRSettings->GetFloat(display::k_svRoot.data(), display::k_svFrequency.data());
    m_sConfiguration.sDisplayConfiguration.dPhotonLatency = m_pVRSettings->GetFloat(display::k_svRoot.data(), display::k_svPhotonLatency.data());
    m_bDirectModeEnabled = m_pVRSettings->GetBool(configuration::k_svRoot.data(), configuration::k_svEnableDirectMode.data()); // hey
    if (m_sConfiguration.bUseFakeScreenConfig) {
        //TODO: Put these in constants
        m_sConfiguration.sDisplayConfiguration.v2iWindowOrigin << 100, 100;
        m_sConfiguration.sDisplayConfiguration.v2iWindowDimensions << 1000, 1000;
        m_sConfiguration.sDisplayConfiguration.v2iEyeRenderAreaDimensions << 1000, 1000;
    } else {
        m_sConfiguration.sDisplayConfiguration.v2iWindowOrigin <<
            m_pVRSettings->GetInt32(display::k_svRoot.data(), display::k_svOriginX.data()),
            m_pVRSettings->GetInt32(display::k_svRoot.data(), display::k_svOriginY.data());

        m_sConfiguration.sDisplayConfiguration.v2iWindowDimensions <<
            m_pVRSettings->GetInt32(display::k_svRoot.data(), display::k_svWidth.data()),
            m_pVRSettings->GetInt32(display::k_svRoot.data(), display::k_svHeight.data());

        m_sConfiguration.sDisplayConfiguration.v2iEyeRenderAreaDimensions <<
            m_pVRSettings->GetInt32(display::k_svRoot.data(), display::k_svRenderWidth.data()),
            m_pVRSettings->GetInt32(display::k_svRoot.data(), display::k_svRenderHeight.data());
    }

    m_sConfiguration.mEyeToHeadLeft = LoadEyeToHeadTransformFromSettings(vr::Eye_Left); // hey
    m_sConfiguration.mEyeToHeadRight = LoadEyeToHeadTransformFromSettings(vr::Eye_Right); // hey

    m_sConfiguration.v4dCameraProjectionFrustumExtentsLRTBLeft =
        m_pVectorFactory->V4DFromXYZWArray(
            { m_pVRSettings->GetFloat(eye::k_svRootLeft.data(), eye::k_svCameraProjectionX.data())
            , m_pVRSettings->GetFloat(eye::k_svRootLeft.data(), eye::k_svCameraProjectionY.data())
            , m_pVRSettings->GetFloat(eye::k_svRootLeft.data(), eye::k_svCameraProjectionW.data())
            , m_pVRSettings->GetFloat(eye::k_svRootLeft.data(), eye::k_svCameraProjectionZ.data()) }); // 注意调换了w和z的位置

    m_sConfiguration.v4dCameraProjectionFrustumExtentsLRTBRight =
        m_pVectorFactory->V4DFromXYZWArray(
            { m_pVRSettings->GetFloat(eye::k_svRootRight.data(), eye::k_svCameraProjectionX.data())
            , m_pVRSettings->GetFloat(eye::k_svRootRight.data(), eye::k_svCameraProjectionY.data())
            , m_pVRSettings->GetFloat(eye::k_svRootRight.data(), eye::k_svCameraProjectionW.data())
            , m_pVRSettings->GetFloat(eye::k_svRootRight.data(), eye::k_svCameraProjectionZ.data()) });

    SetOpenVRConfiguration();
}

void northstar::driver::CHMD::SetOpenVRConfiguration() {
    m_pVRSettings->SetFloat(vr::k_pch_SteamVR_Section, vr::k_pch_SteamVR_IPD_Float, static_cast<float>(m_sConfiguration.dIPD));
}

vr::EVRInitError northstar::driver::CHMD::Activate(vr::TrackedDeviceIndex_t unObjectId) {
    m_sOpenVRState.unObjectId = unObjectId;
    m_sOpenVRState.ulPropertyContainer = m_pVRProperties->TrackedDeviceToPropertyContainer(unObjectId);
    SetOpenVRProperties();
    return vr::VRInitError_None;
}

void northstar::driver::CHMD::SetOpenVRProperties() {
    if (m_sConfiguration.bUseFakeScreenConfig)
        m_pVRProperties->SetBoolProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_IsOnDesktop_Bool, false);

    m_pVRProperties->SetStringProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_SerialNumber_String, "1024" );
    m_pVRProperties->SetStringProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_ModelNumber_String, "0" );
    m_pVRProperties->SetStringProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_RenderModelName_String, "0" );
    m_pVRProperties->SetFloatProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_UserIpdMeters_Float, static_cast<float>(m_sConfiguration.dIPD));
    // m_pVRProperties->SetBoolProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_HasDriverDirectModeComponent_Bool, x_bDirectModeEnabled); // hey
    m_pVRProperties->SetBoolProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_HasDriverDirectModeComponent_Bool, m_bDirectModeEnabled); // hey
    m_pVRProperties->SetFloatProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_DisplayFrequency_Float, static_cast<float>(m_sConfiguration.sDisplayConfiguration.dFrequency));
    m_pVRProperties->SetFloatProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_SecondsFromVsyncToPhotons_Float, static_cast<float>(m_sConfiguration.sDisplayConfiguration.dPhotonLatency));
    m_pVRProperties->SetFloatProperty(m_sOpenVRState.ulPropertyContainer, vr::Prop_UserHeadToEyeDepthMeters_Float, static_cast<float>(x_fUserHeadToEyeDepthInMeters));
    m_pVRProperties->SetUint64Property(m_sOpenVRState.ulPropertyContainer, vr::Prop_CurrentUniverseId_Uint64, driverConfiguration::k_uiCurrentUniverseID );
}

void northstar::driver::CHMD::Deactivate() { 
    m_sOpenVRState.unObjectId = vr::k_unTrackedDeviceIndexInvalid; 
}

void northstar::driver::CHMD::EnterStandby() {}

void* northstar::driver::CHMD::GetComponent( const char* pchComponentNameAndVersion )
{
    if (!_stricmp(pchComponentNameAndVersion, vr::IVRDisplayComponent_Version))
        return static_cast<vr::IVRDisplayComponent*>(this);

    return nullptr;
}

bool northstar::driver::CHMD::IsDisplayOnDesktop() { 
    return x_bIsDisplayOnDesktop;
}

bool northstar::driver::CHMD::IsDisplayRealDisplay() { 
    if (m_sConfiguration.bUseFakeScreenConfig)
        return false;

    return x_bIsDisplayRealDisplay; 
}


// TODO: clean up sensor driver interaction
vr::DriverPose_t northstar::driver::CHMD::GetPose() {
    vr::DriverPose_t sFakePose = { 0 };
    sFakePose.poseIsValid = true;
    sFakePose.deviceIsConnected = true;
    sFakePose.result = vr::TrackingResult_Running_OK;
    sFakePose.qRotation = { 1, 0, 0, 0 };
    sFakePose.qWorldFromDriverRotation = { 1, 0, 0, 0 };
    sFakePose.qDriverFromHeadRotation = { 1, 0, 0, 0 };
    return sFakePose;
}

void northstar::driver::CHMD::GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) {
    *pnX = m_sConfiguration.sDisplayConfiguration.v2iWindowOrigin.x();
    *pnY = m_sConfiguration.sDisplayConfiguration.v2iWindowOrigin.y();
    *pnWidth = m_sConfiguration.sDisplayConfiguration.v2iWindowDimensions.x();
    *pnHeight = m_sConfiguration.sDisplayConfiguration.v2iWindowDimensions.y();
}

void northstar::driver::CHMD::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) {
    *pnWidth = m_sConfiguration.sDisplayConfiguration.v2iEyeRenderAreaDimensions.x();
    *pnHeight = m_sConfiguration.sDisplayConfiguration.v2iEyeRenderAreaDimensions.y();
}

void northstar::driver::CHMD::GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) {
    *pnY = 0;
    *pnWidth = m_sConfiguration.sDisplayConfiguration.v2iWindowDimensions.x() / 2;
    *pnHeight = m_sConfiguration.sDisplayConfiguration.v2iWindowDimensions.y();
    if (eEye == vr::Eye_Left)
        *pnX = 0;
    else
        *pnX = m_sConfiguration.sDisplayConfiguration.v2iWindowDimensions.x() / 2;
}

void northstar::driver::CHMD::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) {
    if (m_sConfiguration.bUseFakeProjection) {
        *pfLeft = -1.0;
        *pfRight = 1.0;
        *pfTop = -1.0;
        *pfBottom = 1.0;
        return;
    }

    // "cameraProjection_x": -0.299042533,
    // "cameraProjection_y": 0.304215378,
    // "cameraProjection_w": -0.2455669,
    // "cameraProjection_z": 0.08854639,

    // "cameraProjection_x": -0.261943438,
    // "cameraProjection_y": 0.352588622,
    // "cameraProjection_w": -0.240336522,
    // "cameraProjection_z": 0.0948431145,

    auto v4dEyeProjectionLRTB = eEye == vr::Eye_Left ? 
        m_sConfiguration.v4dCameraProjectionFrustumExtentsLRTBLeft :  m_sConfiguration.v4dCameraProjectionFrustumExtentsLRTBRight;

    *pfLeft = static_cast<float>(v4dEyeProjectionLRTB.x());
    *pfRight = static_cast<float>(v4dEyeProjectionLRTB.y());
    *pfTop = static_cast<float>(v4dEyeProjectionLRTB.z());
    *pfBottom = static_cast<float>(v4dEyeProjectionLRTB.w());	
}

vr::DistortionCoordinates_t northstar::driver::CHMD::ComputeDistortion(vr::EVREye eEye, float fU, float fV) {
    vr::DistortionCoordinates_t coordinates;
    coordinates.rfRed[0] = fU;
    coordinates.rfRed[1] = fV;
    coordinates.rfGreen[0] = fU;
    coordinates.rfGreen[1] = fV;
    coordinates.rfBlue[0] = fU;
    coordinates.rfBlue[1] = fV;
    return coordinates;
}

void northstar::driver::CHMD::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) {
    if(unResponseBufferSize >= 1)
        pchResponseBuffer[0] = 0;
}

// TODO: this should go in a thread
void northstar::driver::CHMD::RunFrame() {
    if (m_sOpenVRState.unObjectId != vr::k_unTrackedDeviceIndexInvalid) {
        m_pVRServerDriverHost->TrackedDevicePoseUpdated(m_sOpenVRState.unObjectId, GetPose(), sizeof(vr::DriverPose_t));

        // hey
        if (!m_bFlag) {
            m_bFlag = true;
            m_pVRServerDriverHost->SetDisplayEyeToHead(
                m_sOpenVRState.unObjectId, 
                m_sConfiguration.mEyeToHeadLeft, 
                m_sConfiguration.mEyeToHeadRight);
        }
    }
}

// hey
vr::HmdMatrix34_t northstar::driver::CHMD::LoadEyeToHeadTransformFromSettings( vr::EVREye eEye ) {
    auto sEyeKey = eEye == vr::Eye_Left ? eye::k_svRootLeft : eye::k_svRootRight;
    vr::HmdMatrix34_t hmd = { 0 };
    hmd.m[0][0] = m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_00.data() );
    hmd.m[0][1] = m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_01.data() );
    hmd.m[0][2] = -m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_02.data() );
    hmd.m[0][3] = m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_03.data() );
    hmd.m[1][0] = m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_04.data() );
    hmd.m[1][1] = m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_05.data() );
    hmd.m[1][2] = -m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_06.data() );
    hmd.m[1][3] = m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_07.data() );
    hmd.m[2][0] = -m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_08.data() );
    hmd.m[2][1] = -m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_09.data() );
    hmd.m[2][2] = m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_10.data() );
    hmd.m[2][3] = -m_pVRSettings->GetFloat( sEyeKey.data(), eye::k_svEyeToHead_11.data() );

    return hmd;
}
