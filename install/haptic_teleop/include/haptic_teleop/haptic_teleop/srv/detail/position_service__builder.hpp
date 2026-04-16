// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from haptic_teleop:srv/PositionService.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/srv/position_service.hpp"


#ifndef HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__BUILDER_HPP_
#define HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "haptic_teleop/srv/detail/position_service__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace haptic_teleop
{

namespace srv
{

namespace builder
{

class Init_PositionService_Request_input
{
public:
  Init_PositionService_Request_input()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::haptic_teleop::srv::PositionService_Request input(::haptic_teleop::srv::PositionService_Request::_input_type arg)
  {
    msg_.input = std::move(arg);
    return std::move(msg_);
  }

private:
  ::haptic_teleop::srv::PositionService_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::haptic_teleop::srv::PositionService_Request>()
{
  return haptic_teleop::srv::builder::Init_PositionService_Request_input();
}

}  // namespace haptic_teleop


namespace haptic_teleop
{

namespace srv
{

namespace builder
{

class Init_PositionService_Response_output
{
public:
  Init_PositionService_Response_output()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::haptic_teleop::srv::PositionService_Response output(::haptic_teleop::srv::PositionService_Response::_output_type arg)
  {
    msg_.output = std::move(arg);
    return std::move(msg_);
  }

private:
  ::haptic_teleop::srv::PositionService_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::haptic_teleop::srv::PositionService_Response>()
{
  return haptic_teleop::srv::builder::Init_PositionService_Response_output();
}

}  // namespace haptic_teleop


namespace haptic_teleop
{

namespace srv
{

namespace builder
{

class Init_PositionService_Event_response
{
public:
  explicit Init_PositionService_Event_response(::haptic_teleop::srv::PositionService_Event & msg)
  : msg_(msg)
  {}
  ::haptic_teleop::srv::PositionService_Event response(::haptic_teleop::srv::PositionService_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::haptic_teleop::srv::PositionService_Event msg_;
};

class Init_PositionService_Event_request
{
public:
  explicit Init_PositionService_Event_request(::haptic_teleop::srv::PositionService_Event & msg)
  : msg_(msg)
  {}
  Init_PositionService_Event_response request(::haptic_teleop::srv::PositionService_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_PositionService_Event_response(msg_);
  }

private:
  ::haptic_teleop::srv::PositionService_Event msg_;
};

class Init_PositionService_Event_info
{
public:
  Init_PositionService_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PositionService_Event_request info(::haptic_teleop::srv::PositionService_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_PositionService_Event_request(msg_);
  }

private:
  ::haptic_teleop::srv::PositionService_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::haptic_teleop::srv::PositionService_Event>()
{
  return haptic_teleop::srv::builder::Init_PositionService_Event_info();
}

}  // namespace haptic_teleop

#endif  // HAPTIC_TELEOP__SRV__DETAIL__POSITION_SERVICE__BUILDER_HPP_
