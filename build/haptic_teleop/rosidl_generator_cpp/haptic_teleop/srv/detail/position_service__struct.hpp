// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from haptic_teleop:srv/PositionService.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/srv/position_service.hpp"


#ifndef HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__STRUCT_HPP_
#define HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'input'
#include "haptic_teleop/msg/detail/pos_rot__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__haptic_teleop__srv__PositionService_Request __attribute__((deprecated))
#else
# define DEPRECATED__haptic_teleop__srv__PositionService_Request __declspec(deprecated)
#endif

namespace haptic_teleop
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PositionService_Request_
{
  using Type = PositionService_Request_<ContainerAllocator>;

  explicit PositionService_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : input(_init)
  {
    (void)_init;
  }

  explicit PositionService_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : input(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _input_type =
    haptic_teleop::msg::PosRot_<ContainerAllocator>;
  _input_type input;

  // setters for named parameter idiom
  Type & set__input(
    const haptic_teleop::msg::PosRot_<ContainerAllocator> & _arg)
  {
    this->input = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    haptic_teleop::srv::PositionService_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const haptic_teleop::srv::PositionService_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<haptic_teleop::srv::PositionService_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<haptic_teleop::srv::PositionService_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      haptic_teleop::srv::PositionService_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<haptic_teleop::srv::PositionService_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      haptic_teleop::srv::PositionService_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<haptic_teleop::srv::PositionService_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<haptic_teleop::srv::PositionService_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<haptic_teleop::srv::PositionService_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__haptic_teleop__srv__PositionService_Request
    std::shared_ptr<haptic_teleop::srv::PositionService_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__haptic_teleop__srv__PositionService_Request
    std::shared_ptr<haptic_teleop::srv::PositionService_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PositionService_Request_ & other) const
  {
    if (this->input != other.input) {
      return false;
    }
    return true;
  }
  bool operator!=(const PositionService_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PositionService_Request_

// alias to use template instance with default allocator
using PositionService_Request =
  haptic_teleop::srv::PositionService_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace haptic_teleop


// Include directives for member types
// Member 'output'
// already included above
// #include "haptic_teleop/msg/detail/pos_rot__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__haptic_teleop__srv__PositionService_Response __attribute__((deprecated))
#else
# define DEPRECATED__haptic_teleop__srv__PositionService_Response __declspec(deprecated)
#endif

namespace haptic_teleop
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PositionService_Response_
{
  using Type = PositionService_Response_<ContainerAllocator>;

  explicit PositionService_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : output(_init)
  {
    (void)_init;
  }

  explicit PositionService_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : output(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _output_type =
    haptic_teleop::msg::PosRot_<ContainerAllocator>;
  _output_type output;

  // setters for named parameter idiom
  Type & set__output(
    const haptic_teleop::msg::PosRot_<ContainerAllocator> & _arg)
  {
    this->output = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    haptic_teleop::srv::PositionService_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const haptic_teleop::srv::PositionService_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<haptic_teleop::srv::PositionService_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<haptic_teleop::srv::PositionService_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      haptic_teleop::srv::PositionService_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<haptic_teleop::srv::PositionService_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      haptic_teleop::srv::PositionService_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<haptic_teleop::srv::PositionService_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<haptic_teleop::srv::PositionService_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<haptic_teleop::srv::PositionService_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__haptic_teleop__srv__PositionService_Response
    std::shared_ptr<haptic_teleop::srv::PositionService_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__haptic_teleop__srv__PositionService_Response
    std::shared_ptr<haptic_teleop::srv::PositionService_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PositionService_Response_ & other) const
  {
    if (this->output != other.output) {
      return false;
    }
    return true;
  }
  bool operator!=(const PositionService_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PositionService_Response_

// alias to use template instance with default allocator
using PositionService_Response =
  haptic_teleop::srv::PositionService_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace haptic_teleop


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__haptic_teleop__srv__PositionService_Event __attribute__((deprecated))
#else
# define DEPRECATED__haptic_teleop__srv__PositionService_Event __declspec(deprecated)
#endif

namespace haptic_teleop
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PositionService_Event_
{
  using Type = PositionService_Event_<ContainerAllocator>;

  explicit PositionService_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit PositionService_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<haptic_teleop::srv::PositionService_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<haptic_teleop::srv::PositionService_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<haptic_teleop::srv::PositionService_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<haptic_teleop::srv::PositionService_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<haptic_teleop::srv::PositionService_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<haptic_teleop::srv::PositionService_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<haptic_teleop::srv::PositionService_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<haptic_teleop::srv::PositionService_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    haptic_teleop::srv::PositionService_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const haptic_teleop::srv::PositionService_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<haptic_teleop::srv::PositionService_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<haptic_teleop::srv::PositionService_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      haptic_teleop::srv::PositionService_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<haptic_teleop::srv::PositionService_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      haptic_teleop::srv::PositionService_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<haptic_teleop::srv::PositionService_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<haptic_teleop::srv::PositionService_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<haptic_teleop::srv::PositionService_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__haptic_teleop__srv__PositionService_Event
    std::shared_ptr<haptic_teleop::srv::PositionService_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__haptic_teleop__srv__PositionService_Event
    std::shared_ptr<haptic_teleop::srv::PositionService_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PositionService_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const PositionService_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PositionService_Event_

// alias to use template instance with default allocator
using PositionService_Event =
  haptic_teleop::srv::PositionService_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace haptic_teleop

namespace haptic_teleop
{

namespace srv
{

struct PositionService
{
  using Request = haptic_teleop::srv::PositionService_Request;
  using Response = haptic_teleop::srv::PositionService_Response;
  using Event = haptic_teleop::srv::PositionService_Event;
};

}  // namespace srv

}  // namespace haptic_teleop

#endif  // HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__STRUCT_HPP_
