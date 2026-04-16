// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from haptic_teleop:srv/ObjectPoseService.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "haptic_teleop/srv/detail/object_pose_service__struct.h"
#include "haptic_teleop/srv/detail/object_pose_service__type_support.h"
#include "haptic_teleop/srv/detail/object_pose_service__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace haptic_teleop
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _ObjectPoseService_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ObjectPoseService_Request_type_support_ids_t;

static const _ObjectPoseService_Request_type_support_ids_t _ObjectPoseService_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _ObjectPoseService_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ObjectPoseService_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ObjectPoseService_Request_type_support_symbol_names_t _ObjectPoseService_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, haptic_teleop, srv, ObjectPoseService_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, ObjectPoseService_Request)),
  }
};

typedef struct _ObjectPoseService_Request_type_support_data_t
{
  void * data[2];
} _ObjectPoseService_Request_type_support_data_t;

static _ObjectPoseService_Request_type_support_data_t _ObjectPoseService_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ObjectPoseService_Request_message_typesupport_map = {
  2,
  "haptic_teleop",
  &_ObjectPoseService_Request_message_typesupport_ids.typesupport_identifier[0],
  &_ObjectPoseService_Request_message_typesupport_symbol_names.symbol_name[0],
  &_ObjectPoseService_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ObjectPoseService_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ObjectPoseService_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &haptic_teleop__srv__ObjectPoseService_Request__get_type_hash,
  &haptic_teleop__srv__ObjectPoseService_Request__get_type_description,
  &haptic_teleop__srv__ObjectPoseService_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace haptic_teleop

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, haptic_teleop, srv, ObjectPoseService_Request)() {
  return &::haptic_teleop::srv::rosidl_typesupport_c::ObjectPoseService_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "haptic_teleop/srv/detail/object_pose_service__struct.h"
// already included above
// #include "haptic_teleop/srv/detail/object_pose_service__type_support.h"
// already included above
// #include "haptic_teleop/srv/detail/object_pose_service__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace haptic_teleop
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _ObjectPoseService_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ObjectPoseService_Response_type_support_ids_t;

static const _ObjectPoseService_Response_type_support_ids_t _ObjectPoseService_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _ObjectPoseService_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ObjectPoseService_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ObjectPoseService_Response_type_support_symbol_names_t _ObjectPoseService_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, haptic_teleop, srv, ObjectPoseService_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, ObjectPoseService_Response)),
  }
};

typedef struct _ObjectPoseService_Response_type_support_data_t
{
  void * data[2];
} _ObjectPoseService_Response_type_support_data_t;

static _ObjectPoseService_Response_type_support_data_t _ObjectPoseService_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ObjectPoseService_Response_message_typesupport_map = {
  2,
  "haptic_teleop",
  &_ObjectPoseService_Response_message_typesupport_ids.typesupport_identifier[0],
  &_ObjectPoseService_Response_message_typesupport_symbol_names.symbol_name[0],
  &_ObjectPoseService_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ObjectPoseService_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ObjectPoseService_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &haptic_teleop__srv__ObjectPoseService_Response__get_type_hash,
  &haptic_teleop__srv__ObjectPoseService_Response__get_type_description,
  &haptic_teleop__srv__ObjectPoseService_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace haptic_teleop

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, haptic_teleop, srv, ObjectPoseService_Response)() {
  return &::haptic_teleop::srv::rosidl_typesupport_c::ObjectPoseService_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "haptic_teleop/srv/detail/object_pose_service__struct.h"
// already included above
// #include "haptic_teleop/srv/detail/object_pose_service__type_support.h"
// already included above
// #include "haptic_teleop/srv/detail/object_pose_service__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace haptic_teleop
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _ObjectPoseService_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ObjectPoseService_Event_type_support_ids_t;

static const _ObjectPoseService_Event_type_support_ids_t _ObjectPoseService_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _ObjectPoseService_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ObjectPoseService_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ObjectPoseService_Event_type_support_symbol_names_t _ObjectPoseService_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, haptic_teleop, srv, ObjectPoseService_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, ObjectPoseService_Event)),
  }
};

typedef struct _ObjectPoseService_Event_type_support_data_t
{
  void * data[2];
} _ObjectPoseService_Event_type_support_data_t;

static _ObjectPoseService_Event_type_support_data_t _ObjectPoseService_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ObjectPoseService_Event_message_typesupport_map = {
  2,
  "haptic_teleop",
  &_ObjectPoseService_Event_message_typesupport_ids.typesupport_identifier[0],
  &_ObjectPoseService_Event_message_typesupport_symbol_names.symbol_name[0],
  &_ObjectPoseService_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ObjectPoseService_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ObjectPoseService_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &haptic_teleop__srv__ObjectPoseService_Event__get_type_hash,
  &haptic_teleop__srv__ObjectPoseService_Event__get_type_description,
  &haptic_teleop__srv__ObjectPoseService_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace haptic_teleop

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, haptic_teleop, srv, ObjectPoseService_Event)() {
  return &::haptic_teleop::srv::rosidl_typesupport_c::ObjectPoseService_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "haptic_teleop/srv/detail/object_pose_service__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace haptic_teleop
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _ObjectPoseService_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ObjectPoseService_type_support_ids_t;

static const _ObjectPoseService_type_support_ids_t _ObjectPoseService_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _ObjectPoseService_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ObjectPoseService_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ObjectPoseService_type_support_symbol_names_t _ObjectPoseService_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, haptic_teleop, srv, ObjectPoseService)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, ObjectPoseService)),
  }
};

typedef struct _ObjectPoseService_type_support_data_t
{
  void * data[2];
} _ObjectPoseService_type_support_data_t;

static _ObjectPoseService_type_support_data_t _ObjectPoseService_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ObjectPoseService_service_typesupport_map = {
  2,
  "haptic_teleop",
  &_ObjectPoseService_service_typesupport_ids.typesupport_identifier[0],
  &_ObjectPoseService_service_typesupport_symbol_names.symbol_name[0],
  &_ObjectPoseService_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t ObjectPoseService_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ObjectPoseService_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &ObjectPoseService_Request_message_type_support_handle,
  &ObjectPoseService_Response_message_type_support_handle,
  &ObjectPoseService_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    haptic_teleop,
    srv,
    ObjectPoseService
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    haptic_teleop,
    srv,
    ObjectPoseService
  ),
  &haptic_teleop__srv__ObjectPoseService__get_type_hash,
  &haptic_teleop__srv__ObjectPoseService__get_type_description,
  &haptic_teleop__srv__ObjectPoseService__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace haptic_teleop

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, haptic_teleop, srv, ObjectPoseService)() {
  return &::haptic_teleop::srv::rosidl_typesupport_c::ObjectPoseService_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
