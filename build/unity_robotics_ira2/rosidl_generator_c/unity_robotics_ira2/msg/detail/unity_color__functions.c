// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from unity_robotics_ira2:msg/UnityColor.idl
// generated code does not contain a copyright notice
#include "unity_robotics_ira2/msg/detail/unity_color__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
unity_robotics_ira2__msg__UnityColor__init(unity_robotics_ira2__msg__UnityColor * msg)
{
  if (!msg) {
    return false;
  }
  // r
  // g
  // b
  // a
  return true;
}

void
unity_robotics_ira2__msg__UnityColor__fini(unity_robotics_ira2__msg__UnityColor * msg)
{
  if (!msg) {
    return;
  }
  // r
  // g
  // b
  // a
}

bool
unity_robotics_ira2__msg__UnityColor__are_equal(const unity_robotics_ira2__msg__UnityColor * lhs, const unity_robotics_ira2__msg__UnityColor * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // r
  if (lhs->r != rhs->r) {
    return false;
  }
  // g
  if (lhs->g != rhs->g) {
    return false;
  }
  // b
  if (lhs->b != rhs->b) {
    return false;
  }
  // a
  if (lhs->a != rhs->a) {
    return false;
  }
  return true;
}

bool
unity_robotics_ira2__msg__UnityColor__copy(
  const unity_robotics_ira2__msg__UnityColor * input,
  unity_robotics_ira2__msg__UnityColor * output)
{
  if (!input || !output) {
    return false;
  }
  // r
  output->r = input->r;
  // g
  output->g = input->g;
  // b
  output->b = input->b;
  // a
  output->a = input->a;
  return true;
}

unity_robotics_ira2__msg__UnityColor *
unity_robotics_ira2__msg__UnityColor__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__msg__UnityColor * msg = (unity_robotics_ira2__msg__UnityColor *)allocator.allocate(sizeof(unity_robotics_ira2__msg__UnityColor), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(unity_robotics_ira2__msg__UnityColor));
  bool success = unity_robotics_ira2__msg__UnityColor__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
unity_robotics_ira2__msg__UnityColor__destroy(unity_robotics_ira2__msg__UnityColor * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    unity_robotics_ira2__msg__UnityColor__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
unity_robotics_ira2__msg__UnityColor__Sequence__init(unity_robotics_ira2__msg__UnityColor__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__msg__UnityColor * data = NULL;

  if (size) {
    data = (unity_robotics_ira2__msg__UnityColor *)allocator.zero_allocate(size, sizeof(unity_robotics_ira2__msg__UnityColor), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = unity_robotics_ira2__msg__UnityColor__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        unity_robotics_ira2__msg__UnityColor__fini(&data[i - 1]);
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
unity_robotics_ira2__msg__UnityColor__Sequence__fini(unity_robotics_ira2__msg__UnityColor__Sequence * array)
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
      unity_robotics_ira2__msg__UnityColor__fini(&array->data[i]);
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

unity_robotics_ira2__msg__UnityColor__Sequence *
unity_robotics_ira2__msg__UnityColor__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unity_robotics_ira2__msg__UnityColor__Sequence * array = (unity_robotics_ira2__msg__UnityColor__Sequence *)allocator.allocate(sizeof(unity_robotics_ira2__msg__UnityColor__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = unity_robotics_ira2__msg__UnityColor__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
unity_robotics_ira2__msg__UnityColor__Sequence__destroy(unity_robotics_ira2__msg__UnityColor__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    unity_robotics_ira2__msg__UnityColor__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
unity_robotics_ira2__msg__UnityColor__Sequence__are_equal(const unity_robotics_ira2__msg__UnityColor__Sequence * lhs, const unity_robotics_ira2__msg__UnityColor__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!unity_robotics_ira2__msg__UnityColor__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
unity_robotics_ira2__msg__UnityColor__Sequence__copy(
  const unity_robotics_ira2__msg__UnityColor__Sequence * input,
  unity_robotics_ira2__msg__UnityColor__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(unity_robotics_ira2__msg__UnityColor);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    unity_robotics_ira2__msg__UnityColor * data =
      (unity_robotics_ira2__msg__UnityColor *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!unity_robotics_ira2__msg__UnityColor__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          unity_robotics_ira2__msg__UnityColor__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!unity_robotics_ira2__msg__UnityColor__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
