// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from haptic_teleop:msg/PosRot.idl
// generated code does not contain a copyright notice

#ifndef HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "haptic_teleop/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "haptic_teleop/msg/detail/pos_rot__struct.hpp"

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

namespace haptic_teleop
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_haptic_teleop
cdr_serialize(
  const haptic_teleop::msg::PosRot & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_haptic_teleop
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  haptic_teleop::msg::PosRot & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_haptic_teleop
get_serialized_size(
  const haptic_teleop::msg::PosRot & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_haptic_teleop
max_serialized_size_PosRot(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_haptic_teleop
cdr_serialize_key(
  const haptic_teleop::msg::PosRot & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_haptic_teleop
get_serialized_size_key(
  const haptic_teleop::msg::PosRot & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_haptic_teleop
max_serialized_size_key_PosRot(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace haptic_teleop

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_haptic_teleop
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, haptic_teleop, msg, PosRot)();

#ifdef __cplusplus
}
#endif

#endif  // HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
