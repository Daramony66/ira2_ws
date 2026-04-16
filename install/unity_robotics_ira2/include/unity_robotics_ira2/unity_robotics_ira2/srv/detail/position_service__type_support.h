// generated from rosidl_generator_c/resource/idl__type_support.h.em
// with input from unity_robotics_ira2:srv/PositionService.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unity_robotics_ira2/srv/position_service.h"


#ifndef UNITY_ROBOTICS_IRA2__SRV__DETAIL__POSITION_SERVICE__TYPE_SUPPORT_H_
#define UNITY_ROBOTICS_IRA2__SRV__DETAIL__POSITION_SERVICE__TYPE_SUPPORT_H_

#include "rosidl_typesupport_interface/macros.h"

#include "unity_robotics_ira2/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  unity_robotics_ira2,
  srv,
  PositionService_Request
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  unity_robotics_ira2,
  srv,
  PositionService_Response
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  unity_robotics_ira2,
  srv,
  PositionService_Event
)(void);

#include "rosidl_runtime_c/service_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c,
  unity_robotics_ira2,
  srv,
  PositionService
)(void);

// Forward declare the function to create a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  unity_robotics_ira2,
  srv,
  PositionService
)(
  const rosidl_service_introspection_info_t * info,
  rcutils_allocator_t * allocator,
  const void * request_message,
  const void * response_message);

// Forward declare the function to destroy a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  unity_robotics_ira2,
  srv,
  PositionService
)(
  void * event_msg,
  rcutils_allocator_t * allocator);

#ifdef __cplusplus
}
#endif

#endif  // UNITY_ROBOTICS_IRA2__SRV__DETAIL__POSITION_SERVICE__TYPE_SUPPORT_H_
