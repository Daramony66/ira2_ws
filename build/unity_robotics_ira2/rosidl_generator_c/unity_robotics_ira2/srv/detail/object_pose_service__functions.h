// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from unity_robotics_ira2:srv/ObjectPoseService.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unity_robotics_ira2/srv/object_pose_service.h"


#ifndef UNITY_ROBOTICS_IRA2__SRV__DETAIL__OBJECT_POSE_SERVICE__FUNCTIONS_H_
#define UNITY_ROBOTICS_IRA2__SRV__DETAIL__OBJECT_POSE_SERVICE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "unity_robotics_ira2/msg/rosidl_generator_c__visibility_control.h"

#include "unity_robotics_ira2/srv/detail/object_pose_service__struct.h"

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__srv__ObjectPoseService__get_type_hash(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeDescription *
unity_robotics_ira2__srv__ObjectPoseService__get_type_description(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeSource *
unity_robotics_ira2__srv__ObjectPoseService__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__srv__ObjectPoseService__get_type_description_sources(
  const rosidl_service_type_support_t * type_support);

/// Initialize srv/ObjectPoseService message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * unity_robotics_ira2__srv__ObjectPoseService_Request
 * )) before or use
 * unity_robotics_ira2__srv__ObjectPoseService_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Request__init(unity_robotics_ira2__srv__ObjectPoseService_Request * msg);

/// Finalize srv/ObjectPoseService message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Request__fini(unity_robotics_ira2__srv__ObjectPoseService_Request * msg);

/// Create srv/ObjectPoseService message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * unity_robotics_ira2__srv__ObjectPoseService_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
unity_robotics_ira2__srv__ObjectPoseService_Request *
unity_robotics_ira2__srv__ObjectPoseService_Request__create(void);

