// generated from
// rosidl_typesupport_fastrtps_c/resource/rosidl_typesupport_fastrtps_c__visibility_control.h.in
// generated code does not contain a copyright notice

#ifndef UNITY_ROBOTICS_IRA2__MSG__ROSIDL_TYPESUPPORT_FASTRTPS_C__VISIBILITY_CONTROL_H_
#define UNITY_ROBOTICS_IRA2__MSG__ROSIDL_TYPESUPPORT_FASTRTPS_C__VISIBILITY_CONTROL_H_

#if __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_TYPESUPPORT_FASTRTPS_C_EXPORT_unity_robotics_ira2 __attribute__ ((dllexport))
    #define ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_unity_robotics_ira2 __attribute__ ((dllimport))
  #else
    #define ROSIDL_TYPESUPPORT_FASTRTPS_C_EXPORT_unity_robotics_ira2 __declspec(dllexport)
    #define ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_unity_robotics_ira2 __declspec(dllimport)
  #endif
  #ifdef ROSIDL_TYPESUPPORT_FASTRTPS_C_BUILDING_DLL_unity_robotics_ira2
    #define ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2 ROSIDL_TYPESUPPORT_FASTRTPS_C_EXPORT_unity_robotics_ira2
  #else
    #define ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2 ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_unity_robotics_ira2
  #endif
#else
  #define ROSIDL_TYPESUPPORT_FASTRTPS_C_EXPORT_unity_robotics_ira2 __attribute__ ((visibility("default")))
  #define ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_unity_robotics_ira2
  #if __GNUC__ >= 4
    #define ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2 __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_unity_robotics_ira2
  #endif
#endif

#if __cplusplus
}
#endif

#endif  // UNITY_ROBOTICS_IRA2__MSG__ROSIDL_TYPESUPPORT_FASTRTPS_C__VISIBILITY_CONTROL_H_
