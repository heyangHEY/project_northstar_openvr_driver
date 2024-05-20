#pragma once

#include <string_view>

namespace northstar {
    namespace driver {
        namespace settings {
            namespace keys {
                namespace debug {
                    static constexpr std::string_view k_svRoot = "debug";

                    /* from Controller */
                    static constexpr std::string_view k_svUseDebugTrackerConfig = "useDebugTrackerConfig";
                    static constexpr std::string_view k_svUseDebugBasePose = "useDebugBasePose";

                    /* from HMD */
                    static constexpr std::string_view k_svUseFakeScreenConfig = "useFakeScreenConfig";
                    static constexpr std::string_view k_svUseFakeProjection = "useFakeProjection";
                }

                namespace configuration {
                    static constexpr std::string_view k_svRoot = "configuration";

                    /* from Server */
                    static constexpr std::string_view k_svEnableDirectMode = "enableDirectMode"; // hey
                }

                namespace display {
                    static constexpr std::string_view k_svRoot = "display";
                    static constexpr std::string_view k_svOriginX = "originX";
                    static constexpr std::string_view k_svOriginY = "originY";
                    static constexpr std::string_view k_svWidth = "width";
                    static constexpr std::string_view k_svHeight = "height";
                    static constexpr std::string_view k_svRenderWidth = "renderWidth";
                    static constexpr std::string_view k_svRenderHeight = "renderHeight";
                    static constexpr std::string_view k_svFrequency = "frequency";
                    static constexpr std::string_view k_svIPD = "ipd";
                    static constexpr std::string_view k_svPhotonLatency = "photonLatency";
                }

                namespace eye {
                    static constexpr std::string_view k_svRootLeft = "leftEye";
                    static constexpr std::string_view k_svRootRight = "rightEye";

                    static constexpr std::string_view k_svEyeToHead_00 = "eyeToHead_e00"; // hey
                    static constexpr std::string_view k_svEyeToHead_01 = "eyeToHead_e01"; // hey
                    static constexpr std::string_view k_svEyeToHead_02 = "eyeToHead_e02"; // hey
                    static constexpr std::string_view k_svEyeToHead_03 = "eyeToHead_e03"; // hey
                    static constexpr std::string_view k_svEyeToHead_04 = "eyeToHead_e04"; // hey
                    static constexpr std::string_view k_svEyeToHead_05 = "eyeToHead_e05"; // hey
                    static constexpr std::string_view k_svEyeToHead_06 = "eyeToHead_e06"; // hey
                    static constexpr std::string_view k_svEyeToHead_07 = "eyeToHead_e07"; // hey
                    static constexpr std::string_view k_svEyeToHead_08 = "eyeToHead_e08"; // hey
                    static constexpr std::string_view k_svEyeToHead_09 = "eyeToHead_e09"; // hey
                    static constexpr std::string_view k_svEyeToHead_10 = "eyeToHead_e10"; // hey
                    static constexpr std::string_view k_svEyeToHead_11 = "eyeToHead_e11"; // hey

                    static constexpr std::string_view k_svCameraProjectionX = "cameraProjection_x";
                    static constexpr std::string_view k_svCameraProjectionY = "cameraProjection_y";
                    static constexpr std::string_view k_svCameraProjectionZ = "cameraProjection_z";
                    static constexpr std::string_view k_svCameraProjectionW = "cameraProjection_w";
                }
            }

            namespace values {
                namespace driverConfiguration {
                    static constexpr uint64_t k_uiCurrentUniverseID = 2;
                    static constexpr int32_t k_unBoneCount = 31;
                }
            }
        }
    }
}