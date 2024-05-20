#pragma once

#include <openvr_driver.h>

#include "driver/HMD.hpp"
#include "driver/Settings.hpp"
#include "openvr/VRProperties.hpp"
#include "math/WorldAdapter.hpp"
#include "math/MatrixFactory.hpp"
#include "math/VectorFactory.hpp"

namespace northstar {
    namespace driver {
        enum class EHand {
                Left,
                Right
            };
            
        class CServer: public vr::IServerTrackedDeviceProvider
        {
        public:
            CServer() = default;
            virtual vr::EVRInitError Init(vr::IVRDriverContext* pDriverContext);
            virtual void Cleanup() override final;
            virtual const char* const* GetInterfaceVersions() override final;
            virtual void RunFrame() override final;
            virtual bool ShouldBlockStandbyMode() override final;
            virtual void EnterStandby() override final;
            virtual void LeaveStandby() override final;

        private:
            static constexpr std::array<EHand, 2> x_aeHands = { EHand::Left, EHand::Right };
            struct SServerConfiguration{
                northstar::math::types::Vector3d v3dPosition;
                northstar::math::types::Quaterniond qdOrientation;
            };

            void LoadConfiguration();

            SServerConfiguration m_sConfiguration;
            std::shared_ptr<northstar::math::CVectorFactory> m_pVectorFactory;
            std::shared_ptr<northstar::math::CMatrixFactory> m_pMatrixFactory;
            std::shared_ptr<northstar::math::CWorldAdapter> m_pWorldAdapter;
            std::shared_ptr<northstar::utility::CLogger> m_pLogger;
            std::unique_ptr<northstar::driver::CHMD> m_pHMD;
            std::shared_ptr<northstar::openvr::CVRProperties> m_pVRProperties;
        };
    }
}