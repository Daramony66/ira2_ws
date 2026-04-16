// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from haptic_teleop:srv/PositionService.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/srv/position_service.h"


#ifndef HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__STRUCT_H_
#define HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'input'
#include "haptic_teleop/msg/detail/pos_rot__struct.h"

/// Struct defined in srv/PositionService in the package haptic_teleop.
typedef struct haptic_teleop__srv__PositionService_Request
{
  haptic_teleop__msg__PosRot input;
} haptic_teleop__srv__PositionService_Request;

// Struct for a sequence of haptic_teleop__srv__PositionService_Request.
typedef struct haptic_teleop__srv__PositionService_Request__Sequence
{
  haptic_teleop__srv__PositionService_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} haptic_teleop__srv__PositionService_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'output'
// already included above
// #include "haptic_teleop/msg/detail/pos_rot__struct.h"

/// Struct defined in srv/PositionService in the package haptic_teleop.
typedef struct haptic_teleop__srv__PositionService_Response
{
  haptic_teleop__msg__PosRot output;
} haptic_teleop__srv__PositionService_Response;

// Struct for a sequence of haptic_teleop__srv__PositionService_Response.
typedef struct haptic_teleop__srv__PositionService_Response__Sequence
{
  haptic_teleop__srv__PositionService_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} haptic_teleop__srv__PositionService_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  haptic_teleop__srv__PositionService_Event__request__MAX_SIZE = 1
};
// response
enum
{
  haptic_teleop__srv__PositionService_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/PositionService in the package haptic_teleop.
typedef struct haptic_teleop__srv__PositionService_Event
{
  service_msgs__msg__ServiceEventInfo info;
  haptic_teleop__srv__PositionService_Request__Sequence request;
  haptic_teleop__srv__PositionService_Response__Sequence response;
} haptic_teleop__srv__PositionService_Event;

// Struct for a sequence of haptic_teleop__srv__PositionService_Event.
typedef struct haptic_teleop__srv__PositionService_Event__Sequence
{
  haptic_teleop__srv__PositionService_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} haptic_teleop__srv__PositionService_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__STRUCT_H_
