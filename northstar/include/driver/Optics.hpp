#pragma once

#include "driver/IOptics.hpp"
#include "math/Types.hpp"
#include "math/IVectorFactory.hpp"
#include "math/IMatrixFactory.hpp"
#include "math/IWorldAdapter.hpp"
#include "openvr_driver.h"
#include "driver/Settings.hpp"
#include "utility/ILogger.hpp"

#include <memory>

namespace northstar {
    namespace driver {
        class COptics : public IOptics {
        public:
            COptics(
                vr::IVRSettings* pVRSettings,
                std::shared_ptr<northstar::math::IWorldAdapter> pWorldAdapter,
                std::shared_ptr<northstar::math::IVectorFactory> pVectorFactory,
                std::shared_ptr<northstar::utility::ILogger> pLogger);

            virtual northstar::math::types::Vector4d GetEyeProjectionLRTB(const vr::EVREye& eEye) override final;
        private:
            struct SEyeConfiguration {
                northstar::math::types::Vector4d v4dCameraProjectionFrustumExtentsLRTB;
            };

            SEyeConfiguration LoadConfigFromEye(const vr::EVREye& eEye);

            vr::IVRSettings* m_pVRSettings;
            std::shared_ptr<northstar::math::IVectorFactory> m_pVectorFactory;
            std::shared_ptr<northstar::math::IWorldAdapter> m_pWorldAdapter;
            std::shared_ptr<northstar::utility::ILogger> m_pLogger;
            std::unordered_map<vr::EVREye, SEyeConfiguration> m_umEyeConfigs;
        };
    }
}
