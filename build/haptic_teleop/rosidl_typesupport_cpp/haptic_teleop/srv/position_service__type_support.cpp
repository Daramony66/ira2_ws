// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from haptic_teleop:srv/PositionService.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "haptic_teleop/srv/detail/position_service__functions.h"
#include "haptic_teleop/srv/detail/position_service__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace haptic_teleop
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _PositionService_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PositionService_Request_type_support_ids_t;

static const _PositionService_Request_type_support_ids_t _PositionService_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _PositionService_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PositionService_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PositionService_Request_type_support_symbol_names_t _PositionService_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, haptic_teleop, srv, PositionService_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, haptic_teleop, srv, PositionService_Request)),
  }
};

typedef struct _PositionService_Request_type_support_data_t
{
  void * data[2];
} _PositionService_Request_type_support_data_t;

static _PositionService_Request_type_support_data_t _PositionService_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PositionService_Request_message_typesupport_map = {
  2,
  "haptic_teleop",
  &_PositionService_Request_message_typesupport_ids.typesupport_identifier[0],
  &_PositionService_Request_message_typesupport_symbol_names.symbol_name[0],
  &_PositionService_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t PositionService_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PositionService_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &haptic_teleop__srv__PositionService_Request__get_type_hash,
  &haptic_teleop__srv__PositionService_Request__get_type_description,
  &haptic_teleop__srv__PositionService_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace haptic_teleop

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<haptic_teleop::srv::PositionService_Request>()
{
  return &::haptic_teleop::srv::rosidl_typesupport_cpp::PositionService_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, haptic_teleop, srv, PositionService_Request)() {
  return get_message_type_support_handle<haptic_teleop::srv::PositionService_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "haptic_teleop/srv/detail/position_service__functions.h"
// already included above
// #include "haptic_teleop/srv/detail/position_service__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace haptic_teleop
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _PositionService_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PositionService_Response_type_support_ids_t;

static const _PositionService_Response_type_support_ids_t _PositionService_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _PositionService_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PositionService_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PositionService_Response_type_support_symbol_names_t _PositionService_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, haptic_teleop, srv, PositionService_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, haptic_teleop, srv, PositionService_Response)),
  }
};

typedef struct _PositionService_Response_type_support_data_t
{
  void * data[2];
} _PositionService_Response_type_support_data_t;

static _PositionService_Response_type_support_data_t _PositionService_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PositionService_Response_message_typesupport_map = {
  2,
  "haptic_teleop",
  &_PositionService_Response_message_typesupport_ids.typesupport_identifier[0],
  &_PositionService_Response_message_typesupport_symbol_names.symbol_name[0],
  &_PositionService_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t PositionService_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PositionService_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &haptic_teleop__srv__PositionService_Response__get_type_hash,
  &haptic_teleop__srv__PositionService_Response__get_type_description,
  &haptic_teleop__srv__PositionService_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace haptic_teleop

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<haptic_teleop::srv::PositionService_Response>()
{
  return &::haptic_teleop::srv::rosidl_typesupport_cpp::PositionService_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, haptic_teleop, srv, PositionService_Response)() {
  return get_message_type_support_handle<haptic_teleop::srv::PositionService_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "haptic_teleop/srv/detail/position_service__functions.h"
// already included above
// #include "haptic_teleop/srv/detail/position_service__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace haptic_teleop
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _PositionService_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PositionService_Event_type_support_ids_t;

static const _PositionService_Event_type_support_ids_t _PositionService_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _PositionService_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PositionService_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PositionService_Event_type_support_symbol_names_t _PositionService_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, haptic_teleop, srv, PositionService_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, haptic_teleop, srv, PositionService_Event)),
  }
};

typedef struct _PositionService_Event_type_support_data_t
{
  void * data[2];
} _PositionService_Event_type_support_data_t;

static _PositionService_Event_type_support_data_t _PositionService_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PositionService_Event_message_typesupport_map = {
  2,
  "haptic_teleop",
  &_PositionService_Event_message_typesupport_ids.typesupport_identifier[0],
  &_PositionService_Event_message_typesupport_symbol_names.symbol_name[0],
  &_PositionService_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t PositionService_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PositionService_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &haptic_teleop__srv__PositionService_Event__get_type_hash,
  &haptic_teleop__srv__PositionService_Event__get_type_description,
  &haptic_teleop__srv__PositionService_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace haptic_teleop

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<haptic_teleop::srv::PositionService_Event>()
{
  return &::haptic_teleop::srv::rosidl_typesupport_cpp::PositionService_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, haptic_teleop, srv, PositionService_Event)() {
  return get_message_type_support_handle<haptic_teleop::srv::PositionService_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "haptic_teleop/srv/detail/position_service__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace haptic_teleop
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _PositionService_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PositionService_type_support_ids_t;

static const _PositionService_type_support_ids_t _PositionService_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _PositionService_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PositionService_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PositionService_type_support_symbol_names_t _PositionService_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, haptic_teleop, srv, PositionService)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, haptic_teleop, srv, PositionService)),
  }
};

typedef struct _PositionService_type_support_data_t
{
  void * data[2];
} _PositionService_type_support_data_t;

static _PositionService_type_support_data_t _PositionService_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PositionService_service_typesupport_map = {
  2,
  "haptic_teleop",
  &_PositionService_service_typesupport_ids.typesupport_identifier[0],
  &_PositionService_service_typesupport_symbol_names.symbol_name[0],
  &_PositionService_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t PositionService_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PositionService_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<haptic_teleop::srv::PositionService_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<haptic_teleop::srv::PositionService_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<haptic_teleop::srv::PositionService_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<haptic_teleop::srv::PositionService>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<haptic_teleop::srv::PositionService>,
  &haptic_teleop__srv__PositionService__get_type_hash,
  &haptic_teleop__srv__PositionService__get_type_description,
  &haptic_teleop__srv__PositionService__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace haptic_teleop

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<haptic_teleop::srv::PositionService>()
{
  return &::haptic_teleop::srv::rosidl_typesupport_cpp::PositionService_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, haptic_teleop, srv, PositionService)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<haptic_teleop::srv::PositionService>();
}

#ifdef __cplusplus
}
#endif
