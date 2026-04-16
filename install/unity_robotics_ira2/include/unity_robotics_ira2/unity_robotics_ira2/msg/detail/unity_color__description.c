// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from unity_robotics_ira2:msg/UnityColor.idl
// generated code does not contain a copyright notice

#include "unity_robotics_ira2/msg/detail/unity_color__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__msg__UnityColor__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x3d, 0x22, 0x98, 0xff, 0xf3, 0xad, 0x36, 0x60,
      0x75, 0x3f, 0x20, 0xce, 0x8b, 0x03, 0x48, 0x84,
      0x74, 0x11, 0xdb, 0x50, 0x02, 0x0a, 0x10, 0x74,
      0xdc, 0x3c, 0x12, 0x4b, 0xdb, 0xe6, 0x95, 0xf2,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char unity_robotics_ira2__msg__UnityColor__TYPE_NAME[] = "unity_robotics_ira2/msg/UnityColor";

// Define type names, field names, and default values
static char unity_robotics_ira2__msg__UnityColor__FIELD_NAME__r[] = "r";
static char unity_robotics_ira2__msg__UnityColor__FIELD_NAME__g[] = "g";
static char unity_robotics_ira2__msg__UnityColor__FIELD_NAME__b[] = "b";
static char unity_robotics_ira2__msg__UnityColor__FIELD_NAME__a[] = "a";

static rosidl_runtime_c__type_description__Field unity_robotics_ira2__msg__UnityColor__FIELDS[] = {
  {
    {unity_robotics_ira2__msg__UnityColor__FIELD_NAME__r, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__UnityColor__FIELD_NAME__g, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__UnityColor__FIELD_NAME__b, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__UnityColor__FIELD_NAME__a, 1, 1},
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
unity_robotics_ira2__msg__UnityColor__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {unity_robotics_ira2__msg__UnityColor__TYPE_NAME, 34, 34},
      {unity_robotics_ira2__msg__UnityColor__FIELDS, 4, 4},
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
unity_robotics_ira2__msg__UnityColor__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {unity_robotics_ira2__msg__UnityColor__TYPE_NAME, 34, 34},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 32, 32},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__msg__UnityColor__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *unity_robotics_ira2__msg__UnityColor__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
