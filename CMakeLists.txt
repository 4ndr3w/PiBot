project(PiController)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DDMP_FIFO_RATE=9")

set(SOURCE_FILES main.cpp)
set(DRIVER_SOURCE_FILES drivers/PWM.cpp drivers/MPU6050/MPU6050.cpp drivers/MPU6050/SimpleDMP.cpp drivers/MPU6050/I2Cdev.cpp)
set(NETWORK_SOURCE_FILES network/NetComm.cpp)
set(CONTROLLER_SOURCE_FILES controllers/RobotController.cpp controllers/PositionController.cpp controllers/BrickController.cpp)
set(OTHER_SOURCES timing/TimedThread.cpp robot/Drivetrain.cpp controllers/JoystickDriveController.cpp)

add_executable(PiController ${SOURCE_FILES} ${DRIVER_SOURCE_FILES} ${NETWORK_SOURCE_FILES} ${CONTROLLER_SOURCE_FILES} ${OTHER_SOURCES} vision/pixy.h vision/pixy.cpp)
target_link_libraries(PiController -pthread -lm -lwiringPi)
