// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from unity_robotics_ira2:srv/PositionService.idl
// generated code does not contain a copyright notice

#include "unity_robotics_ira2/srv/detail/position_service__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__srv__PositionService__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6e, 0xfa, 0xc1, 0xa0, 0x4f, 0xda, 0x9b, 0x45,
      0x78, 0x0e, 0x38, 0x0b, 0x83, 0xc5, 0x06, 0x45,
      0x81, 0x08, 0x7d, 0xe6, 0x47, 0x7f, 0x70, 0x1f,
      0x67, 0xb1, 0x9c, 0x50, 0x1d, 0x45, 0x50, 0x4b,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__srv__PositionService_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf1, 0xf3, 0x7f, 0x5e, 0x7f, 0x26, 0x1f, 0x51,
      0x06, 0xa3, 0xb1, 0x68, 0xe5, 0x26, 0x5a, 0xb7,
      0x77, 0x90, 0x90, 0x76, 0x7f, 0x33, 0x0d, 0x29,
      0xe5, 0x0b, 0x65, 0xe3, 0xb7, 0xa8, 0xdd, 0xcb,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__srv__PositionService_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x8c, 0xf8, 0x0e, 0xca, 0x57, 0x61, 0xf2, 0x69,
      0x93, 0xb4, 0x8a, 0xc6, 0xe9, 0x43, 0xd4, 0x0e,
      0xfa, 0xcb, 0x69, 0xc4, 0xab, 0x11, 0xfe, 0xbc,
      0x76, 0x50, 0xdd, 0x75, 0x9e, 0x08, 0x9f, 0x4a,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__srv__PositionService_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x4b, 0xc5, 0xb9, 0xdf, 0xbd, 0x88, 0x55, 0x3c,
      0x55, 0xf3, 0x43, 0xe1, 0x32, 0xe9, 0x9b, 0xe4,
      0x6b, 0x95, 0x81, 0x2a, 0xa9, 0x4d, 0xff, 0xac,
      0x87, 0xc3, 0x2e, 0x6a, 0x21, 0x90, 0x7f, 0xc0,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "unity_robotics_ira2/msg/detail/pos_rot__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
static const rosidl_type_hash_t unity_robotics_ira2__msg__PosRot__EXPECTED_HASH = {1, {
    0x2a, 0x2d, 0x40, 0xab, 0xb1, 0x98, 0x04, 0x86,
    0x47, 0xd6, 0x44, 0xb0, 0xf0, 0x1b, 0xd5, 0xf1,
    0x13, 0x87, 0xed, 0xa6, 0x06, 0x8a, 0xd8, 0x55,
    0xa9, 0x07, 0xc9, 0x16, 0xe8, 0x0f, 0xc0, 0xb2,
  }};
#endif

static char unity_robotics_ira2__srv__PositionService__TYPE_NAME[] = "unity_robotics_ira2/srv/PositionService";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";
static char unity_robotics_ira2__msg__PosRot__TYPE_NAME[] = "unity_robotics_ira2/msg/PosRot";
static char unity_robotics_ira2__srv__PositionService_Event__TYPE_NAME[] = "unity_robotics_ira2/srv/PositionService_Event";
static char unity_robotics_ira2__srv__PositionService_Request__TYPE_NAME[] = "unity_robotics_ira2/srv/PositionService_Request";
static char unity_robotics_ira2__srv__PositionService_Response__TYPE_NAME[] = "unity_robotics_ira2/srv/PositionService_Response";

// Define type names, field names, and default values
static char unity_robotics_ira2__srv__PositionService__FIELD_NAME__request_message[] = "request_message";
static char unity_robotics_ira2__srv__PositionService__FIELD_NAME__response_message[] = "response_message";
static char unity_robotics_ira2__srv__PositionService__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field unity_robotics_ira2__srv__PositionService__FIELDS[] = {
  {
    {unity_robotics_ira2__srv__PositionService__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {unity_robotics_ira2__srv__PositionService_Request__TYPE_NAME, 47, 47},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__srv__PositionService__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {unity_robotics_ira2__srv__PositionService_Response__TYPE_NAME, 48, 48},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__srv__PositionService__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {unity_robotics_ira2__srv__PositionService_Event__TYPE_NAME, 45, 45},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription unity_robotics_ira2__srv__PositionService__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__PosRot__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__srv__PositionService_Event__TYPE_NAME, 45, 45},
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__srv__PositionService_Request__TYPE_NAME, 47, 47},
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__srv__PositionService_Response__TYPE_NAME, 48, 48},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
unity_robotics_ira2__srv__PositionService__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {unity_robotics_ira2__srv__PositionService__TYPE_NAME, 39, 39},
      {unity_robotics_ira2__srv__PositionService__FIELDS, 3, 3},
    },
    {unity_robotics_ira2__srv__PositionService__REFERENCED_TYPE_DESCRIPTIONS, 6, 6},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&unity_robotics_ira2__msg__PosRot__EXPECTED_HASH, unity_robotics_ira2__msg__PosRot__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = unity_robotics_ira2__msg__PosRot__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = unity_robotics_ira2__srv__PositionService_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = unity_robotics_ira2__srv__PositionService_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[5].fields = unity_robotics_ira2__srv__PositionService_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char unity_robotics_ira2__srv__PositionService_Request__FIELD_NAME__input[] = "input";

