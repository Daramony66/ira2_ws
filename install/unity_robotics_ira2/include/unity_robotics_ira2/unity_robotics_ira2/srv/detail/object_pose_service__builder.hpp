// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from unity_robotics_ira2:srv/ObjectPoseService.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unity_robotics_ira2/srv/object_pose_service.hpp"


#ifndef UNITY_ROBOTICS_IRA2__SRV__DETAIL__OBJECT_POSE_SERVICE__BUILDER_HPP_
#define UNITY_ROBOTICS_IRA2__SRV__DETAIL__OBJECT_POSE_SERVICE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "unity_robotics_ira2/srv/detail/object_pose_service__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace unity_robotics_ira2
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
  ::unity_robotics_ira2::srv::ObjectPoseService_Request object_name(::unity_robotics_ira2::srv::ObjectPoseService_Request::_object_name_type arg)
  {
    msg_.object_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::unity_robotics_ira2::srv::ObjectPoseService_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::unity_robotics_ira2::srv::ObjectPoseService_Request>()
{
  return unity_robotics_ira2::srv::builder::Init_ObjectPoseService_Request_object_name();
}

}  // namespace unity_robotics_ira2


namespace unity_robotics_ira2
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
  ::unity_robotics_ira2::srv::ObjectPoseService_Response object_pose(::unity_robotics_ira2::srv::ObjectPoseService_Response::_object_pose_type arg)
  {
    msg_.object_pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::unity_robotics_ira2::srv::ObjectPoseService_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::unity_robotics_ira2::srv::ObjectPoseService_Response>()
{
  return unity_robotics_ira2::srv::builder::Init_ObjectPoseService_Response_object_pose();
}

}  // namespace unity_robotics_ira2


namespace unity_robotics_ira2
{

namespace srv
{

namespace builder
{

class Init_ObjectPoseService_Event_response
{
public:
  explicit Init_ObjectPoseService_Event_response(::unity_robotics_ira2::srv::ObjectPoseService_Event & msg)
  : msg_(msg)
  {}
  ::unity_robotics_ira2::srv::ObjectPoseService_Event response(::unity_robotics_ira2::srv::ObjectPoseService_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::unity_robotics_ira2::srv::ObjectPoseService_Event msg_;
};

class Init_ObjectPoseService_Event_request
{
public:
  explicit Init_ObjectPoseService_Event_request(::unity_robotics_ira2::srv::ObjectPoseService_Event & msg)
  : msg_(msg)
  {}
  Init_ObjectPoseService_Event_response request(::unity_robotics_ira2::srv::ObjectPoseService_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_ObjectPoseService_Event_response(msg_);
  }

private:
  ::unity_robotics_ira2::srv::ObjectPoseService_Event msg_;
};

class Init_ObjectPoseService_Event_info
{
public:
  Init_ObjectPoseService_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectPoseService_Event_request info(::unity_robotics_ira2::srv::ObjectPoseService_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_ObjectPoseService_Event_request(msg_);
  }

private:
  ::unity_robotics_ira2::srv::ObjectPoseService_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::unity_robotics_ira2::srv::ObjectPoseService_Event>()
{
  return unity_robotics_ira2::srv::builder::Init_ObjectPoseService_Event_info();
}

}  // namespace unity_robotics_ira2

#endif  // UNITY_ROBOTICS_IRA2__SRV__DETAIL__OBJECT_POSE_SERVICE__BUILDER_HPP_
