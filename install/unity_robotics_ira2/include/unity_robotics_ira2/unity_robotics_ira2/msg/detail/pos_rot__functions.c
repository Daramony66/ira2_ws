// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from unity_robotics_ira2:msg/PosRot.idl
// generated code does not contain a copyright notice
#include "unity_robotics_ira2/msg/detail/pos_rot__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
unity_robotics_ira2__msg__PosRot__init(unity_robotics_ira2__msg__PosRot * msg)
{
  if (!msg) {
    return false;
  }
  // pos_x
  // pos_y
  // pos_z
  // rot_x
  // rot_y
  // rot_z
  // rot_w
  return true;
}

void
unity_robotics_ira2__msg__PosRot__fini(unity_robotics_ira2__msg__PosRot * msg)
{
  if (!msg) {
    return;
  }
  // pos_x
  // pos_y
  // pos_z
  // rot_x
  // rot_y
  // rot_z
  // rot_w
}

bool
unity_robotics_ira2__msg__PosRot__are_equal(const unity_robotics_ira2__msg__PosRot * lhs, const unity_robotics_ira2__msg__PosRot * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pos_x
  if (lhs->pos_x != rhs->pos_x) {
    return false;
  }
  // pos_y
  if (lhs->pos_y != rhs->pos_y) {
    return false;
  }
  // pos_z
  if (lhs->pos_z != rhs->pos_z) {
    return false;
  }
  // rot_x
  if (lhs->rot_x != rhs->rot_x) {
    return false;
  }
  // rot_y
  if (lhs->rot_y != rhs->rot_y) {
    return false;
  }
  // rot_z
  if (lhs->rot_z != rhs->rot_z) {
    return false;
  }
  // rot_w
  if (lhs->rot_w != rhs->rot_w) {
    return false;
  }
  return true;
}

bool
unity_robotics_ira2__msg__PosRot__copy(
  const unity_robotics_ira2__msg__PosRot * input,
  unity_robotics_ira2__msg__PosRot * output)
{
  if (!input || !output) {
    return false;
  }
  // pos_x
  output->pos_x = input->pos_x;
  // pos_y
  output->pos_y = input->pos_y;
  // pos_z
  output->pos_z = input->pos_z;
  // rot_x
  output->rot_x = input->rot_x;
  // rot_y
  output->rot_y = input->rot_y;
  // rot_z
  output->rot_z = input->rot_z;
  // rot_w
  output->rot_w = input->rot_w;
  return true;
}

unity_robotics_ira2__msg__PosRot *
unity_robotics_ira2__msg__PosRot__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__msg__PosRot * msg = (unity_robotics_ira2__msg__PosRot *)allocator.allocate(sizeof(unity_robotics_ira2__msg__PosRot), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(unity_robotics_ira2__msg__PosRot));
  bool success = unity_robotics_ira2__msg__PosRot__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
unity_robotics_ira2__msg__PosRot__destroy(unity_robotics_ira2__msg__PosRot * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    unity_robotics_ira2__msg__PosRot__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
unity_robotics_ira2__msg__PosRot__Sequence__init(unity_robotics_ira2__msg__PosRot__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__msg__PosRot * data = NULL;

  if (size) {
    data = (unity_robotics_ira2__msg__PosRot *)allocator.zero_allocate(size, sizeof(unity_robotics_ira2__msg__PosRot), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = unity_robotics_ira2__msg__PosRot__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        unity_robotics_ira2__msg__PosRot__fini(&data[i - 1]);
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
unity_robotics_ira2__msg__PosRot__Sequence__fini(unity_robotics_ira2__msg__PosRot__Sequence * array)
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
      unity_robotics_ira2__msg__PosRot__fini(&array->data[i]);
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

unity_robotics_ira2__msg__PosRot__Sequence *
unity_robotics_ira2__msg__PosRot__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__msg__PosRot__Sequence * array = (unity_robotics_ira2__msg__PosRot__Sequence *)allocator.allocate(sizeof(unity_robotics_ira2__msg__PosRot__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = unity_robotics_ira2__msg__PosRot__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
unity_robotics_ira2__msg__PosRot__Sequence__destroy(unity_robotics_ira2__msg__PosRot__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    unity_robotics_ira2__msg__PosRot__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
unity_robotics_ira2__msg__PosRot__Sequence__are_equal(const unity_robotics_ira2__msg__PosRot__Sequence * lhs, const unity_robotics_ira2__msg__PosRot__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!unity_robotics_ira2__msg__PosRot__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
unity_robotics_ira2__msg__PosRot__Sequence__copy(
  const unity_robotics_ira2__msg__PosRot__Sequence * input,
  unity_robotics_ira2__msg__PosRot__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(unity_robotics_ira2__msg__PosRot);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    unity_robotics_ira2__msg__PosRot * data =
      (unity_robotics_ira2__msg__PosRot *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!unity_robotics_ira2__msg__PosRot__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          unity_robotics_ira2__msg__PosRot__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!unity_robotics_ira2__msg__PosRot__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
