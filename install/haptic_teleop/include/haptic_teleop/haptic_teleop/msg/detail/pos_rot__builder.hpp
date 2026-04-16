// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from haptic_teleop:msg/PosRot.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/msg/pos_rot.hpp"


#ifndef HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__BUILDER_HPP_
#define HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "haptic_teleop/msg/detail/pos_rot__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace haptic_teleop
{

namespace msg
{

namespace builder
{

class Init_PosRot_rot_w
{
public:
  explicit Init_PosRot_rot_w(::haptic_teleop::msg::PosRot & msg)
  : msg_(msg)
  {}
  ::haptic_teleop::msg::PosRot rot_w(::haptic_teleop::msg::PosRot::_rot_w_type arg)
  {
    msg_.rot_w = std::move(arg);
    return std::move(msg_);
  }

private:
  ::haptic_teleop::msg::PosRot msg_;
};

class Init_PosRot_rot_z
{
public:
  explicit Init_PosRot_rot_z(::haptic_teleop::msg::PosRot & msg)
  : msg_(msg)
  {}
  Init_PosRot_rot_w rot_z(::haptic_teleop::msg::PosRot::_rot_z_type arg)
  {
    msg_.rot_z = std::move(arg);
    return Init_PosRot_rot_w(msg_);
  }

private:
  ::haptic_teleop::msg::PosRot msg_;
};

class Init_PosRot_rot_y
{
public:
  explicit Init_PosRot_rot_y(::haptic_teleop::msg::PosRot & msg)
  : msg_(msg)
  {}
  Init_PosRot_rot_z rot_y(::haptic_teleop::msg::PosRot::_rot_y_type arg)
  {
    msg_.rot_y = std::move(arg);
    return Init_PosRot_rot_z(msg_);
  }

private:
  ::haptic_teleop::msg::PosRot msg_;
};

class Init_PosRot_rot_x
{
public:
  explicit Init_PosRot_rot_x(::haptic_teleop::msg::PosRot & msg)
  : msg_(msg)
  {}
  Init_PosRot_rot_y rot_x(::haptic_teleop::msg::PosRot::_rot_x_type arg)
  {
    msg_.rot_x = std::move(arg);
    return Init_PosRot_rot_y(msg_);
  }

private:
  ::haptic_teleop::msg::PosRot msg_;
};

class Init_PosRot_pos_z
{
public:
  explicit Init_PosRot_pos_z(::haptic_teleop::msg::PosRot & msg)
  : msg_(msg)
  {}
  Init_PosRot_rot_x pos_z(::haptic_teleop::msg::PosRot::_pos_z_type arg)
  {
    msg_.pos_z = std::move(arg);
    return Init_PosRot_rot_x(msg_);
  }

private:
  ::haptic_teleop::msg::PosRot msg_;
};

class Init_PosRot_pos_y
{
public:
  explicit Init_PosRot_pos_y(::haptic_teleop::msg::PosRot & msg)
  : msg_(msg)
  {}
  Init_PosRot_pos_z pos_y(::haptic_teleop::msg::PosRot::_pos_y_type arg)
  {
    msg_.pos_y = std::move(arg);
    return Init_PosRot_pos_z(msg_);
  }

private:
  ::haptic_teleop::msg::PosRot msg_;
};

class Init_PosRot_pos_x
{
public:
  Init_PosRot_pos_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PosRot_pos_y pos_x(::haptic_teleop::msg::PosRot::_pos_x_type arg)
  {
    msg_.pos_x = std::move(arg);
    return Init_PosRot_pos_y(msg_);
  }

private:
  ::haptic_teleop::msg::PosRot msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::haptic_teleop::msg::PosRot>()
{
  return haptic_teleop::msg::builder::Init_PosRot_pos_x();
}

}  // namespace haptic_teleop

#endif  // HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__BUILDER_HPP_
