// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from haptic_teleop:msg/UnityColor.idl
// generated code does not contain a copyright notice
#ifndef HAPTIC_TELEOP__MSG__DETAIL__UNITY_COLOR__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define HAPTIC_TELEOP__MSG__DETAIL__UNITY_COLOR__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "haptic_teleop/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "haptic_teleop/msg/detail/unity_color__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_haptic_teleop
bool cdr_serialize_haptic_teleop__msg__UnityColor(
  const haptic_teleop__msg__UnityColor * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_haptic_teleop
bool cdr_deserialize_haptic_teleop__msg__UnityColor(
  eprosima::fastcdr::Cdr &,
  haptic_teleop__msg__UnityColor * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_haptic_teleop
size_t get_serialized_size_haptic_teleop__msg__UnityColor(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_haptic_teleop
size_t max_serialized_size_haptic_teleop__msg__UnityColor(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_haptic_teleop
bool cdr_serialize_key_haptic_teleop__msg__UnityColor(
  const haptic_teleop__msg__UnityColor * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_haptic_teleop
size_t get_serialized_size_key_haptic_teleop__msg__UnityColor(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_haptic_teleop
size_t max_serialized_size_key_haptic_teleop__msg__UnityColor(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_haptic_teleop
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, haptic_teleop, msg, UnityColor)();

#ifdef __cplusplus
}
#endif

#endif  // HAPTIC_TELEOP__MSG__DETAIL__UNITY_COLOR__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
