cmake_minimum_required(VERSION 2.8.3)
project(bebop_autopilot)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare ROS messages and services

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)
#generate_messages(DEPENDENCIES geometry_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(Test src/test.cpp)
target_link_libraries(Test ${catkin_LIBRARIES})
add_dependencies(Test bebop_controller_generate_messages_cpp)


add_executable(keyboard_controller src/keyboard_controller.cpp)
target_link_libraries(keyboard_controller ${catkin_LIBRARIES})
add_dependencies(keyboard_controller bebop_controller_generate_messages_cpp)

add_executable(keyboard_controller1 src/keyboard_controller1.cpp)
target_link_libraries(keyboard_controller1 ${catkin_LIBRARIES})
add_dependencies(keyboard_controller1 bebop_controller_generate_messages_cpp)

add_executable(keyboard_controller2 src/keyboard_controller2.cpp)
target_link_libraries(keyboard_controller2 ${catkin_LIBRARIES})
add_dependencies(keyboard_controller2 bebop_controller_generate_messages_cpp)


add_executable(BebopController src/BebopController.cpp)
target_link_libraries(BebopController ${catkin_LIBRARIES})
add_dependencies(BebopController bebop_controller_generate_messages_cpp)

add_executable(DirectionController src/DirectionController.cpp)
target_link_libraries(DirectionController ${catkin_LIBRARIES})
add_dependencies(DirectionController bebop_controller_generate_messages_cpp)

add_executable(SpeedController src/SpeedController.cpp)
target_link_libraries(SpeedController ${catkin_LIBRARIES})
add_dependencies(SpeedController bebop_controller_generate_messages_cpp)


add_executable(Agent src/Agent.cpp)
target_link_libraries(Agent ${catkin_LIBRARIES})
add_dependencies(Agent bebop_controller_generate_messages_cpp)

add_executable(SpeedController_follower src/SpeedController_follower.cpp)
target_link_libraries(SpeedController_follower ${catkin_LIBRARIES})
add_dependencies(SpeedController_follower bebop_controller_generate_messages_cpp)

add_executable(DirectionController_follower src/DirectionController_follower.cpp)
target_link_libraries(DirectionController_follower ${catkin_LIBRARIES})
add_dependencies(DirectionController_follower bebop_controller_generate_messages_cpp)

add_executable(BebopController_follower src/BebopController_follower.cpp)
target_link_libraries(BebopController_follower ${catkin_LIBRARIES})
add_dependencies(BebopController_follower bebop_controller_generate_messages_cpp)

add_executable(SpeedController_follower1 src/SpeedController_follower1.cpp)
target_link_libraries(SpeedController_follower1 ${catkin_LIBRARIES})
add_dependencies(SpeedController_follower1 bebop_controller_generate_messages_cpp)

add_executable(DirectionController_follower1 src/DirectionController_follower1.cpp)
target_link_libraries(DirectionController_follower1 ${catkin_LIBRARIES})
add_dependencies(DirectionController_follower1 bebop_controller_generate_messages_cpp)

add_executable(BebopController_follower1 src/BebopController_follower1.cpp)
target_link_libraries(BebopController_follower1 ${catkin_LIBRARIES})
add_dependencies(BebopController_follower1 bebop_controller_generate_messages_cpp)




