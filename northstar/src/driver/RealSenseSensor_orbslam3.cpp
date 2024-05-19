#include "driver/RealSenseSensor.hpp"

northstar::driver::CRealSenseSensor::CRealSenseSensor(
    std::shared_ptr<northstar::utility::ITimeProvider> pTimeProvider,
    std::shared_ptr<northstar::utility::CLogger> pLogger)
{
    m_pTimeProvider = pTimeProvider;
    m_pLogger = pLogger;
    m_bSessionStartSuccessful = true;
	StartPollingDriverServerOnBackgroundThread();
}

void northstar::driver::CRealSenseSensor::StartPollingDriverServerOnBackgroundThread()
{
    m_PollingThread = std::thread([this] { PollingUpdateLoop(); });
}

northstar::driver::CRealSenseSensor::~CRealSenseSensor()
{
    m_bPollingShouldStop = true;
    if (m_PollingThread.joinable())
        m_PollingThread.join();
}

// TODO: Atomics aren't helping here clean this up
bool northstar::driver::CRealSenseSensor::GetPose(
    vr::DriverPose_t& pose, 
    EPoseRetrievalError& error) {
    const rs2_pose rsPose = m_LastPoseRecieved;
    const double rsPoseTimeStamp = m_LastPoseRecievedTimeStamp;
    ConvertRealSensePoseToOpenVRPose(rsPose, rsPoseTimeStamp, pose);
    if (!SessionStartWasSuccessful()) {
        error = EPoseRetrievalError::SessionStartFailed;
        return false;
    } else if (!m_Status.bDriverSessionIsRunning) {
        error = EPoseRetrievalError::SessionNotRunning;
        return false;
    }

    return true;
}

// TODO: Time offset, this is causing significant rendering chop
void northstar::driver::CRealSenseSensor::ConvertRealSensePoseToOpenVRPose(const rs2_pose& rsPose, const double& rsPoseTimeStamp, vr::DriverPose_t& ovrPose) {
    ovrPose.willDriftInYaw = false;
    ovrPose.shouldApplyHeadModel = false;

    ovrPose.qWorldFromDriverRotation = vr::HmdQuaternion_t{ 1, 0, 0, 0 };
    ovrPose.vecWorldFromDriverTranslation[0] = 0;
    ovrPose.vecWorldFromDriverTranslation[1] = 0;
    ovrPose.vecWorldFromDriverTranslation[2] = 0;

    // TODO: measure distance / orientation from head to structure sensors rotation
    ovrPose.qDriverFromHeadRotation = vr::HmdQuaternion_t{ 1, 0, 0, 0 };
    ovrPose.vecDriverFromHeadTranslation[0] = 0;
    ovrPose.vecDriverFromHeadTranslation[1] = 0;
    ovrPose.vecDriverFromHeadTranslation[2] = 0;

    ovrPose.qRotation.w = rsPose.rotation.w;
    ovrPose.qRotation.x = rsPose.rotation.x;
    ovrPose.qRotation.y = rsPose.rotation.y;
    ovrPose.qRotation.z = rsPose.rotation.z;

    CopyRealSenseSensorVectorIntoDriverPose(rsPose.translation, ovrPose.vecPosition);

    // TODO: These are choppy
    CopyRealSenseSensorVectorIntoDriverPose(/*rsPose.velocity*/{ 0, 0, 0 }, ovrPose.vecVelocity);
    CopyRealSenseSensorVectorIntoDriverPose(/*rsPose.acceleration*/{ 0, 0, 0 }, ovrPose.vecAcceleration);
    CopyRealSenseSensorVectorIntoDriverPose(/*rsPose.angular_velocity*/{ 0, 0, 0 }, ovrPose.vecAngularVelocity);
    CopyRealSenseSensorVectorIntoDriverPose(/*rsPose.angular_acceleration*/{ 0, 0, 0 }, ovrPose.vecAngularAcceleration);

    ovrPose.poseTimeOffset = m_pTimeProvider->CurrentUnixTimestamp() - rsPoseTimeStamp;
}

void northstar::driver::CRealSenseSensor::CopyRealSenseSensorVectorIntoDriverPose(const rs2_vector& rsVector, double* pdDriverPoseVec) const {
    pdDriverPoseVec[0] = rsVector.x;
    pdDriverPoseVec[1] = rsVector.y;
    pdDriverPoseVec[2] = rsVector.z;
}

bool northstar::driver::CRealSenseSensor::SessionStartWasSuccessful() {
    return m_bSessionStartSuccessful;
}

// TODO: Driver start success etc
void northstar::driver::CRealSenseSensor::PollingUpdateLoop() 
{
    try {
        rs2::pipeline rsPipeLine;
        rs2::config rsConfig;
        rsConfig.enable_stream(RS2_STREAM_FISHEYE, 1, RS2_FORMAT_Y8);
        rsConfig.enable_stream(RS2_STREAM_FISHEYE, 2, RS2_FORMAT_Y8);
        rsPipeLine.start(rsConfig);

        std::string vocabulary_file_dir = "D:/HEY/XR/HeyAR_LLAPI/Vocabulary/ORBvoc.bin";
        std::string setting_file_dir = "D:/HEY/XR/HeyAR_LLAPI/RealSense_T265.yaml";
        ORB_SLAM3::System SLAM(vocabulary_file_dir,setting_file_dir,ORB_SLAM3::System::STEREO, false);

        cv::Mat im_left, im_right;
        int width_img = 848, height_img = 800;

        while (!m_bPollingShouldStop)
        {
            auto sFrameSet = rsPipeLine.wait_for_frames();
            auto sFrame = sFrameSet.first_or_default(RS2_STREAM_FISHEYE);
            rs2::video_frame image_frame_left = sFrameSet.get_fisheye_frame(1);
            rs2::video_frame image_frame_right = sFrameSet.get_fisheye_frame(2);
            m_LastPoseRecievedTimeStamp = sFrameSet.get_timestamp();
            im_left = cv::Mat(cv::Size(width_img, height_img), CV_8UC1, (void*)(image_frame_left.get_data()), cv::Mat::AUTO_STEP);
            im_right = cv::Mat(cv::Size(width_img, height_img), CV_8UC1, (void*)(image_frame_right.get_data()), cv::Mat::AUTO_STEP);

            const Sophus::SE3f Tcw = SLAM.TrackStereo(im_left, im_right, m_LastPoseRecievedTimeStamp);

            Sophus::SE3f Twc = Tcw.inverse();
            Eigen::Vector3f twc = Twc.translation();
            Eigen::Quaternionf quaternion = Twc.unit_quaternion();

            rs2_pose rsPose;
            rsPose.translation.x = twc(0);
            rsPose.translation.y = -twc(1);
            rsPose.translation.z = -twc(2);
            rsPose.rotation.x = quaternion.x();
            rsPose.rotation.y = -quaternion.y();
            rsPose.rotation.z = -quaternion.z();
            rsPose.rotation.w = quaternion.w();

            m_LastPoseRecieved = rsPose;
            m_Status.bDriverSessionIsRunning = true;
            // std::this_thread::sleep_for(std::chrono::milliseconds(s_unPollingSleepIntervalInMilliSeconds));
        }

        rsPipeLine.stop();
        SLAM.Shutdown();
    } catch (const rs2::error&) {
        m_Status.bDriverSessionIsRunning = false;
    } catch (const std::exception&) {
        m_Status.bDriverSessionIsRunning = false;
    }
}
