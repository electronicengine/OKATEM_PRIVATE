cmake_minimum_required(VERSION 2.8)

set(INCLUDE_PATH
    ./src
    )

include_directories(${INCLUDE_PATH}
#    /usr/local/include
#     /root/Downloads/opencv-3.4.0/build/
     /usr/arm-linux-gnueabihf/include
    )


project(apptics)

set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

#set(CMAKE_C_COMPILER /usr/bin/gcc)
#set(CMAKE_CXX_COMPILER /usr/bin/g++)


set(CMAKE_C_FLAGS "-std=c++17")
Set(CMAKE_CXX_FLAGS "-std=c++17")


#find_library(/usr/lib/x86_64-linux-gnu
#    /usr/local/lib/
#    )


#find_package(OpenCV)


link_directories(
#    /usr/local/lib/
#    /usr/lib/
#    /usr/lib/x86_64-linux-gnu
    /usr/arm-linux-gnueabihf/lib
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
    ${INCLUDE_PATH}/lcdhmi.cpp
    ${INCLUDE_PATH}/lasertracker.cpp
    ${INCLUDE_PATH}/serialcom.cpp
    ${INCLUDE_PATH}/lorawan.cpp
    ${INCLUDE_PATH}/spicom.cpp
    ${INCLUDE_PATH}/controller.cpp
    ${INCLUDE_PATH}/sfpmonitor.cpp
    ${INCLUDE_PATH}/udpsocket.cpp
    ${INCLUDE_PATH}/queue.cpp
    ${INCLUDE_PATH}/json.cpp
    ${INCLUDE_PATH}/datatypes.h
    ${INCLUDE_PATH}/globals.cpp

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
#  COMMAND sudo sshpass -p "hyperion" scp -r ../build-apptics-Desktop-Debug pi@10.100.93.61:/home/pi
#  COMMAND sudo sshpass -p "hyperion" scp -r ../build-apptics-Desktop-Debug pi@10.100.93.62:/home/pi
  COMMENT "Creating directory: "
)
