// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from haptic_teleop:srv/ObjectPoseService.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "haptic_teleop/srv/object_pose_service.hpp"


#ifndef HAPTIC_TELEOP__SRV__DETAIL__OBJECT_POSE_SERVICE__TRAITS_HPP_
#define HAPTIC_TELEOP__SRV__DETAIL__OBJECT_POSE_SERVICE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "haptic_teleop/srv/detail/object_pose_service__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace haptic_teleop
{

namespace srv
{

inline void to_flow_style_yaml(
  const ObjectPoseService_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: object_name
  {
    out << "object_name: ";
    rosidl_generator_traits::value_to_yaml(msg.object_name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ObjectPoseService_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: object_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "object_name: ";
    rosidl_generator_traits::value_to_yaml(msg.object_name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ObjectPoseService_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace haptic_teleop

namespace rosidl_generator_traits
{

[[deprecated("use haptic_teleop::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const haptic_teleop::srv::ObjectPoseService_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  haptic_teleop::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use haptic_teleop::srv::to_yaml() instead")]]
inline std::string to_yaml(const haptic_teleop::srv::ObjectPoseService_Request & msg)
{
  return haptic_teleop::srv::to_yaml(msg);
}

template<>
inline const char * data_type<haptic_teleop::srv::ObjectPoseService_Request>()
{
  return "haptic_teleop::srv::ObjectPoseService_Request";
}

template<>
inline const char * name<haptic_teleop::srv::ObjectPoseService_Request>()
{
  return "haptic_teleop/srv/ObjectPoseService_Request";
}

template<>
struct has_fixed_size<haptic_teleop::srv::ObjectPoseService_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<haptic_teleop::srv::ObjectPoseService_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<haptic_teleop::srv::ObjectPoseService_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'object_pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace haptic_teleop
{

namespace srv
{

inline void to_flow_style_yaml(
  const ObjectPoseService_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: object_pose
  {
    out << "object_pose: ";
    to_flow_style_yaml(msg.object_pose, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ObjectPoseService_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: object_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "object_pose:\n";
    to_block_style_yaml(msg.object_pose, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ObjectPoseService_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace haptic_teleop

namespace rosidl_generator_traits
{

[[deprecated("use haptic_teleop::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const haptic_teleop::srv::ObjectPoseService_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  haptic_teleop::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use haptic_teleop::srv::to_yaml() instead")]]
inline std::string to_yaml(const haptic_teleop::srv::ObjectPoseService_Response & msg)
{
  return haptic_teleop::srv::to_yaml(msg);
}

template<>
inline const char * data_type<haptic_teleop::srv::ObjectPoseService_Response>()
{
  return "haptic_teleop::srv::ObjectPoseService_Response";
}

template<>
inline const char * name<haptic_teleop::srv::ObjectPoseService_Response>()
{
  return "haptic_teleop/srv/ObjectPoseService_Response";
}

template<>
struct has_fixed_size<haptic_teleop::srv::ObjectPoseService_Response>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Pose>::value> {};

template<>
struct has_bounded_size<haptic_teleop::srv::ObjectPoseService_Response>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Pose>::value> {};

template<>
struct is_message<haptic_teleop::srv::ObjectPoseService_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace haptic_teleop
{

namespace srv
{

inline void to_flow_style_yaml(
  const ObjectPoseService_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ObjectPoseService_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ObjectPoseService_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace haptic_teleop

namespace rosidl_generator_traits
{

[[deprecated("use haptic_teleop::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const haptic_teleop::srv::ObjectPoseService_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  haptic_teleop::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use haptic_teleop::srv::to_yaml() instead")]]
inline std::string to_yaml(const haptic_teleop::srv::ObjectPoseService_Event & msg)
{
  return haptic_teleop::srv::to_yaml(msg);
}

template<>
inline const char * data_type<haptic_teleop::srv::ObjectPoseService_Event>()
{
  return "haptic_teleop::srv::ObjectPoseService_Event";
}

template<>
inline const char * name<haptic_teleop::srv::ObjectPoseService_Event>()
{
  return "haptic_teleop/srv/ObjectPoseService_Event";
}

template<>
struct has_fixed_size<haptic_teleop::srv::ObjectPoseService_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<haptic_teleop::srv::ObjectPoseService_Event>
  : std::integral_constant<bool, has_bounded_size<haptic_teleop::srv::ObjectPoseService_Request>::value && has_bounded_size<haptic_teleop::srv::ObjectPoseService_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<haptic_teleop::srv::ObjectPoseService_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<haptic_teleop::srv::ObjectPoseService>()
{
  return "haptic_teleop::srv::ObjectPoseService";
}

template<>
inline const char * name<haptic_teleop::srv::ObjectPoseService>()
{
  return "haptic_teleop/srv/ObjectPoseService";
}

template<>
struct has_fixed_size<haptic_teleop::srv::ObjectPoseService>
  : std::integral_constant<
    bool,
    has_fixed_size<haptic_teleop::srv::ObjectPoseService_Request>::value &&
    has_fixed_size<haptic_teleop::srv::ObjectPoseService_Response>::value
  >
{
};

template<>
struct has_bounded_size<haptic_teleop::srv::ObjectPoseService>
  : std::integral_constant<
    bool,
    has_bounded_size<haptic_teleop::srv::ObjectPoseService_Request>::value &&
    has_bounded_size<haptic_teleop::srv::ObjectPoseService_Response>::value
  >
{
};

template<>
struct is_service<haptic_teleop::srv::ObjectPoseService>
  : std::true_type
{
};

template<>
struct is_service_request<haptic_teleop::srv::ObjectPoseService_Request>
  : std::true_type
{
};

template<>
struct is_service_response<haptic_teleop::srv::ObjectPoseService_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // HAPTIC_TELEOP__SRV__DETAIL__OBJECT_POSE_SERVICE__TRAITS_HPP_
