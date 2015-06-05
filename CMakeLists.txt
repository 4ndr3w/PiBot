cmake_minimum_required(VERSION 2.8)
project(PiBot)
set(CMAKE_MODULE_PATH cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DDMP_FIFO_RATE=9")
find_package ( libpixyusb REQUIRED )
find_package ( libusb-1.0 REQUIRED )
find_package ( Boost 1.49 COMPONENTS thread system chrono REQUIRED)


file(STRINGS "cmake/VERSION" LIBPIXY_VERSION)
add_definitions(-D__LIBPIXY_VERSION__="${LIBPIXY_VERSION}")

set(SOURCE_FILES core.cpp)
set(DRIVER_SOURCE_FILES drivers/PWM.cpp drivers/MPU6050/MPU6050.cpp drivers/MPU6050/SimpleDMP.cpp drivers/MPU6050/I2Cdev.cpp drivers/LIDAR.cpp)
set(CONTROLLER_SOURCE_FILES controllers/RobotController.cpp controllers/PositionController.cpp controllers/BrickController.cpp controllers/PixyController.cpp controllers/ProfileFollower.cpp)
set(VISION_SOURCE_FILES vision/pixy.cpp)
set(OTHER_SOURCES timing/TimedThread.cpp robot/Drivetrain.cpp controllers/JoystickDriveController.cpp)
set(ROBOT_LIB ${SOURCE_FILES} ${DRIVER_SOURCE_FILES} ${CONTROLLER_SOURCE_FILES} ${VISION_SOURCE_FILES} ${OTHER_SOURCES})

set(LINK_LIBS ${CMAKE_SOURCE_DIR}/librplidar_sdk.a -pthread -lm -lwiringPi pixyusb ${Boost_LIBRARIES} ${LIBUSB_1_LIBRARY} ${CMAKE_SOURCE_DIR}/librplidar_sdk.a rt)

add_library(RobotLib ${ROBOT_LIB})
target_link_libraries(RobotLib ${LINK_LIBS})

add_executable(BallDemo BallDemo.cpp)
target_link_libraries(BallDemo RobotLib)

add_executable(JoystickDemo JoystickDemo.cpp)
target_link_libraries(JoystickDemo RobotLib)

add_executable(GridDemo GridDemo.cpp)
target_link_libraries(GridDemo RobotLib)

add_executable(1DProfile 1DProfile.cpp)
target_link_libraries(1DProfile RobotLib)


add_executable(LidarMapDemo LidarMap.cpp)
target_link_libraries(LidarMapDemo RobotLib)