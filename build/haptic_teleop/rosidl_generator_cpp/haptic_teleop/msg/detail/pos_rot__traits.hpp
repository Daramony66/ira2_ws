// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from haptic_teleop:msg/PosRot.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/msg/pos_rot.hpp"


#ifndef HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__TRAITS_HPP_
#define HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "haptic_teleop/msg/detail/pos_rot__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace haptic_teleop
{

namespace msg
{

inline void to_flow_style_yaml(
  const PosRot & msg,
  std::ostream & out)
{
  out << "{";
  // member: pos_x
  {
    out << "pos_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_x, out);
    out << ", ";
  }

  // member: pos_y
  {
    out << "pos_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_y, out);
    out << ", ";
  }

  // member: pos_z
  {
    out << "pos_z: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_z, out);
    out << ", ";
  }

  // member: rot_x
  {
    out << "rot_x: ";
    rosidl_generator_traits::value_to_yaml(msg.rot_x, out);
    out << ", ";
  }

  // member: rot_y
  {
    out << "rot_y: ";
    rosidl_generator_traits::value_to_yaml(msg.rot_y, out);
    out << ", ";
  }

  // member: rot_z
  {
    out << "rot_z: ";
    rosidl_generator_traits::value_to_yaml(msg.rot_z, out);
    out << ", ";
  }

  // member: rot_w
  {
    out << "rot_w: ";
    rosidl_generator_traits::value_to_yaml(msg.rot_w, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PosRot & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pos_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pos_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_x, out);
    out << "\n";
  }

  // member: pos_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pos_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_y, out);
    out << "\n";
  }

  // member: pos_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pos_z: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_z, out);
    out << "\n";
  }

  // member: rot_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rot_x: ";
    rosidl_generator_traits::value_to_yaml(msg.rot_x, out);
    out << "\n";
  }

  // member: rot_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rot_y: ";
    rosidl_generator_traits::value_to_yaml(msg.rot_y, out);
    out << "\n";
  }

  // member: rot_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rot_z: ";
    rosidl_generator_traits::value_to_yaml(msg.rot_z, out);
    out << "\n";
  }

  // member: rot_w
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rot_w: ";
    rosidl_generator_traits::value_to_yaml(msg.rot_w, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PosRot & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace haptic_teleop

namespace rosidl_generator_traits
{

[[deprecated("use haptic_teleop::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const haptic_teleop::msg::PosRot & msg,
  std::ostream & out, size_t indentation = 0)
{
  haptic_teleop::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use haptic_teleop::msg::to_yaml() instead")]]
inline std::string to_yaml(const haptic_teleop::msg::PosRot & msg)
{
  return haptic_teleop::msg::to_yaml(msg);
}

template<>
inline const char * data_type<haptic_teleop::msg::PosRot>()
{
  return "haptic_teleop::msg::PosRot";
}

template<>
inline const char * name<haptic_teleop::msg::PosRot>()
{
  return "haptic_teleop/msg/PosRot";
}

template<>
struct has_fixed_size<haptic_teleop::msg::PosRot>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<haptic_teleop::msg::PosRot>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<haptic_teleop::msg::PosRot>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HAPTIC_TELEOP__MSG__DETAIL__POS_ROT__TRAITS_HPP_
