// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from unity_robotics_ira2:msg/PosRot.idl
// generated code does not contain a copyright notice

#ifndef UNITY_ROBOTICS_IRA2__MSG__DETAIL__POS_ROT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define UNITY_ROBOTICS_IRA2__MSG__DETAIL__POS_ROT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "unity_robotics_ira2/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "unity_robotics_ira2/msg/detail/pos_rot__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace unity_robotics_ira2
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_unity_robotics_ira2
cdr_serialize(
  const unity_robotics_ira2::msg::PosRot & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_unity_robotics_ira2
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  unity_robotics_ira2::msg::PosRot & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_unity_robotics_ira2
get_serialized_size(
  const unity_robotics_ira2::msg::PosRot & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_unity_robotics_ira2
max_serialized_size_PosRot(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_unity_robotics_ira2
cdr_serialize_key(
  const unity_robotics_ira2::msg::PosRot & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_unity_robotics_ira2
get_serialized_size_key(
  const unity_robotics_ira2::msg::PosRot & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_unity_robotics_ira2
max_serialized_size_key_PosRot(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace unity_robotics_ira2

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_unity_robotics_ira2
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, unity_robotics_ira2, msg, PosRot)();

#ifdef __cplusplus
}
#endif

#endif  // UNITY_ROBOTICS_IRA2__MSG__DETAIL__POS_ROT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
