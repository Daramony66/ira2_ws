// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from unity_robotics_ira2:msg/UnityColor.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unity_robotics_ira2/msg/unity_color.hpp"


#ifndef UNITY_ROBOTICS_IRA2__MSG__DETAIL__UNITY_COLOR__TRAITS_HPP_
#define UNITY_ROBOTICS_IRA2__MSG__DETAIL__UNITY_COLOR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "unity_robotics_ira2/msg/detail/unity_color__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace unity_robotics_ira2
{

namespace msg
{

inline void to_flow_style_yaml(
  const UnityColor & msg,
  std::ostream & out)
{
  out << "{";
  // member: r
  {
    out << "r: ";
    rosidl_generator_traits::value_to_yaml(msg.r, out);
    out << ", ";
  }

  // member: g
  {
    out << "g: ";
    rosidl_generator_traits::value_to_yaml(msg.g, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << ", ";
  }

  // member: a
  {
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UnityColor & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: r
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r: ";
    rosidl_generator_traits::value_to_yaml(msg.r, out);
    out << "\n";
  }

  // member: g
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "g: ";
    rosidl_generator_traits::value_to_yaml(msg.g, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
  }

  // member: a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UnityColor & msg, bool use_flow_style = false)
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

}  // namespace unity_robotics_ira2

namespace rosidl_generator_traits
{

[[deprecated("use unity_robotics_ira2::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const unity_robotics_ira2::msg::UnityColor & msg,
  std::ostream & out, size_t indentation = 0)
{
  unity_robotics_ira2::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use unity_robotics_ira2::msg::to_yaml() instead")]]
inline std::string to_yaml(const unity_robotics_ira2::msg::UnityColor & msg)
{
  return unity_robotics_ira2::msg::to_yaml(msg);
}

template<>
inline const char * data_type<unity_robotics_ira2::msg::UnityColor>()
{
  return "unity_robotics_ira2::msg::UnityColor";
}

template<>
inline const char * name<unity_robotics_ira2::msg::UnityColor>()
{
  return "unity_robotics_ira2/msg/UnityColor";
}

template<>
struct has_fixed_size<unity_robotics_ira2::msg::UnityColor>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<unity_robotics_ira2::msg::UnityColor>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<unity_robotics_ira2::msg::UnityColor>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UNITY_ROBOTICS_IRA2__MSG__DETAIL__UNITY_COLOR__TRAITS_HPP_
