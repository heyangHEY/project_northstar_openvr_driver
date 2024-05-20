#pragma once
// TODO: Quaternion class
#define _USE_MATH_DEFINES
#include <cmath>
#include <Eigen/Geometry>

#include <memory>

#include <LeapC.h>

#include "math/ISkeletalAdapter.hpp"

#include "driver/Settings.hpp"
#include "driver/Types.hpp"
#include "math/IVectorFactory.hpp"
#include "math/IMatrixFactory.hpp"
#include "math/Types.hpp"
#include "utility/ILogger.hpp"
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2

namespace northstar {
    namespace math {
        class CSkeletalAdapter : public ISkeletalAdapter {
        public:
            CSkeletalAdapter(
                std::shared_ptr<IVectorFactory> pVectorFactory, 
                std::shared_ptr<IMatrixFactory> pMatrixFactory,
                std::shared_ptr<northstar::utility::ILogger> pLogger);

            ~CSkeletalAdapter() = default;
            virtual void FromLeapMotionHandToOVRBonePoseArray(
                const vr::DriverPose_t& sPose,
                const types::AffineMatrix4d& m4dFromLeapSensorToHMDRelativeSpace,
                const types::AffineMatrix4d& m4dFromHMDToWorldSpace,
                const LEAP_HAND& sLeapHand, 
                std::array<vr::VRBoneTransform_t, northstar::driver::settings::values::driverConfiguration::k_unBoneCount>& saOpenVRBoneTargets,
                const northstar::driver::types::EHand& eHand) const override final;
        private:
            enum class EBoneType {
                Digit,
                Thumb,
            };

            enum class ESegmentClassification {
                Metacarpal,
                Proximal,
                Intermediate,
                Distal,
                Tip,
                Auxilary,
            };

            void WriteConvertedDigitToTargetOVRBoneIndicies(
                const types::AffineMatrix4d& m4dFromWorldToRootBoneRelativeSpace,
                const types::AffineMatrix4d& m4dFromWorldToWristBoneRelativeSpace,
                const types::AffineMatrix4d& m4dFromLeapSensorToHMDRelativeSpace,
                const types::AffineMatrix4d& m4dFromHMDToWorldSpace,
                const LEAP_DIGIT& sLeapDigit,
                const std::array<northstar::driver::types::EHandeSkeletonBone, 5>& aeDestinationIndicies,
                const northstar::driver::types::EHandeSkeletonBone& eAuxBoneIndex,
                std::array<vr::VRBoneTransform_t, northstar::driver::settings::values::driverConfiguration::k_unBoneCount>& saOpenVRBoneTargets,
                const EBoneType& eBoneType,
                const northstar::driver::types::EHand& eHand) const;

            types::AffineMatrix4d northstar::math::CSkeletalAdapter::ConvertAndWriteBoneToOVRBoneReturningNewWorldToRelativeTransform(
                const types::AffineMatrix4d& m4dFromWorldSpaceToParentRelativeSpace,
                const types::AffineMatrix4d& m4dFromLeapSensorToHMDRelativeSpace,
                const types::AffineMatrix4d& m4dFromHMDToWorldSpace,
                const LEAP_VECTOR& sLeapPosition,
                const LEAP_QUATERNION& sLeapOrientation,
                vr::VRBoneTransform_t& sVRBoneTransform,
                const EBoneType& eBoneType,
                const ESegmentClassification& eSegmentClassification,
                const northstar::driver::types::EHand& eHand) const;

            types::Vector4d GetTranslationSensitiveV4DFromLeapVectorPosition(const LEAP_VECTOR& sPosition) const;
            types::Quaterniond GetQuaterniondFromLeapQuaternionOrientation(const LEAP_QUATERNION& sOrientation) const;
            types::Vector4d ConvertLeapDigitPositionToOpenVRDigitPosition(
                const types::Vector4d& qdLeapDigitPosition, 
                const types::Quaterniond& qdLeapDigitOrientation, 
                const EBoneType& eBoneType,
                const ESegmentClassification& eSegmentClassification,
                const northstar::driver::types::EHand& eHand) const;

            types::Quaterniond ConvertLeapDigitOrientationToOpenVRDigitOrientation(
                const types::Quaterniond& qdLeapDigitOrientation, 
                const EBoneType& eBoneType,
                const ESegmentClassification& eSegmentClassification,
                const northstar::driver::types::EHand& eHand) const;

            void WritePositionAndOrientationIntoVRBonePose(vr::VRBoneTransform_t& sVRBoneTransform, const types::Vector4d& v4dPosition, const types::Quaterniond& qdOrientation) const;

            std::shared_ptr<IVectorFactory> m_pVectorFactory;
            std::shared_ptr<IMatrixFactory> m_pMatrixFactory;
            std::shared_ptr<utility::ILogger> m_pLogger;
        };
    }
}