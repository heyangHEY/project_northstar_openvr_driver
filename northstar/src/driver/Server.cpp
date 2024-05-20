#include "driver/Server.hpp"

using namespace northstar::driver::settings::keys;

vr::EVRInitError northstar::driver::CServer::Init(vr::IVRDriverContext* pDriverContext) {
    VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
    LoadConfiguration();
    m_pLogger = std::make_shared<northstar::utility::CLogger>(vr::VRDriverLog());
    m_pVRProperties = std::make_shared<northstar::openvr::CVRProperties>(vr::VRProperties());
    m_pHostProber = std::make_shared<northstar::utility::CHostProber>();
    m_pMatrixFactory = std::make_shared<northstar::math::CMatrixFactory>();
    m_pVectorFactory = std::make_shared<northstar::math::CVectorFactory>();
    m_pTimeProvider = std::make_shared<northstar::utility::CTimeProvider>();
    m_pSpaceAdapter = std::make_shared<northstar::math::CSpaceAdapter>(m_pVectorFactory);
    m_pGeometry = std::make_shared <northstar::math::CGeometry>(m_pVectorFactory);
    m_pWorldAdapter = std::make_shared<northstar::math::CWorldAdapter>(
        m_pMatrixFactory,
        m_pVectorFactory);

    m_pOptics = std::make_shared<northstar::driver::COptics>(
        vr::VRSettings(),
        m_pWorldAdapter,
        m_pSpaceAdapter,
        m_pGeometry,
        m_pMatrixFactory,
        m_pVectorFactory,
        m_pLogger);

    m_pHMD = std::make_unique<northstar::driver::CHMD>(
        vr::VRSettings(),
        vr::VRServerDriverHost(),
        m_pHostProber,
        m_pVRProperties,
        m_pVectorFactory,
        m_pOptics,
        m_pLogger);

    vr::VRServerDriverHost()->TrackedDeviceAdded(
        "1024", // m_pHMD->GetSerialNumber().data(),
        vr::TrackedDeviceClass_HMD,
        m_pHMD.get());

    return vr::EVRInitError::VRInitError_None;
}

void northstar::driver::CServer::LoadConfiguration() {
    auto pVRSettings = vr::VRSettings();
}

void northstar::driver::CServer::Cleanup() {
    m_pLogger = nullptr;
    m_pVRProperties = nullptr;
    m_pHostProber = nullptr;
    m_pMatrixFactory = nullptr;
    m_pVectorFactory = nullptr;
    m_pTimeProvider = nullptr;
    m_pSpaceAdapter = nullptr;
    m_pGeometry = nullptr;
    m_pWorldAdapter = nullptr;
    m_pOptics = nullptr;
    m_pHMD = nullptr;
}

const char* const* northstar::driver::CServer::GetInterfaceVersions() { 
    return vr::k_InterfaceVersions;
}

void northstar::driver::CServer::RunFrame() {
    if (m_pHMD)
        m_pHMD->RunFrame();

    static vr::VREvent_t vrEvent;
    while (vr::VRServerDriverHost()->PollNextEvent(&vrEvent, sizeof(vrEvent))) {}
}

bool northstar::driver::CServer::ShouldBlockStandbyMode() { 
    return true;  // true
}

void northstar::driver::CServer::EnterStandby() {}

void northstar::driver::CServer::LeaveStandby() {}