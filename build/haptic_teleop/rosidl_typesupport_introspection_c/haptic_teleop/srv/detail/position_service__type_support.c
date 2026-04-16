// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from haptic_teleop:srv/PositionService.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "haptic_teleop/srv/detail/position_service__rosidl_typesupport_introspection_c.h"
#include "haptic_teleop/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "haptic_teleop/srv/detail/position_service__functions.h"
#include "haptic_teleop/srv/detail/position_service__struct.h"


// Include directives for member types
// Member `input`
#include "haptic_teleop/msg/pos_rot.h"
// Member `input`
#include "haptic_teleop/msg/detail/pos_rot__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  haptic_teleop__srv__PositionService_Request__init(message_memory);
}

void haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_fini_function(void * message_memory)
{
  haptic_teleop__srv__PositionService_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_member_array[1] = {
  {
    "input",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(haptic_teleop__srv__PositionService_Request, input),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_members = {
  "haptic_teleop__srv",  // message namespace
  "PositionService_Request",  // message name
  1,  // number of fields
  sizeof(haptic_teleop__srv__PositionService_Request),
  false,  // has_any_key_member_
  haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_member_array,  // message members
  haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle = {
  0,
  &haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_members,
  get_message_typesupport_handle_function,
  &haptic_teleop__srv__PositionService_Request__get_type_hash,
  &haptic_teleop__srv__PositionService_Request__get_type_description,
  &haptic_teleop__srv__PositionService_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_haptic_teleop
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Request)() {
  haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, msg, PosRot)();
  if (!haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle.typesupport_identifier) {
    haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "haptic_teleop/srv/detail/position_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "haptic_teleop/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "haptic_teleop/srv/detail/position_service__functions.h"
// already included above
// #include "haptic_teleop/srv/detail/position_service__struct.h"


// Include directives for member types
// Member `output`
// already included above
// #include "haptic_teleop/msg/pos_rot.h"
// Member `output`
// already included above
// #include "haptic_teleop/msg/detail/pos_rot__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  haptic_teleop__srv__PositionService_Response__init(message_memory);
}

void haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_fini_function(void * message_memory)
{
  haptic_teleop__srv__PositionService_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_member_array[1] = {
  {
    "output",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(haptic_teleop__srv__PositionService_Response, output),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_members = {
  "haptic_teleop__srv",  // message namespace
  "PositionService_Response",  // message name
  1,  // number of fields
  sizeof(haptic_teleop__srv__PositionService_Response),
  false,  // has_any_key_member_
  haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_member_array,  // message members
  haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle = {
  0,
  &haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_members,
  get_message_typesupport_handle_function,
  &haptic_teleop__srv__PositionService_Response__get_type_hash,
  &haptic_teleop__srv__PositionService_Response__get_type_description,
  &haptic_teleop__srv__PositionService_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_haptic_teleop
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Response)() {
  haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, msg, PosRot)();
  if (!haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle.typesupport_identifier) {
    haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "haptic_teleop/srv/detail/position_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "haptic_teleop/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "haptic_teleop/srv/detail/position_service__functions.h"
// already included above
// #include "haptic_teleop/srv/detail/position_service__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "haptic_teleop/srv/position_service.h"
// Member `request`
// Member `response`
// already included above
// #include "haptic_teleop/srv/detail/position_service__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  haptic_teleop__srv__PositionService_Event__init(message_memory);
}

void haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_fini_function(void * message_memory)
{
  haptic_teleop__srv__PositionService_Event__fini(message_memory);
}

size_t haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__size_function__PositionService_Event__request(
  const void * untyped_member)
{
  const haptic_teleop__srv__PositionService_Request__Sequence * member =
    (const haptic_teleop__srv__PositionService_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__request(
  const void * untyped_member, size_t index)
{
  const haptic_teleop__srv__PositionService_Request__Sequence * member =
    (const haptic_teleop__srv__PositionService_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__request(
  void * untyped_member, size_t index)
{
  haptic_teleop__srv__PositionService_Request__Sequence * member =
    (haptic_teleop__srv__PositionService_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__fetch_function__PositionService_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const haptic_teleop__srv__PositionService_Request * item =
    ((const haptic_teleop__srv__PositionService_Request *)
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__request(untyped_member, index));
  haptic_teleop__srv__PositionService_Request * value =
    (haptic_teleop__srv__PositionService_Request *)(untyped_value);
  *value = *item;
}

void haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__assign_function__PositionService_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  haptic_teleop__srv__PositionService_Request * item =
    ((haptic_teleop__srv__PositionService_Request *)
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__request(untyped_member, index));
  const haptic_teleop__srv__PositionService_Request * value =
    (const haptic_teleop__srv__PositionService_Request *)(untyped_value);
  *item = *value;
}

bool haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__resize_function__PositionService_Event__request(
  void * untyped_member, size_t size)
{
  haptic_teleop__srv__PositionService_Request__Sequence * member =
    (haptic_teleop__srv__PositionService_Request__Sequence *)(untyped_member);
  haptic_teleop__srv__PositionService_Request__Sequence__fini(member);
  return haptic_teleop__srv__PositionService_Request__Sequence__init(member, size);
}

size_t haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__size_function__PositionService_Event__response(
  const void * untyped_member)
{
  const haptic_teleop__srv__PositionService_Response__Sequence * member =
    (const haptic_teleop__srv__PositionService_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__response(
  const void * untyped_member, size_t index)
{
  const haptic_teleop__srv__PositionService_Response__Sequence * member =
    (const haptic_teleop__srv__PositionService_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__response(
  void * untyped_member, size_t index)
{
  haptic_teleop__srv__PositionService_Response__Sequence * member =
    (haptic_teleop__srv__PositionService_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__fetch_function__PositionService_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const haptic_teleop__srv__PositionService_Response * item =
    ((const haptic_teleop__srv__PositionService_Response *)
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__response(untyped_member, index));
  haptic_teleop__srv__PositionService_Response * value =
    (haptic_teleop__srv__PositionService_Response *)(untyped_value);
  *value = *item;
}

void haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__assign_function__PositionService_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  haptic_teleop__srv__PositionService_Response * item =
    ((haptic_teleop__srv__PositionService_Response *)
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__response(untyped_member, index));
  const haptic_teleop__srv__PositionService_Response * value =
    (const haptic_teleop__srv__PositionService_Response *)(untyped_value);
  *item = *value;
}

bool haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__resize_function__PositionService_Event__response(
  void * untyped_member, size_t size)
{
  haptic_teleop__srv__PositionService_Response__Sequence * member =
    (haptic_teleop__srv__PositionService_Response__Sequence *)(untyped_member);
  haptic_teleop__srv__PositionService_Response__Sequence__fini(member);
  return haptic_teleop__srv__PositionService_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(haptic_teleop__srv__PositionService_Event, info),  // bytes offset in struct
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
    offsetof(haptic_teleop__srv__PositionService_Event, request),  // bytes offset in struct
    NULL,  // default value
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__size_function__PositionService_Event__request,  // size() function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__request,  // get_const(index) function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__request,  // get(index) function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__fetch_function__PositionService_Event__request,  // fetch(index, &value) function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__assign_function__PositionService_Event__request,  // assign(index, value) function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__resize_function__PositionService_Event__request  // resize(index) function pointer
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
    offsetof(haptic_teleop__srv__PositionService_Event, response),  // bytes offset in struct
    NULL,  // default value
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__size_function__PositionService_Event__response,  // size() function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_const_function__PositionService_Event__response,  // get_const(index) function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__get_function__PositionService_Event__response,  // get(index) function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__fetch_function__PositionService_Event__response,  // fetch(index, &value) function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__assign_function__PositionService_Event__response,  // assign(index, value) function pointer
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__resize_function__PositionService_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_members = {
  "haptic_teleop__srv",  // message namespace
  "PositionService_Event",  // message name
  3,  // number of fields
  sizeof(haptic_teleop__srv__PositionService_Event),
  false,  // has_any_key_member_
  haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array,  // message members
  haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle = {
  0,
  &haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_members,
  get_message_typesupport_handle_function,
  &haptic_teleop__srv__PositionService_Event__get_type_hash,
  &haptic_teleop__srv__PositionService_Event__get_type_description,
  &haptic_teleop__srv__PositionService_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_haptic_teleop
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Event)() {
  haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Request)();
  haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Response)();
  if (!haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle.typesupport_identifier) {
    haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "haptic_teleop/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "haptic_teleop/srv/detail/position_service__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_members = {
  "haptic_teleop__srv",  // service namespace
  "PositionService",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle,
  NULL,  // response message
  // haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle
  NULL  // event_message
  // haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle
};


static rosidl_service_type_support_t haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle = {
  0,
  &haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_members,
  get_service_typesupport_handle_function,
  &haptic_teleop__srv__PositionService_Request__rosidl_typesupport_introspection_c__PositionService_Request_message_type_support_handle,
  &haptic_teleop__srv__PositionService_Response__rosidl_typesupport_introspection_c__PositionService_Response_message_type_support_handle,
  &haptic_teleop__srv__PositionService_Event__rosidl_typesupport_introspection_c__PositionService_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    haptic_teleop,
    srv,
    PositionService
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    haptic_teleop,
    srv,
    PositionService
  ),
  &haptic_teleop__srv__PositionService__get_type_hash,
  &haptic_teleop__srv__PositionService__get_type_description,
  &haptic_teleop__srv__PositionService__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_haptic_teleop
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService)(void) {
  if (!haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle.typesupport_identifier) {
    haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, haptic_teleop, srv, PositionService_Event)()->data;
  }

  return &haptic_teleop__srv__detail__position_service__rosidl_typesupport_introspection_c__PositionService_service_type_support_handle;
}
