// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from haptic_teleop:srv/PositionService.idl
// generated code does not contain a copyright notice

#include "haptic_teleop/srv/detail/position_service__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_type_hash_t *
haptic_teleop__srv__PositionService__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x7e, 0x5f, 0x33, 0x09, 0x2c, 0x02, 0xb6, 0x5a,
      0x8a, 0xd2, 0x6d, 0x98, 0xa2, 0xea, 0x0c, 0x61,
      0x1f, 0x9a, 0x06, 0x70, 0x2a, 0xca, 0xa8, 0x84,
      0xa6, 0x51, 0x17, 0xdd, 0x51, 0x76, 0x6b, 0x6a,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_type_hash_t *
haptic_teleop__srv__PositionService_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x7c, 0x47, 0xf6, 0x80, 0xc3, 0x3f, 0xb4, 0x57,
      0x47, 0xfc, 0x73, 0x9a, 0x7b, 0x99, 0xc0, 0x3f,
      0x8d, 0x89, 0x17, 0xb8, 0xa0, 0x53, 0x3d, 0x85,
      0x65, 0xc5, 0x22, 0xdd, 0xbd, 0xb6, 0x73, 0x7e,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_type_hash_t *
haptic_teleop__srv__PositionService_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe4, 0x11, 0xe4, 0x2c, 0xd1, 0xd0, 0xf5, 0xa1,
      0xa1, 0x97, 0x08, 0xe4, 0xe7, 0xf9, 0x06, 0xa4,
      0xe1, 0x64, 0x34, 0x29, 0x15, 0x60, 0x5e, 0x6a,
      0x17, 0x16, 0x19, 0x75, 0x3b, 0x22, 0xb9, 0xfd,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_type_hash_t *
haptic_teleop__srv__PositionService_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x62, 0x10, 0x0f, 0x3f, 0xd0, 0x41, 0x78, 0xd3,
      0xa1, 0x79, 0x81, 0x60, 0x9a, 0x45, 0x5c, 0x4d,
      0xe3, 0x8c, 0x13, 0x96, 0xc9, 0xa7, 0xcd, 0xad,
      0x8a, 0x71, 0x4c, 0x82, 0x4c, 0xd7, 0x3c, 0x2d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "haptic_teleop/msg/detail/pos_rot__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t haptic_teleop__msg__PosRot__EXPECTED_HASH = {1, {
    0x30, 0xcf, 0x11, 0x6a, 0x3a, 0xf3, 0x63, 0x84,
    0x3e, 0x25, 0x3e, 0xc9, 0x42, 0x03, 0xbe, 0xa6,
    0x0b, 0xf9, 0xe5, 0xfc, 0x58, 0x52, 0xad, 0x64,
    0x63, 0xe9, 0x15, 0xba, 0xd0, 0xb7, 0xfc, 0xf8,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char haptic_teleop__srv__PositionService__TYPE_NAME[] = "haptic_teleop/srv/PositionService";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char haptic_teleop__msg__PosRot__TYPE_NAME[] = "haptic_teleop/msg/PosRot";
