// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from haptic_teleop:msg/UnityColor.idl
// generated code does not contain a copyright notice

#include "haptic_teleop/msg/detail/unity_color__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_type_hash_t *
haptic_teleop__msg__UnityColor__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x98, 0x9f, 0x97, 0x12, 0x9a, 0x4d, 0x08, 0x6f,
      0x77, 0x62, 0xb8, 0xee, 0xb7, 0x83, 0x92, 0x72,
      0x3a, 0xa5, 0xd1, 0xf1, 0x53, 0x9b, 0x6d, 0xef,
      0xe7, 0xec, 0x87, 0x5b, 0x88, 0x11, 0x3b, 0xe8,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char haptic_teleop__msg__UnityColor__TYPE_NAME[] = "haptic_teleop/msg/UnityColor";

// Define type names, field names, and default values
static char haptic_teleop__msg__UnityColor__FIELD_NAME__r[] = "r";
static char haptic_teleop__msg__UnityColor__FIELD_NAME__g[] = "g";
static char haptic_teleop__msg__UnityColor__FIELD_NAME__b[] = "b";
static char haptic_teleop__msg__UnityColor__FIELD_NAME__a[] = "a";

static rosidl_runtime_c__type_description__Field haptic_teleop__msg__UnityColor__FIELDS[] = {
  {
    {haptic_teleop__msg__UnityColor__FIELD_NAME__r, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__UnityColor__FIELD_NAME__g, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__UnityColor__FIELD_NAME__b, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__UnityColor__FIELD_NAME__a, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
haptic_teleop__msg__UnityColor__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {haptic_teleop__msg__UnityColor__TYPE_NAME, 28, 28},
      {haptic_teleop__msg__UnityColor__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 r\n"
  "int32 g\n"
  "int32 b\n"
  "int32 a";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
haptic_teleop__msg__UnityColor__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {haptic_teleop__msg__UnityColor__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 32, 32},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
haptic_teleop__msg__UnityColor__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *haptic_teleop__msg__UnityColor__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
