#include "driver/Optics.hpp"

using namespace northstar::math::types;
using namespace northstar::driver::settings::keys;

northstar::driver::COptics::COptics(
    vr::IVRSettings* pVRSettings,
    std::shared_ptr<northstar::math::IWorldAdapter> pWorldAdapter,
    std::shared_ptr<northstar::math::IVectorFactory> pVectorFactory,
    std::shared_ptr<northstar::utility::ILogger> pLogger) {
    m_pVRSettings = pVRSettings;
    m_pWorldAdapter = pWorldAdapter;
    m_pVectorFactory = pVectorFactory;
    m_pLogger = pLogger;

    for (const auto& eEye : { vr::Eye_Left, vr::Eye_Right }) {
        m_umEyeConfigs.insert({ eEye, LoadConfigFromEye(eEye) });
    }
}

northstar::driver::COptics::SEyeConfiguration northstar::driver::COptics::LoadConfigFromEye(const vr::EVREye& eEye) {
    auto sEyeKey = eEye == vr::Eye_Left ? eye::k_svRootLeft : eye::k_svRootRight;
    SEyeConfiguration sEyeConfiguration;

    // "cameraProjection_x": -0.299042533,
    // "cameraProjection_y": 0.304215378,
    // "cameraProjection_w": -0.2455669,
    // "cameraProjection_z": 0.08854639,
    sEyeConfiguration.v4dCameraProjectionFrustumExtentsLRTB =
        m_pWorldAdapter->FromUnityProjectionExtentsLRTBToOpenVRProjectionExtentsLRTB(
            m_pVectorFactory->V4DFromXYZWArray(
                { m_pVRSettings->GetFloat(sEyeKey.data(), eye::k_svCameraProjectionX.data())
                , m_pVRSettings->GetFloat(sEyeKey.data(), eye::k_svCameraProjectionY.data())
                , m_pVRSettings->GetFloat(sEyeKey.data(), eye::k_svCameraProjectionZ.data())
                , m_pVRSettings->GetFloat(sEyeKey.data(), eye::k_svCameraProjectionW.data()) }));

    return sEyeConfiguration;
}

Vector4d northstar::driver::COptics::GetEyeProjectionLRTB(const vr::EVREye& eEye) {
    return m_umEyeConfigs.at(eEye).v4dCameraProjectionFrustumExtentsLRTB;
}
