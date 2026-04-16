// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from haptic_teleop:msg/UnityColor.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/msg/unity_color.hpp"


#ifndef HAPTIC_TELEOP__MSG__DETAIL__UNITY_COLOR__BUILDER_HPP_
#define HAPTIC_TELEOP__MSG__DETAIL__UNITY_COLOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "haptic_teleop/msg/detail/unity_color__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace haptic_teleop
{

namespace msg
{

namespace builder
{

class Init_UnityColor_a
{
public:
  explicit Init_UnityColor_a(::haptic_teleop::msg::UnityColor & msg)
  : msg_(msg)
  {}
  ::haptic_teleop::msg::UnityColor a(::haptic_teleop::msg::UnityColor::_a_type arg)
  {
    msg_.a = std::move(arg);
    return std::move(msg_);
  }

private:
  ::haptic_teleop::msg::UnityColor msg_;
};

class Init_UnityColor_b
{
public:
  explicit Init_UnityColor_b(::haptic_teleop::msg::UnityColor & msg)
  : msg_(msg)
  {}
  Init_UnityColor_a b(::haptic_teleop::msg::UnityColor::_b_type arg)
  {
    msg_.b = std::move(arg);
    return Init_UnityColor_a(msg_);
  }

private:
  ::haptic_teleop::msg::UnityColor msg_;
};

class Init_UnityColor_g
{
public:
  explicit Init_UnityColor_g(::haptic_teleop::msg::UnityColor & msg)
  : msg_(msg)
  {}
  Init_UnityColor_b g(::haptic_teleop::msg::UnityColor::_g_type arg)
  {
    msg_.g = std::move(arg);
    return Init_UnityColor_b(msg_);
  }

private:
  ::haptic_teleop::msg::UnityColor msg_;
};

class Init_UnityColor_r
{
public:
  Init_UnityColor_r()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_UnityColor_g r(::haptic_teleop::msg::UnityColor::_r_type arg)
  {
    msg_.r = std::move(arg);
    return Init_UnityColor_g(msg_);
  }

private:
  ::haptic_teleop::msg::UnityColor msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::haptic_teleop::msg::UnityColor>()
{
  return haptic_teleop::msg::builder::Init_UnityColor_r();
}

}  // namespace haptic_teleop

#endif  // HAPTIC_TELEOP__MSG__DETAIL__UNITY_COLOR__BUILDER_HPP_
