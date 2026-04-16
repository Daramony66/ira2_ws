// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from unity_robotics_ira2:srv/PositionService.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "unity_robotics_ira2/srv/detail/position_service__rosidl_typesupport_introspection_c.h"
#include "unity_robotics_ira2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "unity_robotics_ira2/srv/detail/position_service__functions.h"
#include "unity_robotics_ira2/srv/detail/position_service__struct.h"


// Include directives for member types
// Member `input`
#include "unity_robotics_ira2/msg/pos_rot.h"
// Member `input`
#include "unity_robotics_ira2/msg/detail/pos_rot__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  unity_robotics_ira2__srv__PositionService_Request__init(message_memory);
}

void unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_fini_function(void * message_memory)
{
  unity_robotics_ira2__srv__PositionService_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_member_array[1] = {
  {
    "input",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(unity_robotics_ira2__srv__PositionService_Request, input),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_members = {
  "unity_robotics_ira2__srv",  // message namespace
  "PositionService_Request",  // message name
  1,  // number of fields
  sizeof(unity_robotics_ira2__srv__PositionService_Request),
  false,  // has_any_key_member_
  unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_member_array,  // message members
  unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle = {
  0,
  &unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_members,
  get_message_typesupport_handle_function,
  &unity_robotics_ira2__srv__PositionService_Request__get_type_hash,
  &unity_robotics_ira2__srv__PositionService_Request__get_type_description,
  &unity_robotics_ira2__srv__PositionService_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_unity_robotics_ira2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Request)() {
  unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, msg, PosRot)();
  if (!unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle.typesupport_identifier) {
    unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "unity_robotics_ira2/srv/detail/position_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "unity_robotics_ira2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "unity_robotics_ira2/srv/detail/position_service__functions.h"
// already included above
// #include "unity_robotics_ira2/srv/detail/position_service__struct.h"


// Include directives for member types
// Member `output`
// already included above
// #include "unity_robotics_ira2/msg/pos_rot.h"
// Member `output`
// already included above
// #include "unity_robotics_ira2/msg/detail/pos_rot__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  unity_robotics_ira2__srv__PositionService_Response__init(message_memory);
}

void unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_fini_function(void * message_memory)
{
  unity_robotics_ira2__srv__PositionService_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_member_array[1] = {
  {
    "output",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(unity_robotics_ira2__srv__PositionService_Response, output),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_members = {
  "unity_robotics_ira2__srv",  // message namespace
  "PositionService_Response",  // message name
  1,  // number of fields
  sizeof(unity_robotics_ira2__srv__PositionService_Response),
  false,  // has_any_key_member_
  unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_member_array,  // message members
  unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle = {
  0,
  &unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_members,
  get_message_typesupport_handle_function,
  &unity_robotics_ira2__srv__PositionService_Response__get_type_hash,
  &unity_robotics_ira2__srv__PositionService_Response__get_type_description,
  &unity_robotics_ira2__srv__PositionService_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_unity_robotics_ira2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Response)() {
  unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, msg, PosRot)();
  if (!unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle.typesupport_identifier) {
    unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "unity_robotics_ira2/srv/detail/position_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "unity_robotics_ira2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "unity_robotics_ira2/srv/detail/position_service__functions.h"
// already included above
// #include "unity_robotics_ira2/srv/detail/position_service__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "unity_robotics_ira2/srv/position_service.h"
// Member `request`
// Member `response`
// already included above
// #include "unity_robotics_ira2/srv/detail/position_service__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  unity_robotics_ira2__srv__PositionService_Event__init(message_memory);
}

void unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_fini_function(void * message_memory)
{
  unity_robotics_ira2__srv__PositionService_Event__fini(message_memory);
}

size_t unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__size_function__PositionService_Event__request(
  const void * untyped_member)
{
  const unity_robotics_ira2__srv__PositionService_Request__Sequence * member =
    (const unity_robotics_ira2__srv__PositionService_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__request(
  const void * untyped_member, size_t index)
{
  const unity_robotics_ira2__srv__PositionService_Request__Sequence * member =
    (const unity_robotics_ira2__srv__PositionService_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__request(
  void * untyped_member, size_t index)
{
  unity_robotics_ira2__srv__PositionService_Request__Sequence * member =
    (unity_robotics_ira2__srv__PositionService_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__fetch_function__PositionService_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const unity_robotics_ira2__srv__PositionService_Request * item =
    ((const unity_robotics_ira2__srv__PositionService_Request *)
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__request(untyped_member, index));
  unity_robotics_ira2__srv__PositionService_Request * value =
    (unity_robotics_ira2__srv__PositionService_Request *)(untyped_value);
  *value = *item;
}

void unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__assign_function__PositionService_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  unity_robotics_ira2__srv__PositionService_Request * item =
    ((unity_robotics_ira2__srv__PositionService_Request *)
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__request(untyped_member, index));
  const unity_robotics_ira2__srv__PositionService_Request * value =
    (const unity_robotics_ira2__srv__PositionService_Request *)(untyped_value);
  *item = *value;
}

bool unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__resize_function__PositionService_Event__request(
  void * untyped_member, size_t size)
{
  unity_robotics_ira2__srv__PositionService_Request__Sequence * member =
    (unity_robotics_ira2__srv__PositionService_Request__Sequence *)(untyped_member);
  unity_robotics_ira2__srv__PositionService_Request__Sequence__fini(member);
  return unity_robotics_ira2__srv__PositionService_Request__Sequence__init(member, size);
}

size_t unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__size_function__PositionService_Event__response(
  const void * untyped_member)
{
  const unity_robotics_ira2__srv__PositionService_Response__Sequence * member =
    (const unity_robotics_ira2__srv__PositionService_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__response(
  const void * untyped_member, size_t index)
{
  const unity_robotics_ira2__srv__PositionService_Response__Sequence * member =
    (const unity_robotics_ira2__srv__PositionService_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__response(
  void * untyped_member, size_t index)
{
  unity_robotics_ira2__srv__PositionService_Response__Sequence * member =
    (unity_robotics_ira2__srv__PositionService_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__fetch_function__PositionService_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const unity_robotics_ira2__srv__PositionService_Response * item =
    ((const unity_robotics_ira2__srv__PositionService_Response *)
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__response(untyped_member, index));
  unity_robotics_ira2__srv__PositionService_Response * value =
    (unity_robotics_ira2__srv__PositionService_Response *)(untyped_value);
  *value = *item;
}

void unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__assign_function__PositionService_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  unity_robotics_ira2__srv__PositionService_Response * item =
    ((unity_robotics_ira2__srv__PositionService_Response *)
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__response(untyped_member, index));
  const unity_robotics_ira2__srv__PositionService_Response * value =
    (const unity_robotics_ira2__srv__PositionService_Response *)(untyped_value);
  *item = *value;
}

bool unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__resize_function__PositionService_Event__response(
  void * untyped_member, size_t size)
{
  unity_robotics_ira2__srv__PositionService_Response__Sequence * member =
    (unity_robotics_ira2__srv__PositionService_Response__Sequence *)(untyped_member);
  unity_robotics_ira2__srv__PositionService_Response__Sequence__fini(member);
  return unity_robotics_ira2__srv__PositionService_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(unity_robotics_ira2__srv__PositionService_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(unity_robotics_ira2__srv__PositionService_Event, request),  // bytes offset in struct
    NULL,  // default value
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__size_function__PositionService_Event__request,  // size() function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__request,  // get_const(index) function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__request,  // get(index) function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__fetch_function__PositionService_Event__request,  // fetch(index, &value) function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__assign_function__PositionService_Event__request,  // assign(index, value) function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__resize_function__PositionService_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(unity_robotics_ira2__srv__PositionService_Event, response),  // bytes offset in struct
    NULL,  // default value
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__size_function__PositionService_Event__response,  // size() function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__response,  // get_const(index) function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__response,  // get(index) function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__fetch_function__PositionService_Event__response,  // fetch(index, &value) function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__assign_function__PositionService_Event__response,  // assign(index, value) function pointer
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__resize_function__PositionService_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_members = {
  "unity_robotics_ira2__srv",  // message namespace
  "PositionService_Event",  // message name
  3,  // number of fields
  sizeof(unity_robotics_ira2__srv__PositionService_Event),
  false,  // has_any_key_member_
  unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array,  // message members
  unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle = {
  0,
  &unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_members,
  get_message_typesupport_handle_function,
  &unity_robotics_ira2__srv__PositionService_Event__get_type_hash,
  &unity_robotics_ira2__srv__PositionService_Event__get_type_description,
  &unity_robotics_ira2__srv__PositionService_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_unity_robotics_ira2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Event)() {
  unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Request)();
  unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Response)();
  if (!unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle.typesupport_identifier) {
    unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "unity_robotics_ira2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "unity_robotics_ira2/srv/detail/position_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_members = {
  "unity_robotics_ira2__srv",  // service namespace
  "PositionService",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle,
  NULL,  // response message
  // unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle
  NULL  // event_message
  // unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle
};


static rosidl_service_type_support_t unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle = {
  0,
  &unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_members,
  get_service_typesupport_handle_function,
  &unity_robotics_ira2__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle,
  &unity_robotics_ira2__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle,
  &unity_robotics_ira2__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    unity_robotics_ira2,
    srv,
    PositionService
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    unity_robotics_ira2,
    srv,
    PositionService
  ),
  &unity_robotics_ira2__srv__PositionService__get_type_hash,
  &unity_robotics_ira2__srv__PositionService__get_type_description,
  &unity_robotics_ira2__srv__PositionService__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_unity_robotics_ira2
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService)(void) {
  if (!unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle.typesupport_identifier) {
    unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unity_robotics_ira2, srv, PositionService_Event)()->data;
  }

  return &unity_robotics_ira2__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle;
}
