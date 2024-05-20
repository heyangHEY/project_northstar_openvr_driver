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
                    static constexpr std::string_view k_svUseFakeWarp = "useFakeWarp";

                    /* from Server */
                    static constexpr std::string_view k_svShouldBlockStandbyMode = "shouldBlockStandbyMode";
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

                    static constexpr std::string_view k_svEllipseMinorAxis = "ellipseMinorAxis";
                    static constexpr std::string_view k_svEllipseMajorAxis = "ellipseMajorAxis";

                    static constexpr std::string_view k_svScreenForwardX = "screenForward_x";
                    static constexpr std::string_view k_svScreenForwardY = "screenForward_y";
                    static constexpr std::string_view k_svScreenForwardZ = "screenForward_z";

                    static constexpr std::string_view k_svScreenPositionX = "screenPosition_x";
                    static constexpr std::string_view k_svScreenPositionY = "screenPosition_y";
                    static constexpr std::string_view k_svScreenPositionZ = "screenPosition_z";

                    static constexpr std::string_view k_svEyePositionX = "eyePosition_x";
                    static constexpr std::string_view k_svEyePositionY = "eyePosition_y";
                    static constexpr std::string_view k_svEyePositionZ = "eyePosition_z";

                    static constexpr std::string_view k_svEyeRotationX = "eyeRotation_x";
                    static constexpr std::string_view k_svEyeRotationY = "eyeRotation_y";
                    static constexpr std::string_view k_svEyeRotationZ = "eyeRotation_z";
                    static constexpr std::string_view k_svEyeRotationW = "eyeRotation_w";

                    static constexpr std::string_view k_svCameraProjectionX = "cameraProjection_x";
                    static constexpr std::string_view k_svCameraProjectionY = "cameraProjection_y";
                    static constexpr std::string_view k_svCameraProjectionZ = "cameraProjection_z";
                    static constexpr std::string_view k_svCameraProjectionW = "cameraProjection_w";

                    static constexpr std::string_view k_svSphereToWorldSpace_00 = "sphereToWorldSpace_e00";
                    static constexpr std::string_view k_svSphereToWorldSpace_01 = "sphereToWorldSpace_e01";
                    static constexpr std::string_view k_svSphereToWorldSpace_02 = "sphereToWorldSpace_e02";
                    static constexpr std::string_view k_svSphereToWorldSpace_03 = "sphereToWorldSpace_e03";
                    static constexpr std::string_view k_svSphereToWorldSpace_10 = "sphereToWorldSpace_e10";
                    static constexpr std::string_view k_svSphereToWorldSpace_11 = "sphereToWorldSpace_e11";
                    static constexpr std::string_view k_svSphereToWorldSpace_12 = "sphereToWorldSpace_e12";
                    static constexpr std::string_view k_svSphereToWorldSpace_13 = "sphereToWorldSpace_e13";
                    static constexpr std::string_view k_svSphereToWorldSpace_20 = "sphereToWorldSpace_e20";
                    static constexpr std::string_view k_svSphereToWorldSpace_21 = "sphereToWorldSpace_e21";
                    static constexpr std::string_view k_svSphereToWorldSpace_22 = "sphereToWorldSpace_e22";
                    static constexpr std::string_view k_svSphereToWorldSpace_23 = "sphereToWorldSpace_e23";

                    static constexpr std::string_view k_svWorldToScreenSpace_00 = "worldToScreenSpace_e00";
                    static constexpr std::string_view k_svWorldToScreenSpace_01 = "worldToScreenSpace_e01";
                    static constexpr std::string_view k_svWorldToScreenSpace_02 = "worldToScreenSpace_e02";
                    static constexpr std::string_view k_svWorldToScreenSpace_03 = "worldToScreenSpace_e03";
                    static constexpr std::string_view k_svWorldToScreenSpace_10 = "worldToScreenSpace_e10";
                    static constexpr std::string_view k_svWorldToScreenSpace_11 = "worldToScreenSpace_e11";
                    static constexpr std::string_view k_svWorldToScreenSpace_12 = "worldToScreenSpace_e12";
                    static constexpr std::string_view k_svWorldToScreenSpace_13 = "worldToScreenSpace_e13";
                    static constexpr std::string_view k_svWorldToScreenSpace_20 = "worldToScreenSpace_e20";
                    static constexpr std::string_view k_svWorldToScreenSpace_21 = "worldToScreenSpace_e21";
                    static constexpr std::string_view k_svWorldToScreenSpace_22 = "worldToScreenSpace_e22";
                    static constexpr std::string_view k_svWorldToScreenSpace_23 = "worldToScreenSpace_e23";
                }

                namespace leapMotion {
                    static constexpr std::string_view k_svRoot = "leapTrackerOdometryOrigin";
                    static constexpr std::string_view k_svPositionX = "position_x";
                    static constexpr std::string_view k_svPositionY = "position_y";
                    static constexpr std::string_view k_svPositionZ = "position_z";
                    static constexpr std::string_view k_svRotationX = "rotation_x";
                    static constexpr std::string_view k_svRotationY = "rotation_y";
                    static constexpr std::string_view k_svRotationZ = "rotation_z";
                    static constexpr std::string_view k_svRotationW = "rotation_w";
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