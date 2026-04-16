// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from haptic_teleop:msg/PosRot.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/msg/pos_rot.h"


#ifndef HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__STRUCT_H_
#define HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/PosRot in the package haptic_teleop.
typedef struct haptic_teleop__msg__PosRot
{
  float pos_x;
  float pos_y;
  float pos_z;
  float rot_x;
  float rot_y;
  float rot_z;
  float rot_w;
} haptic_teleop__msg__PosRot;

// Struct for a sequence of haptic_teleop__msg__PosRot.
typedef struct haptic_teleop__msg__PosRot__Sequence
{
  haptic_teleop__msg__PosRot * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} haptic_teleop__msg__PosRot__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__STRUCT_H_
