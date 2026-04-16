// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from unity_robotics_ira2:srv/PositionService.idl
// generated code does not contain a copyright notice
#include "unity_robotics_ira2/srv/detail/position_service__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `input`
#include "unity_robotics_ira2/msg/detail/pos_rot__functions.h"

bool
unity_robotics_ira2__srv__PositionService_Request__init(unity_robotics_ira2__srv__PositionService_Request * msg)
{
  if (!msg) {
    return false;
  }
  // input
  if (!unity_robotics_ira2__msg__PosRot__init(&msg->input)) {
    unity_robotics_ira2__srv__PositionService_Request__fini(msg);
    return false;
  }
  return true;
}

void
unity_robotics_ira2__srv__PositionService_Request__fini(unity_robotics_ira2__srv__PositionService_Request * msg)
{
  if (!msg) {
    return;
  }
  // input
  unity_robotics_ira2__msg__PosRot__fini(&msg->input);
}

bool
unity_robotics_ira2__srv__PositionService_Request__are_equal(const unity_robotics_ira2__srv__PositionService_Request * lhs, const unity_robotics_ira2__srv__PositionService_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // input
  if (!unity_robotics_ira2__msg__PosRot__are_equal(
      &(lhs->input), &(rhs->input)))
  {
    return false;
  }
  return true;
}

bool
unity_robotics_ira2__srv__PositionService_Request__copy(
  const unity_robotics_ira2__srv__PositionService_Request * input,
  unity_robotics_ira2__srv__PositionService_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // input
  if (!unity_robotics_ira2__msg__PosRot__copy(
      &(input->input), &(output->input)))
  {
    return false;
  }
  return true;
}

