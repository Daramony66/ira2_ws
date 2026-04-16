// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from unity_robotics_ira2:msg/PosRot.idl
// generated code does not contain a copyright notice

#include "unity_robotics_ira2/msg/detail/pos_rot__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__msg__PosRot__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x2a, 0x2d, 0x40, 0xab, 0xb1, 0x98, 0x04, 0x86,
      0x47, 0xd6, 0x44, 0xb0, 0xf0, 0x1b, 0xd5, 0xf1,
      0x13, 0x87, 0xed, 0xa6, 0x06, 0x8a, 0xd8, 0x55,
      0xa9, 0x07, 0xc9, 0x16, 0xe8, 0x0f, 0xc0, 0xb2,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char unity_robotics_ira2__msg__PosRot__TYPE_NAME[] = "unity_robotics_ira2/msg/PosRot";

// Define type names, field names, and default values
static char unity_robotics_ira2__msg__PosRot__FIELD_NAME__pos_x[] = "pos_x";
static char unity_robotics_ira2__msg__PosRot__FIELD_NAME__pos_y[] = "pos_y";
static char unity_robotics_ira2__msg__PosRot__FIELD_NAME__pos_z[] = "pos_z";
static char unity_robotics_ira2__msg__PosRot__FIELD_NAME__rot_x[] = "rot_x";
static char unity_robotics_ira2__msg__PosRot__FIELD_NAME__rot_y[] = "rot_y";
static char unity_robotics_ira2__msg__PosRot__FIELD_NAME__rot_z[] = "rot_z";
static char unity_robotics_ira2__msg__PosRot__FIELD_NAME__rot_w[] = "rot_w";

static rosidl_runtime_c__type_description__Field unity_robotics_ira2__msg__PosRot__FIELDS[] = {
  {
    {unity_robotics_ira2__msg__PosRot__FIELD_NAME__pos_x, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__PosRot__FIELD_NAME__pos_y, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__PosRot__FIELD_NAME__pos_z, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__PosRot__FIELD_NAME__rot_x, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__PosRot__FIELD_NAME__rot_y, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__PosRot__FIELD_NAME__rot_z, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__PosRot__FIELD_NAME__rot_w, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
unity_robotics_ira2__msg__PosRot__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {unity_robotics_ira2__msg__PosRot__TYPE_NAME, 30, 30},
      {unity_robotics_ira2__msg__PosRot__FIELDS, 7, 7},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 pos_x\n"
  "float32 pos_y\n"
  "float32 pos_z\n"
  "float32 rot_x\n"
  "float32 rot_y\n"
  "float32 rot_z\n"
  "float32 rot_w";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
unity_robotics_ira2__msg__PosRot__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {unity_robotics_ira2__msg__PosRot__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 97, 97},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__msg__PosRot__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *unity_robotics_ira2__msg__PosRot__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