static rosidl_runtime_c__type_description__Field unity_robotics_ira2__srv__PositionService_Request__FIELDS[] = {
  {
    {unity_robotics_ira2__srv__PositionService_Request__FIELD_NAME__input, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {unity_robotics_ira2__msg__PosRot__TYPE_NAME, 30, 30},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription unity_robotics_ira2__srv__PositionService_Request__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {unity_robotics_ira2__msg__PosRot__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
unity_robotics_ira2__srv__PositionService_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {unity_robotics_ira2__srv__PositionService_Request__TYPE_NAME, 47, 47},
      {unity_robotics_ira2__srv__PositionService_Request__FIELDS, 1, 1},
    },
    {unity_robotics_ira2__srv__PositionService_Request__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&unity_robotics_ira2__msg__PosRot__EXPECTED_HASH, unity_robotics_ira2__msg__PosRot__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = unity_robotics_ira2__msg__PosRot__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char unity_robotics_ira2__srv__PositionService_Response__FIELD_NAME__output[] = "output";

static rosidl_runtime_c__type_description__Field unity_robotics_ira2__srv__PositionService_Response__FIELDS[] = {
  {
    {unity_robotics_ira2__srv__PositionService_Response__FIELD_NAME__output, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {unity_robotics_ira2__msg__PosRot__TYPE_NAME, 30, 30},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription unity_robotics_ira2__srv__PositionService_Response__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {unity_robotics_ira2__msg__PosRot__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
unity_robotics_ira2__srv__PositionService_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {unity_robotics_ira2__srv__PositionService_Response__TYPE_NAME, 48, 48},
      {unity_robotics_ira2__srv__PositionService_Response__FIELDS, 1, 1},
    },
    {unity_robotics_ira2__srv__PositionService_Response__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&unity_robotics_ira2__msg__PosRot__EXPECTED_HASH, unity_robotics_ira2__msg__PosRot__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = unity_robotics_ira2__msg__PosRot__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char unity_robotics_ira2__srv__PositionService_Event__FIELD_NAME__info[] = "info";
static char unity_robotics_ira2__srv__PositionService_Event__FIELD_NAME__request[] = "request";
static char unity_robotics_ira2__srv__PositionService_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field unity_robotics_ira2__srv__PositionService_Event__FIELDS[] = {
  {
    {unity_robotics_ira2__srv__PositionService_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__srv__PositionService_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {unity_robotics_ira2__srv__PositionService_Request__TYPE_NAME, 47, 47},
    },
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__srv__PositionService_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {unity_robotics_ira2__srv__PositionService_Response__TYPE_NAME, 48, 48},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription unity_robotics_ira2__srv__PositionService_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__msg__PosRot__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__srv__PositionService_Request__TYPE_NAME, 47, 47},
    {NULL, 0, 0},
  },
  {
    {unity_robotics_ira2__srv__PositionService_Response__TYPE_NAME, 48, 48},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
unity_robotics_ira2__srv__PositionService_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {unity_robotics_ira2__srv__PositionService_Event__TYPE_NAME, 45, 45},
      {unity_robotics_ira2__srv__PositionService_Event__FIELDS, 3, 3},
    },
    {unity_robotics_ira2__srv__PositionService_Event__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&unity_robotics_ira2__msg__PosRot__EXPECTED_HASH, unity_robotics_ira2__msg__PosRot__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = unity_robotics_ira2__msg__PosRot__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = unity_robotics_ira2__srv__PositionService_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = unity_robotics_ira2__srv__PositionService_Response__get_type_description(NULL)->type_description.fields;
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
unity_robotics_ira2__srv__PositionService__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {unity_robotics_ira2__srv__PositionService__TYPE_NAME, 39, 39},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 30, 30},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
unity_robotics_ira2__srv__PositionService_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {unity_robotics_ira2__srv__PositionService_Request__TYPE_NAME, 47, 47},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
unity_robotics_ira2__srv__PositionService_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {unity_robotics_ira2__srv__PositionService_Response__TYPE_NAME, 48, 48},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
unity_robotics_ira2__srv__PositionService_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {unity_robotics_ira2__srv__PositionService_Event__TYPE_NAME, 45, 45},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__srv__PositionService__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[7];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 7, 7};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *unity_robotics_ira2__srv__PositionService__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *unity_robotics_ira2__msg__PosRot__get_individual_type_description_source(NULL);
    sources[4] = *unity_robotics_ira2__srv__PositionService_Event__get_individual_type_description_source(NULL);
    sources[5] = *unity_robotics_ira2__srv__PositionService_Request__get_individual_type_description_source(NULL);
    sources[6] = *unity_robotics_ira2__srv__PositionService_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__srv__PositionService_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *unity_robotics_ira2__srv__PositionService_Request__get_individual_type_description_source(NULL),
    sources[1] = *unity_robotics_ira2__msg__PosRot__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__srv__PositionService_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *unity_robotics_ira2__srv__PositionService_Response__get_individual_type_description_source(NULL),
    sources[1] = *unity_robotics_ira2__msg__PosRot__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__srv__PositionService_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *unity_robotics_ira2__srv__PositionService_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *unity_robotics_ira2__msg__PosRot__get_individual_type_description_source(NULL);
    sources[4] = *unity_robotics_ira2__srv__PositionService_Request__get_individual_type_description_source(NULL);
    sources[5] = *unity_robotics_ira2__srv__PositionService_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
