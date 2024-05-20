#pragma once

#include <openvr_driver.h>

#include "math/Types.hpp"

namespace northstar {
    namespace driver {
        class IOptics {
        public:
            virtual northstar::math::types::Vector4d GetEyeProjectionLRTB(const vr::EVREye& eEye) = 0;
        };
    }
}
