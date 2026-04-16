// generated from rosidl_generator_c/resource/idl__type_support.h.em
// with input from haptic_teleop:srv/PositionService.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/srv/position_service.h"


#ifndef HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__TYPE_SUPPORT_H_
#define HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__TYPE_SUPPORT_H_

#include "rosidl_typesupport_interface/macros.h"

#include "haptic_teleop/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  haptic_teleop,
  srv,
  PositionService_Request
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  haptic_teleop,
  srv,
  PositionService_Response
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  haptic_teleop,
  srv,
  PositionService_Event
)(void);

#include "rosidl_runtime_c/service_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c,
  haptic_teleop,
  srv,
  PositionService
)(void);

// Forward declare the function to create a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
void *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  haptic_teleop,
  srv,
  PositionService
)(
  const rosidl_service_introspection_info_t * info,
  rcutils_allocator_t * allocator,
  const void * request_message,
  const void * response_message);

// Forward declare the function to destroy a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_haptic_teleop
bool
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  haptic_teleop,
  srv,
  PositionService
)(
  void * event_msg,
  rcutils_allocator_t * allocator);

#ifdef __cplusplus
}
#endif

#endif  // HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__TYPE_SUPPORT_H_
