cmake_minimum_required(VERSION 2.8)

set(INCLUDE_PATH
    ./src
    )

include_directories(${INCLUDE_PATH}
#    /usr/local/include
     /root/Downloads/opencv-3.4.0/build_arm/
     /usr/arm-linux-gnueabi/include
    )


project(apptics)

set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)

#set(CMAKE_C_COMPILER /usr/bin/gcc)
#set(CMAKE_CXX_COMPILER /usr/bin/g++)


set(CMAKE_C_FLAGS "-std=c++14")
Set(CMAKE_CXX_FLAGS "-std=c++14")


#find_library(/usr/lib/x86_64-linux-gnu
#    /usr/local/lib/
#    )


#find_package(OpenCV)


link_directories(
#    /usr/local/lib/
#    /usr/lib/
#    /usr/lib/x86_64-linux-gnu
    /usr/arm-linux-gnueabi/lib
    )

link_libraries(
    pthread
    opencv_calib3d
    opencv_core
    opencv_dnn
    opencv_features2d
    opencv_flann
    opencv_highgui
    opencv_imgcodecs
    opencv_imgproc
    opencv_ml
    opencv_objdetect
    opencv_photo
    opencv_shape
    opencv_stitching
    opencv_superres
    opencv_videoio
    opencv_video
    opencv_videostab
    )

add_executable(${PROJECT_NAME}
    main.cpp
    ${INCLUDE_PATH}/lasertracker.cpp
    ${INCLUDE_PATH}/serialcom.cpp
    ${INCLUDE_PATH}/lorawan.cpp
    ${INCLUDE_PATH}/spicom.cpp
    ${INCLUDE_PATH}/bananapi.cpp
    )

#target_link_libraries( ${PROJECT_NAME}
#    pthread
#    opencv_calib3d
#    opencv_core
#    opencv_dnn
#    opencv_features2d
#    opencv_flann
#    opencv_highgui
#    opencv_imgcodecs
#    opencv_imgproc
#    opencv_ml
#    opencv_objdetect
#    opencv_photo
#    opencv_shape
#    opencv_stitching
#    opencv_superres
#    opencv_videoio
#    opencv_video
#    opencv_videostab
#    )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  #COMMAND sudo sshpass -p "bananapi" scp -r ../build-apptics-Desktop-Debug pi@10.100.93.17:/home/pi
  #COMMAND sudo sshpass -p "bananapi" scp -r /root/qt-workspace/apptics pi@10.100.93.17:/home/pi
  COMMENT "Creating directory: "
)
