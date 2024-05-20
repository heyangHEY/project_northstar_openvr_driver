#include <openvr_driver.h>
#include <string>
#include <string_view>

#include "driver/Settings.hpp"
#include "openvr/IVRProperties.hpp"
#include "utility/Logger.hpp"
#include "math/IVectorFactory.hpp"
#include "math/Types.hpp"


namespace northstar {
    namespace driver {
        class CHMD : public vr::ITrackedDeviceServerDriver, public vr::IVRDisplayComponent
        {
        public:
            CHMD(vr::IVRSettings* pVRSettings,
                vr::IVRServerDriverHost* pVRServerDriverHost,
                std::shared_ptr<northstar::openvr::IVRProperties> pVRProperties,
                std::shared_ptr<northstar::math::IVectorFactory> pVectorFactory,
                std::shared_ptr<northstar::utility::ILogger> pLogger);

            // 继承自 vr::ITrackedDeviceServerDriver，见openvr_driver.h
            virtual vr::EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId) override final;
            virtual void Deactivate() override final;
            virtual void EnterStandby() override final;
            virtual void* GetComponent(const char* pchComponentNameAndVersion) override final;
            virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override final;

            // 继承自 vr::IVRDisplayComponent，见openvr_driver.h
            virtual bool IsDisplayOnDesktop() override final;
            virtual bool IsDisplayRealDisplay() override final;
            virtual vr::DriverPose_t GetPose() override final;
            virtual void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override final;
            virtual void GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight) override final;
            virtual void GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override final;
            virtual void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override final;
            virtual vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV) override final;

            void RunFrame();
            vr::HmdMatrix34_t LoadEyeToHeadTransformFromSettings(vr::EVREye eEye); // hey

        private:
            static constexpr int32_t x_iFallbackWindowOriginX = 0;
            static constexpr float x_fUserHeadToEyeDepthInMeters = 0.0f; // TODO: validate this
            // static constexpr bool x_bDirectModeEnabled = false; // hey

            static constexpr bool x_bIsDisplayOnDesktop = true;
            static constexpr bool x_bIsDisplayRealDisplay = true;

            struct SDisplayConfiguration {
                northstar::math::types::Vector2i v2iWindowOrigin;
                northstar::math::types::Vector2i v2iWindowDimensions;
                northstar::math::types::Vector2i v2iEyeRenderAreaDimensions;
                double dFrequency;
                double dPhotonLatency;
            };

            struct SConfiguration{
                SDisplayConfiguration sDisplayConfiguration;
                bool bUseFakeScreenConfig;
                bool bUseFakeProjection;
                double dIPD;
                vr::HmdMatrix34_t mEyeToHeadLeft; // hey
                vr::HmdMatrix34_t mEyeToHeadRight; // hey
                northstar::math::types::Vector4d v4dCameraProjectionFrustumExtentsLRTBLeft;
                northstar::math::types::Vector4d v4dCameraProjectionFrustumExtentsLRTBRight;
            };

            struct SOpenVRState {
                vr::TrackedDeviceIndex_t unObjectId;
                vr::PropertyContainerHandle_t ulPropertyContainer;
            };

            void LoadConfiguration();
            void SetOpenVRConfiguration();
            void SetOpenVRProperties();

            SConfiguration m_sConfiguration;
            SOpenVRState m_sOpenVRState;
            bool m_bDirectModeEnabled; // hey
            bool m_bFlag; // hey

            std::shared_ptr<northstar::math::IVectorFactory> m_pVectorFactory;
            std::shared_ptr<northstar::utility::ILogger> m_pLogger;
            std::shared_ptr<northstar::openvr::IVRProperties> m_pVRProperties;
            vr::IVRSettings* m_pVRSettings;
            vr::IVRServerDriverHost* m_pVRServerDriverHost;
        };
    }
}