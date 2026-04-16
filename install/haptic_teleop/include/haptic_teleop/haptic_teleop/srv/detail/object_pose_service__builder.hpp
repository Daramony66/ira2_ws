// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from haptic_teleop:srv/ObjectPoseService.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/srv/object_pose_service.hpp"


#ifndef HAPTIC_TELEOP__SRV__DETAIL__OBJECT_POSE_SERVICE__BUILDER_HPP_
#define HAPTIC_TELEOP__SRV__DETAIL__OBJECT_POSE_SERVICE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "haptic_teleop/srv/detail/object_pose_service__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace haptic_teleop
{

namespace srv
{

namespace builder
{

class Init_ObjectPoseService_Request_object_name
{
public:
  Init_ObjectPoseService_Request_object_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::haptic_teleop::srv::ObjectPoseService_Request object_name(::haptic_teleop::srv::ObjectPoseService_Request::_object_name_type arg)
  {
    msg_.object_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::haptic_teleop::srv::ObjectPoseService_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::haptic_teleop::srv::ObjectPoseService_Request>()
{
  return haptic_teleop::srv::builder::Init_ObjectPoseService_Request_object_name();
}

}  // namespace haptic_teleop


namespace haptic_teleop
{

namespace srv
{

namespace builder
{

class Init_ObjectPoseService_Response_object_pose
{
public:
  Init_ObjectPoseService_Response_object_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::haptic_teleop::srv::ObjectPoseService_Response object_pose(::haptic_teleop::srv::ObjectPoseService_Response::_object_pose_type arg)
  {
    msg_.object_pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::haptic_teleop::srv::ObjectPoseService_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::haptic_teleop::srv::ObjectPoseService_Response>()
{
  return haptic_teleop::srv::builder::Init_ObjectPoseService_Response_object_pose();
}

}  // namespace haptic_teleop


namespace haptic_teleop
{

namespace srv
{

namespace builder
{

class Init_ObjectPoseService_Event_response
{
public:
  explicit Init_ObjectPoseService_Event_response(::haptic_teleop::srv::ObjectPoseService_Event & msg)
  : msg_(msg)
  {}
  ::haptic_teleop::srv::ObjectPoseService_Event response(::haptic_teleop::srv::ObjectPoseService_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::haptic_teleop::srv::ObjectPoseService_Event msg_;
};

class Init_ObjectPoseService_Event_request
{
public:
  explicit Init_ObjectPoseService_Event_request(::haptic_teleop::srv::ObjectPoseService_Event & msg)
  : msg_(msg)
  {}
  Init_ObjectPoseService_Event_response request(::haptic_teleop::srv::ObjectPoseService_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_ObjectPoseService_Event_response(msg_);
  }

private:
  ::haptic_teleop::srv::ObjectPoseService_Event msg_;
};

class Init_ObjectPoseService_Event_info
{
public:
  Init_ObjectPoseService_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectPoseService_Event_request info(::haptic_teleop::srv::ObjectPoseService_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_ObjectPoseService_Event_request(msg_);
  }

private:
  ::haptic_teleop::srv::ObjectPoseService_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::haptic_teleop::srv::ObjectPoseService_Event>()
{
  return haptic_teleop::srv::builder::Init_ObjectPoseService_Event_info();
}

}  // namespace haptic_teleop

#endif  // HAPTIC_TELEOP__SRV__DETAIL__OBJECT_POSE_SERVICE__BUILDER_HPP_
