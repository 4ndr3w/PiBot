cmake_minimum_required(VERSION 2.8)
project(PiController)
set(CMAKE_MODULE_PATH cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DDMP_FIFO_RATE=9")
find_package ( libpixyusb REQUIRED )
find_package ( libusb-1.0 REQUIRED )
find_package ( Boost 1.49 COMPONENTS thread system chrono REQUIRED)


file(STRINGS "cmake/VERSION" LIBPIXY_VERSION)
add_definitions(-D__LIBPIXY_VERSION__="${LIBPIXY_VERSION}")

set(SOURCE_FILES main.cpp)
set(DRIVER_SOURCE_FILES drivers/PWM.cpp drivers/MPU6050/MPU6050.cpp drivers/MPU6050/SimpleDMP.cpp drivers/MPU6050/I2Cdev.cpp)
set(CONTROLLER_SOURCE_FILES controllers/RobotController.cpp controllers/PositionController.cpp controllers/BrickController.cpp controllers/PixyController.cpp)
set(VISION_SOURCE_FILES vision/pixy.cpp)
set(OTHER_SOURCES timing/TimedThread.cpp robot/Drivetrain.cpp controllers/JoystickDriveController.cpp)

add_executable(PiController ${SOURCE_FILES} ${DRIVER_SOURCE_FILES} ${CONTROLLER_SOURCE_FILES} ${VISION_SOURCE_FILES} ${OTHER_SOURCES})
target_link_libraries(PiController -pthread -lm -lwiringPi)
target_link_libraries(PiController pixyusb)
target_link_libraries (PiController ${Boost_LIBRARIES})
target_link_libraries (PiController ${LIBUSB_1_LIBRARY})
