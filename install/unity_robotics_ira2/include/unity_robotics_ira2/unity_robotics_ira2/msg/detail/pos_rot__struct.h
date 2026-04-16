// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from unity_robotics_ira2:msg/PosRot.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unity_robotics_ira2/msg/pos_rot.h"


#ifndef UNITY_ROBOTICS_IRA2__MSG__DETAIL__POS_ROT__STRUCT_H_
#define UNITY_ROBOTICS_IRA2__MSG__DETAIL__POS_ROT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/PosRot in the package unity_robotics_ira2.
typedef struct unity_robotics_ira2__msg__PosRot
{
  float pos_x;
  float pos_y;
  float pos_z;
  float rot_x;
  float rot_y;
  float rot_z;
  float rot_w;
} unity_robotics_ira2__msg__PosRot;

// Struct for a sequence of unity_robotics_ira2__msg__PosRot.
typedef struct unity_robotics_ira2__msg__PosRot__Sequence
{
  unity_robotics_ira2__msg__PosRot * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} unity_robotics_ira2__msg__PosRot__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UNITY_ROBOTICS_IRA2__MSG__DETAIL__POS_ROT__STRUCT_H_