static char haptic_teleop__srv__PositionService_Event__TYPE_NAME[] = "haptic_teleop/srv/PositionService_Event";
static char haptic_teleop__srv__PositionService_Request__TYPE_NAME[] = "haptic_teleop/srv/PositionService_Request";
static char haptic_teleop__srv__PositionService_Response__TYPE_NAME[] = "haptic_teleop/srv/PositionService_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char haptic_teleop__srv__PositionService__FIELD_NAME__request_message[] = "request_message";
static char haptic_teleop__srv__PositionService__FIELD_NAME__response_message[] = "response_message";
static char haptic_teleop__srv__PositionService__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field haptic_teleop__srv__PositionService__FIELDS[] = {
  {
    {haptic_teleop__srv__PositionService__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {haptic_teleop__srv__PositionService_Request__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__srv__PositionService__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {haptic_teleop__srv__PositionService_Response__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__srv__PositionService__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {haptic_teleop__srv__PositionService_Event__TYPE_NAME, 39, 39},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription haptic_teleop__srv__PositionService__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__PosRot__TYPE_NAME, 24, 24},
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__srv__PositionService_Event__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__srv__PositionService_Request__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__srv__PositionService_Response__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
haptic_teleop__srv__PositionService__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {haptic_teleop__srv__PositionService__TYPE_NAME, 33, 33},
      {haptic_teleop__srv__PositionService__FIELDS, 3, 3},
    },
    {haptic_teleop__srv__PositionService__REFERENCED_TYPE_DESCRIPTIONS, 6, 6},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&haptic_teleop__msg__PosRot__EXPECTED_HASH, haptic_teleop__msg__PosRot__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = haptic_teleop__msg__PosRot__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = haptic_teleop__srv__PositionService_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = haptic_teleop__srv__PositionService_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = haptic_teleop__srv__PositionService_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char haptic_teleop__srv__PositionService_Request__FIELD_NAME__input[] = "input";

static rosidl_runtime_c__type_description__Field haptic_teleop__srv__PositionService_Request__FIELDS[] = {
  {
    {haptic_teleop__srv__PositionService_Request__FIELD_NAME__input, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {haptic_teleop__msg__PosRot__TYPE_NAME, 24, 24},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription haptic_teleop__srv__PositionService_Request__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {haptic_teleop__msg__PosRot__TYPE_NAME, 24, 24},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
haptic_teleop__srv__PositionService_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {haptic_teleop__srv__PositionService_Request__TYPE_NAME, 41, 41},
      {haptic_teleop__srv__PositionService_Request__FIELDS, 1, 1},
    },
    {haptic_teleop__srv__PositionService_Request__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&haptic_teleop__msg__PosRot__EXPECTED_HASH, haptic_teleop__msg__PosRot__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = haptic_teleop__msg__PosRot__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char haptic_teleop__srv__PositionService_Response__FIELD_NAME__output[] = "output";

static rosidl_runtime_c__type_description__Field haptic_teleop__srv__PositionService_Response__FIELDS[] = {
  {
    {haptic_teleop__srv__PositionService_Response__FIELD_NAME__output, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {haptic_teleop__msg__PosRot__TYPE_NAME, 24, 24},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription haptic_teleop__srv__PositionService_Response__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {haptic_teleop__msg__PosRot__TYPE_NAME, 24, 24},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
haptic_teleop__srv__PositionService_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {haptic_teleop__srv__PositionService_Response__TYPE_NAME, 42, 42},
      {haptic_teleop__srv__PositionService_Response__FIELDS, 1, 1},
    },
    {haptic_teleop__srv__PositionService_Response__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&haptic_teleop__msg__PosRot__EXPECTED_HASH, haptic_teleop__msg__PosRot__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = haptic_teleop__msg__PosRot__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char haptic_teleop__srv__PositionService_Event__FIELD_NAME__info[] = "info";
static char haptic_teleop__srv__PositionService_Event__FIELD_NAME__request[] = "request";
static char haptic_teleop__srv__PositionService_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field haptic_teleop__srv__PositionService_Event__FIELDS[] = {
  {
    {haptic_teleop__srv__PositionService_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__srv__PositionService_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {haptic_teleop__srv__PositionService_Request__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__srv__PositionService_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {haptic_teleop__srv__PositionService_Response__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription haptic_teleop__srv__PositionService_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__msg__PosRot__TYPE_NAME, 24, 24},
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__srv__PositionService_Request__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {haptic_teleop__srv__PositionService_Response__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
haptic_teleop__srv__PositionService_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {haptic_teleop__srv__PositionService_Event__TYPE_NAME, 39, 39},
      {haptic_teleop__srv__PositionService_Event__FIELDS, 3, 3},
    },
    {haptic_teleop__srv__PositionService_Event__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&haptic_teleop__msg__PosRot__EXPECTED_HASH, haptic_teleop__msg__PosRot__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = haptic_teleop__msg__PosRot__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = haptic_teleop__srv__PositionService_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = haptic_teleop__srv__PositionService_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "PosRot input\n"
  "---\n"
  "PosRot output";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
haptic_teleop__srv__PositionService__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {haptic_teleop__srv__PositionService__TYPE_NAME, 33, 33},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 30, 30},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
haptic_teleop__srv__PositionService_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {haptic_teleop__srv__PositionService_Request__TYPE_NAME, 41, 41},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
haptic_teleop__srv__PositionService_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {haptic_teleop__srv__PositionService_Response__TYPE_NAME, 42, 42},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
haptic_teleop__srv__PositionService_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {haptic_teleop__srv__PositionService_Event__TYPE_NAME, 39, 39},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
haptic_teleop__srv__PositionService__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[7];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 7, 7};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *haptic_teleop__srv__PositionService__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *haptic_teleop__msg__PosRot__get_individual_type_description_source(NULL);
    sources[3] = *haptic_teleop__srv__PositionService_Event__get_individual_type_description_source(NULL);
    sources[4] = *haptic_teleop__srv__PositionService_Request__get_individual_type_description_source(NULL);
    sources[5] = *haptic_teleop__srv__PositionService_Response__get_individual_type_description_source(NULL);
    sources[6] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
haptic_teleop__srv__PositionService_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *haptic_teleop__srv__PositionService_Request__get_individual_type_description_source(NULL),
    sources[1] = *haptic_teleop__msg__PosRot__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
haptic_teleop__srv__PositionService_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *haptic_teleop__srv__PositionService_Response__get_individual_type_description_source(NULL),
    sources[1] = *haptic_teleop__msg__PosRot__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
haptic_teleop__srv__PositionService_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *haptic_teleop__srv__PositionService_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *haptic_teleop__msg__PosRot__get_individual_type_description_source(NULL);
    sources[3] = *haptic_teleop__srv__PositionService_Request__get_individual_type_description_source(NULL);
    sources[4] = *haptic_teleop__srv__PositionService_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
