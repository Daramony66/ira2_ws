cmake_minimum_required(VERSION 3.8)
project(haptic_teleop)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED) #Ajouté le 31/03 à 11h10
find_package(tf2 REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(ur_rtde REQUIRED)
find_package(builtin_interfaces REQUIRED)

# Install message files

rosidl_generate_interfaces(${PROJECT_NAME}
#  "msg/HapticInfo.msg"
  "msg/PosRot.msg"
  "msg/UnityColor.msg"
  "srv/PositionService.srv"
  "srv/ObjectPoseService.srv"
  DEPENDENCIES builtin_interfaces std_msgs geometry_msgs
)

ament_export_dependencies(rosidl_default_runtime)

# define executables
add_executable(unity_control src/unity_control.cpp)
add_executable(unity_control_v2 src/unity_control_v2.cpp)
add_executable(robot_control src/robot_control.cpp)
add_executable(joints_sub src/joints_sub.cpp)
add_executable(haptic_control src/haptic_control.cpp)

#ajouté le 03/03 à 10h30
add_executable(haptic_control2 src/haptic_control2.cpp)

#Ajouté le 18/03 à 10h32 
add_executable(haptic_control3 src/haptic_control3.cpp)

#Ajouté le 19/03 à 17h42
add_executable(haptic_control4 src/haptic_control4.cpp)

add_executable(get_force src/get_force.cpp)
add_executable(color_publisher src/color_publisher.cpp)
add_executable(position_service src/position_service.cpp)

# Define dependencies for each executable
ament_target_dependencies(unity_control
  rclcpp 
  geometry_msgs
  std_msgs
  tf2
)

ament_target_dependencies(unity_control_v2
  rclcpp 
  geometry_msgs
  std_msgs
  ur_rtde
  tf2
)


ament_target_dependencies(robot_control 
  rclcpp 
  ur_rtde
  geometry_msgs
  tf2
)


ament_target_dependencies(joints_sub 
  rclcpp 
  sensor_msgs
  ur_rtde
  std_msgs
)

ament_target_dependencies(haptic_control
  rclcpp 
  geometry_msgs
  std_msgs
  tf2
  Boost
  ur_rtde
  std_msgs
)
add_dependencies(haptic_control ${PROJECT_NAME}__rosidl_generator_cpp)

#ajouté le 03/03 à 10h30
ament_target_dependencies(haptic_control2
rclcpp 
geometry_msgs
std_msgs
tf2
Boost
ur_rtde
std_msgs
)
add_dependencies(haptic_control2 ${PROJECT_NAME}__rosidl_generator_cpp)

#Ajouté le 18/03 à 10h34
ament_target_dependencies(haptic_control3
  rclcpp
  geometry_msgs
  std_msgs
  tf2
  Boost
  ur_rtde
  std_msgs
  std_srvs #Ajouté le 31/03 à 11h10
)
add_dependencies(haptic_control3 ${PROJECT_NAME}__rosidl_generator_cpp)

#Ajouté le 19/03 à 17h43
ament_target_dependencies(haptic_control4
  rclcpp
  geometry_msgs
  std_msgs
  tf2
  Boost
  ur_rtde
  std_msgs
)
add_dependencies(haptic_control4 ${PROJECT_NAME}__rosidl_generator_cpp)



ament_target_dependencies(get_force 
  rclcpp 
  geometry_msgs
)

ament_target_dependencies(color_publisher 
  rclcpp 
  std_msgs
)
add_dependencies(color_publisher ${PROJECT_NAME}__rosidl_generator_cpp)

ament_target_dependencies(position_service 
  rclcpp 
  geometry_msgs
  std_msgs
)
add_dependencies(position_service ${PROJECT_NAME}__rosidl_generator_cpp)

# Install executables
install(TARGETS
  unity_control
  unity_control_v2
  robot_control
  joints_sub
  haptic_control
  haptic_control2 #ajouté  le 03/03 à 10h30
  haptic_control3 #Ajouté le 18/03 à 10h35
  haptic_control4 #Ajouté le 19/03 à 17h43
  get_force
  color_publisher
  position_service
  DESTINATION lib/${PROJECT_NAME}
)

rosidl_target_interfaces(haptic_control
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

#ajouté le 03/03 à 10h30
rosidl_target_interfaces(haptic_control2
${PROJECT_NAME} "rosidl_typesupport_cpp"
)

#ajouté le 18/03 à 10h30
rosidl_target_interfaces(haptic_control3
${PROJECT_NAME} "rosidl_typesupport_cpp"
)

#ajouté le 19/03 à 17h43
rosidl_target_interfaces(haptic_control4
${PROJECT_NAME} "rosidl_typesupport_cpp"
)


rosidl_target_interfaces(color_publisher
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)
rosidl_target_interfaces(position_service
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

target_link_libraries(haptic_control ur_rtde::rtde)

#ajoutée le 03/03 à 10h30
target_link_libraries(haptic_control2 ur_rtde::rtde)

#Ajouté le 18/03 à 10h33
target_link_libraries(haptic_control3 ur_rtde::rtde)

#Ajouté le 19/03 à 17h44
target_link_libraries(haptic_control4 ur_rtde::rtde)

target_link_libraries(joints_sub ur_rtde::rtde)
target_link_libraries(robot_control ur_rtde::rtde)
target_link_libraries(unity_control_v2 ur_rtde::rtde)
target_link_libraries(get_force ur_rtde::rtde)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
