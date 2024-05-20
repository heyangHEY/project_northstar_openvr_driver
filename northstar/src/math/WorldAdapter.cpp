#include "math/WorldAdapter.hpp"

using namespace northstar::math::types;

northstar::math::CWorldAdapter::CWorldAdapter(
    std::shared_ptr<IMatrixFactory> pMatrixFactory,
    std::shared_ptr<IVectorFactory> pVectorFactory) {
    m_pMatrixFactory = pMatrixFactory;
    m_pVectorFactory = pVectorFactory;
}

/*
Given a pose return a rotation and scaling matrix
*/
AffineMatrix4d northstar::math::CWorldAdapter::ConversionMatrixFromHMDSpaceToOpenVRWorldSpace(const vr::DriverPose_t& sOVRPose) {
    return AffineMatrix4d::Identity()
        * Translation3d(
            m_pVectorFactory->V3DFromArray({ sOVRPose.vecPosition[0], sOVRPose.vecPosition[1], sOVRPose.vecPosition[2] }))
        * Quaterniond(sOVRPose.qRotation.w, sOVRPose.qRotation.x, sOVRPose.qRotation.y, sOVRPose.qRotation.z);
}

/*
Given A Unity Space Quaternion return a OpenVR Quaternion

Unity is left handed +z out, +y up, +x right
OpenVR is right handed +z in, +y up, +x right

therefore negating x and y rotation is needed
*/
Quaterniond northstar::math::CWorldAdapter::FromUnityQuaternionToOpenVRQuaternion(const Quaterniond& qdUnityRotation) {
    return Quaterniond(qdUnityRotation.w(), -qdUnityRotation.x(), -qdUnityRotation.y(), qdUnityRotation.z());
}

/*
Given A Unity Space Position return a OpenVR Position

Unity is left handed +z out, +y up, +x right
OpenVR is right handed +z in, +y up, +x right

therefore inverting z is needed
*/
Vector3d northstar::math::CWorldAdapter::FromUnityPositionToOpenVRPosition(const Vector3d& v3dUnityPosition) {
    return Vector3d(v3dUnityPosition.x(), v3dUnityPosition.y(), -v3dUnityPosition.z());
}

/*
In unity y is not inverted for clip space
*/
Vector4d northstar::math::CWorldAdapter::FromUnityProjectionExtentsLRTBToOpenVRProjectionExtentsLRTB(const Vector4d& v4dUnityProjectionExtentsLRTB) {
    return Vector4d(v4dUnityProjectionExtentsLRTB.x(), v4dUnityProjectionExtentsLRTB.y(), v4dUnityProjectionExtentsLRTB.w(), v4dUnityProjectionExtentsLRTB.z());
}

/*
Unity is left handed with z forward, Openvr is right handed with z back

Therefore negate z position and invert x / y rotation
*/
AffineMatrix4d northstar::math::CWorldAdapter::FromUnityMatrix4dToOpenVRMatrix4d(const AffineMatrix4d& v4dUnityPose) {
    auto v3dTranslation = v4dUnityPose.translation().array();
    auto qdRotation = Quaterniond(v4dUnityPose.rotation());
    return Translation3d(v3dTranslation.x(), v3dTranslation.y(), -v3dTranslation.z()) 
        * Quaterniond(qdRotation.w(), -qdRotation.x(), -qdRotation.y(), qdRotation.z())
        * AffineMatrix4d::Identity();
}

/*
Unity UV origin is lower Left, OpenVR uses an upper left origin
*/
Vector2d northstar::math::CWorldAdapter::FromOpenGLUVToUnityUV(const Vector2d& v2dOpenGLUV) {
    return Vector2d(v2dOpenGLUV.x(), 1.0 - v2dOpenGLUV.y());
}

/*
Unity UV origin is lower Left, OpenVR uses an upper left origin
*/
Vector2d northstar::math::CWorldAdapter::FromUnityUVToOpenGLUV(const Vector2d& v2dUnityUV) {
    return Vector2d(v2dUnityUV.x(), 1.0 - v2dUnityUV.y());
}
