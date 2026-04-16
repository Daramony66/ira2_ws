// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from haptic_teleop:msg/UnityColor.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/msg/unity_color.h"


#ifndef HAPTIC_TELEOP__MSG__DETAIL__UNITY_COLOR__STRUCT_H_
#define HAPTIC_TELEOP__MSG__DETAIL__UNITY_COLOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/UnityColor in the package haptic_teleop.
typedef struct haptic_teleop__msg__UnityColor
{
  int32_t r;
  int32_t g;
  int32_t b;
  int32_t a;
} haptic_teleop__msg__UnityColor;

// Struct for a sequence of haptic_teleop__msg__UnityColor.
typedef struct haptic_teleop__msg__UnityColor__Sequence
{
  haptic_teleop__msg__UnityColor * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} haptic_teleop__msg__UnityColor__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HAPTIC_TELEOP__MSG__DETAIL__UNITY_COLOR__STRUCT_H_
