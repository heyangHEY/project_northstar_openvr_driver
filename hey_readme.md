build_202405
20240519编译，可在win11上运行，编译环境：
1. win11，以管理员身份运行 msys2（ucrt64）
2. 
    mkdir build
    cd build
    cmake -G "Visual Studio 17 2022" ..
    cmake --build . --config Release

    # 清除build目录
    rm -rf ./*

    # install
    cd build
    cmake --install .
    # install命令需要管理员身份
3. 默认的install目录为：C:/Program Files (x86)/Northstar_OpenVR/northstar
4. 在 C:\Users\Yang\AppData\Local\openvr\openvrpaths.vrpath 的 external_drivers 中添加：
    "external_drivers" : 
	[
		"C:\\Program Files (x86)\\Northstar_OpenVR\\northstar"
	]
5. 在 C:\Program Files (x86)\Steam\config\steamvr.vrsettings 中添加
    "TrackingOverrides" : {
      "/devices/htc/vive_trackerLHR-432133A9" : "/user/head",
      "/devices/lighthouse/LHR-3F9E6C1E" : "/user/hand/left",
      "/devices/lighthouse/LHR-EC6911DA" : "/user/hand/right"
   },
   "driver_northstar" : {
      "blocked_by_safe_mode" : false
   }
6. 开启多驱动模式
    Steam 安装目录下找到\steamapps\common\SteamVR\resources\settings\default.vrsettings
    修改requireHmd 为false， 修改activateMultipleDrivers 为true
7. pc上插入sw3接收器，开启lighthouse灯塔、index手柄、vive tracker，插入rokid眼镜，长按按键10s，进入3D模式，调整显示器和主屏幕的相对位置，调整 
    C:\Program Files (x86)\Northstar_OpenVR\northstar\resources\settings\default.vrsettings 中的参数。
8. 开启steamvr，如果报错109，则大概是因为compositor合成器无法正确的在rokid的3d桌面上显示