unity_robotics_ira2__srv__PositionService_Request *
unity_robotics_ira2__srv__PositionService_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__srv__PositionService_Request * msg = (unity_robotics_ira2__srv__PositionService_Request *)allocator.allocate(sizeof(unity_robotics_ira2__srv__PositionService_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(unity_robotics_ira2__srv__PositionService_Request));
  bool success = unity_robotics_ira2__srv__PositionService_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
unity_robotics_ira2__srv__PositionService_Request__destroy(unity_robotics_ira2__srv__PositionService_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    unity_robotics_ira2__srv__PositionService_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
unity_robotics_ira2__srv__PositionService_Request__Sequence__init(unity_robotics_ira2__srv__PositionService_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__srv__PositionService_Request * data = NULL;

  if (size) {
    data = (unity_robotics_ira2__srv__PositionService_Request *)allocator.zero_allocate(size, sizeof(unity_robotics_ira2__srv__PositionService_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = unity_robotics_ira2__srv__PositionService_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        unity_robotics_ira2__srv__PositionService_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
unity_robotics_ira2__srv__PositionService_Request__Sequence__fini(unity_robotics_ira2__srv__PositionService_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      unity_robotics_ira2__srv__PositionService_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

unity_robotics_ira2__srv__PositionService_Request__Sequence *
unity_robotics_ira2__srv__PositionService_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__srv__PositionService_Request__Sequence * array = (unity_robotics_ira2__srv__PositionService_Request__Sequence *)allocator.allocate(sizeof(unity_robotics_ira2__srv__PositionService_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = unity_robotics_ira2__srv__PositionService_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
unity_robotics_ira2__srv__PositionService_Request__Sequence__destroy(unity_robotics_ira2__srv__PositionService_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    unity_robotics_ira2__srv__PositionService_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
unity_robotics_ira2__srv__PositionService_Request__Sequence__are_equal(const unity_robotics_ira2__srv__PositionService_Request__Sequence * lhs, const unity_robotics_ira2__srv__PositionService_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!unity_robotics_ira2__srv__PositionService_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
unity_robotics_ira2__srv__PositionService_Request__Sequence__copy(
  const unity_robotics_ira2__srv__PositionService_Request__Sequence * input,
  unity_robotics_ira2__srv__PositionService_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(unity_robotics_ira2__srv__PositionService_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    unity_robotics_ira2__srv__PositionService_Request * data =
      (unity_robotics_ira2__srv__PositionService_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!unity_robotics_ira2__srv__PositionService_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          unity_robotics_ira2__srv__PositionService_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!unity_robotics_ira2__srv__PositionService_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `output`
// already included above
// #include "unity_robotics_ira2/msg/detail/pos_rot__functions.h"

bool
unity_robotics_ira2__srv__PositionService_Response__init(unity_robotics_ira2__srv__PositionService_Response * msg)
{
  if (!msg) {
    return false;
  }
  // output
  if (!unity_robotics_ira2__msg__PosRot__init(&msg->output)) {
    unity_robotics_ira2__srv__PositionService_Response__fini(msg);
    return false;
  }
  return true;
}

void
unity_robotics_ira2__srv__PositionService_Response__fini(unity_robotics_ira2__srv__PositionService_Response * msg)
{
  if (!msg) {
    return;
  }
  // output
  unity_robotics_ira2__msg__PosRot__fini(&msg->output);
}

bool
unity_robotics_ira2__srv__PositionService_Response__are_equal(const unity_robotics_ira2__srv__PositionService_Response * lhs, const unity_robotics_ira2__srv__PositionService_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // output
  if (!unity_robotics_ira2__msg__PosRot__are_equal(
      &(lhs->output), &(rhs->output)))
  {
    return false;
  }
  return true;
}

bool
unity_robotics_ira2__srv__PositionService_Response__copy(
  const unity_robotics_ira2__srv__PositionService_Response * input,
  unity_robotics_ira2__srv__PositionService_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // output
  if (!unity_robotics_ira2__msg__PosRot__copy(
      &(input->output), &(output->output)))
  {
    return false;
  }
  return true;
}

unity_robotics_ira2__srv__PositionService_Response *
unity_robotics_ira2__srv__PositionService_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__srv__PositionService_Response * msg = (unity_robotics_ira2__srv__PositionService_Response *)allocator.allocate(sizeof(unity_robotics_ira2__srv__PositionService_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(unity_robotics_ira2__srv__PositionService_Response));
  bool success = unity_robotics_ira2__srv__PositionService_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
unity_robotics_ira2__srv__PositionService_Response__destroy(unity_robotics_ira2__srv__PositionService_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    unity_robotics_ira2__srv__PositionService_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
unity_robotics_ira2__srv__PositionService_Response__Sequence__init(unity_robotics_ira2__srv__PositionService_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__srv__PositionService_Response * data = NULL;

  if (size) {
    data = (unity_robotics_ira2__srv__PositionService_Response *)allocator.zero_allocate(size, sizeof(unity_robotics_ira2__srv__PositionService_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = unity_robotics_ira2__srv__PositionService_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        unity_robotics_ira2__srv__PositionService_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
unity_robotics_ira2__srv__PositionService_Response__Sequence__fini(unity_robotics_ira2__srv__PositionService_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      unity_robotics_ira2__srv__PositionService_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

unity_robotics_ira2__srv__PositionService_Response__Sequence *
unity_robotics_ira2__srv__PositionService_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__srv__PositionService_Response__Sequence * array = (unity_robotics_ira2__srv__PositionService_Response__Sequence *)allocator.allocate(sizeof(unity_robotics_ira2__srv__PositionService_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = unity_robotics_ira2__srv__PositionService_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
unity_robotics_ira2__srv__PositionService_Response__Sequence__destroy(unity_robotics_ira2__srv__PositionService_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    unity_robotics_ira2__srv__PositionService_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
unity_robotics_ira2__srv__PositionService_Response__Sequence__are_equal(const unity_robotics_ira2__srv__PositionService_Response__Sequence * lhs, const unity_robotics_ira2__srv__PositionService_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!unity_robotics_ira2__srv__PositionService_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
unity_robotics_ira2__srv__PositionService_Response__Sequence__copy(
  const unity_robotics_ira2__srv__PositionService_Response__Sequence * input,
  unity_robotics_ira2__srv__PositionService_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(unity_robotics_ira2__srv__PositionService_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    unity_robotics_ira2__srv__PositionService_Response * data =
      (unity_robotics_ira2__srv__PositionService_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!unity_robotics_ira2__srv__PositionService_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          unity_robotics_ira2__srv__PositionService_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!unity_robotics_ira2__srv__PositionService_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "unity_robotics_ira2/srv/detail/position_service__functions.h"

bool
unity_robotics_ira2__srv__PositionService_Event__init(unity_robotics_ira2__srv__PositionService_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    unity_robotics_ira2__srv__PositionService_Event__fini(msg);
    return false;
  }
  // request
  if (!unity_robotics_ira2__srv__PositionService_Request__Sequence__init(&msg->request, 0)) {
    unity_robotics_ira2__srv__PositionService_Event__fini(msg);
    return false;
  }
  // response
  if (!unity_robotics_ira2__srv__PositionService_Response__Sequence__init(&msg->response, 0)) {
    unity_robotics_ira2__srv__PositionService_Event__fini(msg);
    return false;
  }
  return true;
}

void
unity_robotics_ira2__srv__PositionService_Event__fini(unity_robotics_ira2__srv__PositionService_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  unity_robotics_ira2__srv__PositionService_Request__Sequence__fini(&msg->request);
  // response
  unity_robotics_ira2__srv__PositionService_Response__Sequence__fini(&msg->response);
}

bool
unity_robotics_ira2__srv__PositionService_Event__are_equal(const unity_robotics_ira2__srv__PositionService_Event * lhs, const unity_robotics_ira2__srv__PositionService_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!unity_robotics_ira2__srv__PositionService_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!unity_robotics_ira2__srv__PositionService_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
unity_robotics_ira2__srv__PositionService_Event__copy(
  const unity_robotics_ira2__srv__PositionService_Event * input,
  unity_robotics_ira2__srv__PositionService_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!unity_robotics_ira2__srv__PositionService_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!unity_robotics_ira2__srv__PositionService_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

unity_robotics_ira2__srv__PositionService_Event *
unity_robotics_ira2__srv__PositionService_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__srv__PositionService_Event * msg = (unity_robotics_ira2__srv__PositionService_Event *)allocator.allocate(sizeof(unity_robotics_ira2__srv__PositionService_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(unity_robotics_ira2__srv__PositionService_Event));
  bool success = unity_robotics_ira2__srv__PositionService_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
unity_robotics_ira2__srv__PositionService_Event__destroy(unity_robotics_ira2__srv__PositionService_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    unity_robotics_ira2__srv__PositionService_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
unity_robotics_ira2__srv__PositionService_Event__Sequence__init(unity_robotics_ira2__srv__PositionService_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__srv__PositionService_Event * data = NULL;

  if (size) {
    data = (unity_robotics_ira2__srv__PositionService_Event *)allocator.zero_allocate(size, sizeof(unity_robotics_ira2__srv__PositionService_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = unity_robotics_ira2__srv__PositionService_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        unity_robotics_ira2__srv__PositionService_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
unity_robotics_ira2__srv__PositionService_Event__Sequence__fini(unity_robotics_ira2__srv__PositionService_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      unity_robotics_ira2__srv__PositionService_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

unity_robotics_ira2__srv__PositionService_Event__Sequence *
unity_robotics_ira2__srv__PositionService_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__srv__PositionService_Event__Sequence * array = (unity_robotics_ira2__srv__PositionService_Event__Sequence *)allocator.allocate(sizeof(unity_robotics_ira2__srv__PositionService_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = unity_robotics_ira2__srv__PositionService_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
unity_robotics_ira2__srv__PositionService_Event__Sequence__destroy(unity_robotics_ira2__srv__PositionService_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    unity_robotics_ira2__srv__PositionService_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
unity_robotics_ira2__srv__PositionService_Event__Sequence__are_equal(const unity_robotics_ira2__srv__PositionService_Event__Sequence * lhs, const unity_robotics_ira2__srv__PositionService_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!unity_robotics_ira2__srv__PositionService_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
unity_robotics_ira2__srv__PositionService_Event__Sequence__copy(
  const unity_robotics_ira2__srv__PositionService_Event__Sequence * input,
  unity_robotics_ira2__srv__PositionService_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(unity_robotics_ira2__srv__PositionService_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    unity_robotics_ira2__srv__PositionService_Event * data =
      (unity_robotics_ira2__srv__PositionService_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!unity_robotics_ira2__srv__PositionService_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          unity_robotics_ira2__srv__PositionService_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!unity_robotics_ira2__srv__PositionService_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
