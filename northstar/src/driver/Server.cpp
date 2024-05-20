#include "driver/Server.hpp"

using namespace northstar::driver::settings::keys;

vr::EVRInitError northstar::driver::CServer::Init(vr::IVRDriverContext* pDriverContext) {
    VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
    LoadConfiguration();
    m_pLogger = std::make_shared<northstar::utility::CLogger>(vr::VRDriverLog());
    m_pVRProperties = std::make_shared<northstar::openvr::CVRProperties>(vr::VRProperties());
    m_pVectorFactory = std::make_shared<northstar::math::CVectorFactory>();

    m_pHMD = std::make_unique<northstar::driver::CHMD>(
        vr::VRSettings(),
        vr::VRServerDriverHost(),
        m_pVRProperties,
        m_pVectorFactory,
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
    m_pVectorFactory = nullptr;
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