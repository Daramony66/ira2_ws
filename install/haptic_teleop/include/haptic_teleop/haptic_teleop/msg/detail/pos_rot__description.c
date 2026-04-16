// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from haptic_teleop:msg/PosRot.idl
// generated code does not contain a copyright notice

#include "haptic_teleop/msg/detail/pos_rot__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_type_hash_t *
haptic_teleop__msg__PosRot__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x30, 0xcf, 0x11, 0x6a, 0x3a, 0xf3, 0x63, 0x84,
      0x3e, 0x25, 0x3e, 0xc9, 0x42, 0x03, 0xbe, 0xa6,
      0x0b, 0xf9, 0xe5, 0xfc, 0x58, 0x52, 0xad, 0x64,
      0x63, 0xe9, 0x15, 0xba, 0xd0, 0xb7, 0xfc, 0xf8,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char haptic_teleop__msg__PosRot__TYPE_NAME[] = "haptic_teleop/msg/PosRot";

// Define type names, field names, and default values
static char haptic_teleop__msg__PosRot__FIELD_NAME__pos_x[] = "pos_x";
static char haptic_teleop__msg__PosRot__FIELD_NAME__pos_y[] = "pos_y";
static char haptic_teleop__msg__PosRot__FIELD_NAME__pos_z[] = "pos_z";
static char haptic_teleop__msg__PosRot__FIELD_NAME__rot_x[] = "rot_x";
static char haptic_teleop__msg__PosRot__FIELD_NAME__rot_y[] = "rot_y";
static char haptic_teleop__msg__PosRot__FIELD_NAME__rot_z[] = "rot_z";
static char haptic_teleop__msg__PosRot__FIELD_NAME__rot_w[] = "rot_w";

static rosidl_runtime_c__type_description__Field haptic_teleop__msg__PosRot__FIELDS[] = {
  {
    {haptic_teleop__msg__PosRot__FIELD_NAME__pos_x, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__PosRot__FIELD_NAME__pos_y, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__PosRot__FIELD_NAME__pos_z, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__PosRot__FIELD_NAME__rot_x, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__PosRot__FIELD_NAME__rot_y, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__PosRot__FIELD_NAME__rot_z, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__PosRot__FIELD_NAME__rot_w, 5, 5},
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
haptic_teleop__msg__PosRot__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {haptic_teleop__msg__PosRot__TYPE_NAME, 24, 24},
      {haptic_teleop__msg__PosRot__FIELDS, 7, 7},
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
haptic_teleop__msg__PosRot__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {haptic_teleop__msg__PosRot__TYPE_NAME, 24, 24},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 97, 97},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
haptic_teleop__msg__PosRot__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *haptic_teleop__msg__PosRot__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
