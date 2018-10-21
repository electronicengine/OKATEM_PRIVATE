cmake_minimum_required(VERSION 2.8)


set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_C_FLAGS "-std=c++17")
Set(CMAKE_CXX_FLAGS "-std=c++17")


include_directories(
    /usr/local/include/
    /usr/lib/
    )

link_directories(
    /usr/local/lib/
    /usr/lib/

    )


project(apptics_controller)

link_libraries(

    ncurses
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
       "main.cpp"
       "udpsocket.cpp"
       "controller.cpp"
       "videostream.cpp"
       )