/// Destroy srv/ObjectPoseService message.
/**
 * It calls
 * unity_robotics_ira2__srv__ObjectPoseService_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Request__destroy(unity_robotics_ira2__srv__ObjectPoseService_Request * msg);

/// Check for srv/ObjectPoseService message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Request__are_equal(const unity_robotics_ira2__srv__ObjectPoseService_Request * lhs, const unity_robotics_ira2__srv__ObjectPoseService_Request * rhs);

/// Copy a srv/ObjectPoseService message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Request__copy(
  const unity_robotics_ira2__srv__ObjectPoseService_Request * input,
  unity_robotics_ira2__srv__ObjectPoseService_Request * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__srv__ObjectPoseService_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeDescription *
unity_robotics_ira2__srv__ObjectPoseService_Request__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeSource *
unity_robotics_ira2__srv__ObjectPoseService_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__srv__ObjectPoseService_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/ObjectPoseService messages.
/**
 * It allocates the memory for the number of elements and calls
 * unity_robotics_ira2__srv__ObjectPoseService_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence__init(unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence * array, size_t size);

/// Finalize array of srv/ObjectPoseService messages.
/**
 * It calls
 * unity_robotics_ira2__srv__ObjectPoseService_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence__fini(unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence * array);

/// Create array of srv/ObjectPoseService messages.
/**
 * It allocates the memory for the array and calls
 * unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence *
unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence__create(size_t size);

/// Destroy array of srv/ObjectPoseService messages.
/**
 * It calls
 * unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence__destroy(unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence * array);

/// Check for srv/ObjectPoseService message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence__are_equal(const unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence * lhs, const unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence * rhs);

/// Copy an array of srv/ObjectPoseService messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence__copy(
  const unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence * input,
  unity_robotics_ira2__srv__ObjectPoseService_Request__Sequence * output);

/// Initialize srv/ObjectPoseService message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * unity_robotics_ira2__srv__ObjectPoseService_Response
 * )) before or use
 * unity_robotics_ira2__srv__ObjectPoseService_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Response__init(unity_robotics_ira2__srv__ObjectPoseService_Response * msg);

/// Finalize srv/ObjectPoseService message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Response__fini(unity_robotics_ira2__srv__ObjectPoseService_Response * msg);

/// Create srv/ObjectPoseService message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * unity_robotics_ira2__srv__ObjectPoseService_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
unity_robotics_ira2__srv__ObjectPoseService_Response *
unity_robotics_ira2__srv__ObjectPoseService_Response__create(void);

/// Destroy srv/ObjectPoseService message.
/**
 * It calls
 * unity_robotics_ira2__srv__ObjectPoseService_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Response__destroy(unity_robotics_ira2__srv__ObjectPoseService_Response * msg);

/// Check for srv/ObjectPoseService message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Response__are_equal(const unity_robotics_ira2__srv__ObjectPoseService_Response * lhs, const unity_robotics_ira2__srv__ObjectPoseService_Response * rhs);

/// Copy a srv/ObjectPoseService message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Response__copy(
  const unity_robotics_ira2__srv__ObjectPoseService_Response * input,
  unity_robotics_ira2__srv__ObjectPoseService_Response * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__srv__ObjectPoseService_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeDescription *
unity_robotics_ira2__srv__ObjectPoseService_Response__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeSource *
unity_robotics_ira2__srv__ObjectPoseService_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__srv__ObjectPoseService_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/ObjectPoseService messages.
/**
 * It allocates the memory for the number of elements and calls
 * unity_robotics_ira2__srv__ObjectPoseService_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence__init(unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence * array, size_t size);

/// Finalize array of srv/ObjectPoseService messages.
/**
 * It calls
 * unity_robotics_ira2__srv__ObjectPoseService_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence__fini(unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence * array);

/// Create array of srv/ObjectPoseService messages.
/**
 * It allocates the memory for the array and calls
 * unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence *
unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence__create(size_t size);

/// Destroy array of srv/ObjectPoseService messages.
/**
 * It calls
 * unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence__destroy(unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence * array);

/// Check for srv/ObjectPoseService message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence__are_equal(const unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence * lhs, const unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence * rhs);

/// Copy an array of srv/ObjectPoseService messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence__copy(
  const unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence * input,
  unity_robotics_ira2__srv__ObjectPoseService_Response__Sequence * output);

/// Initialize srv/ObjectPoseService message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * unity_robotics_ira2__srv__ObjectPoseService_Event
 * )) before or use
 * unity_robotics_ira2__srv__ObjectPoseService_Event__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Event__init(unity_robotics_ira2__srv__ObjectPoseService_Event * msg);

/// Finalize srv/ObjectPoseService message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Event__fini(unity_robotics_ira2__srv__ObjectPoseService_Event * msg);

/// Create srv/ObjectPoseService message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * unity_robotics_ira2__srv__ObjectPoseService_Event__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
unity_robotics_ira2__srv__ObjectPoseService_Event *
unity_robotics_ira2__srv__ObjectPoseService_Event__create(void);

/// Destroy srv/ObjectPoseService message.
/**
 * It calls
 * unity_robotics_ira2__srv__ObjectPoseService_Event__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Event__destroy(unity_robotics_ira2__srv__ObjectPoseService_Event * msg);

/// Check for srv/ObjectPoseService message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Event__are_equal(const unity_robotics_ira2__srv__ObjectPoseService_Event * lhs, const unity_robotics_ira2__srv__ObjectPoseService_Event * rhs);

/// Copy a srv/ObjectPoseService message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Event__copy(
  const unity_robotics_ira2__srv__ObjectPoseService_Event * input,
  unity_robotics_ira2__srv__ObjectPoseService_Event * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_type_hash_t *
unity_robotics_ira2__srv__ObjectPoseService_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeDescription *
unity_robotics_ira2__srv__ObjectPoseService_Event__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeSource *
unity_robotics_ira2__srv__ObjectPoseService_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
const rosidl_runtime_c__type_description__TypeSource__Sequence *
unity_robotics_ira2__srv__ObjectPoseService_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/ObjectPoseService messages.
/**
 * It allocates the memory for the number of elements and calls
 * unity_robotics_ira2__srv__ObjectPoseService_Event__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence__init(unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence * array, size_t size);

/// Finalize array of srv/ObjectPoseService messages.
/**
 * It calls
 * unity_robotics_ira2__srv__ObjectPoseService_Event__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence__fini(unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence * array);

/// Create array of srv/ObjectPoseService messages.
/**
 * It allocates the memory for the array and calls
 * unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence *
unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence__create(size_t size);

/// Destroy array of srv/ObjectPoseService messages.
/**
 * It calls
 * unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
void
unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence__destroy(unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence * array);

/// Check for srv/ObjectPoseService message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence__are_equal(const unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence * lhs, const unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence * rhs);

/// Copy an array of srv/ObjectPoseService messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_unity_robotics_ira2
bool
unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence__copy(
  const unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence * input,
  unity_robotics_ira2__srv__ObjectPoseService_Event__Sequence * output);
#ifdef __cplusplus
}
#endif

#endif  // UNITY_ROBOTICS_IRA2__SRV__DETAIL__OBJECT_POSE_SERVICE__FUNCTIONS_H_
