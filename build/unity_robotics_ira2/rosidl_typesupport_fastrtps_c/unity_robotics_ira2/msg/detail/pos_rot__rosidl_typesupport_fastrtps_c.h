// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from unity_robotics_ira2:msg/PosRot.idl
// generated code does not contain a copyright notice
#ifndef UNITY_ROBOTICS_IRA2__MSG__DETAIL__POS_ROT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define UNITY_ROBOTICS_IRA2__MSG__DETAIL__POS_ROT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "unity_robotics_ira2/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "unity_robotics_ira2/msg/detail/pos_rot__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2
bool cdr_serialize_unity_robotics_ira2__msg__PosRot(
  const unity_robotics_ira2__msg__PosRot * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2
bool cdr_deserialize_unity_robotics_ira2__msg__PosRot(
  eprosima::fastcdr::Cdr &,
  unity_robotics_ira2__msg__PosRot * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2
size_t get_serialized_size_unity_robotics_ira2__msg__PosRot(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2
size_t max_serialized_size_unity_robotics_ira2__msg__PosRot(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2
bool cdr_serialize_key_unity_robotics_ira2__msg__PosRot(
  const unity_robotics_ira2__msg__PosRot * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2
size_t get_serialized_size_key_unity_robotics_ira2__msg__PosRot(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2
size_t max_serialized_size_key_unity_robotics_ira2__msg__PosRot(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, unity_robotics_ira2, msg, PosRot)();

#ifdef __cplusplus
}
#endif

#endif  // UNITY_ROBOTICS_IRA2__MSG__DETAIL__POS_ROT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
