# Install script for directory: /home/stlab24-04/ira2_ws/ur_rtde

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/stlab24-04/ira2_ws/install/ur_rtde")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde_lib" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librtde.so.1.6.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librtde.so.1.6"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/stlab24-04/ira2_ws/build/ur_rtde/librtde.so.1.6.2"
    "/home/stlab24-04/ira2_ws/build/ur_rtde/librtde.so.1.6"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librtde.so.1.6.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/librtde.so.1.6"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde_lib" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/stlab24-04/ira2_ws/build/ur_rtde/librtde.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_control.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_control.cpython-312-x86_64-linux-gnu.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_control.cpython-312-x86_64-linux-gnu.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/python3/dist-packages/rtde_control.cpython-312-x86_64-linux-gnu.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/lib/python3/dist-packages" TYPE SHARED_LIBRARY FILES "/home/stlab24-04/ira2_ws/build/ur_rtde/rtde_control.cpython-312-x86_64-linux-gnu.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_control.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_control.cpython-312-x86_64-linux-gnu.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_control.cpython-312-x86_64-linux-gnu.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/stlab24-04/ira2_ws/build/ur_rtde/CMakeFiles/rtde_control.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_receive.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_receive.cpython-312-x86_64-linux-gnu.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_receive.cpython-312-x86_64-linux-gnu.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/python3/dist-packages/rtde_receive.cpython-312-x86_64-linux-gnu.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/lib/python3/dist-packages" TYPE SHARED_LIBRARY FILES "/home/stlab24-04/ira2_ws/build/ur_rtde/rtde_receive.cpython-312-x86_64-linux-gnu.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_receive.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_receive.cpython-312-x86_64-linux-gnu.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_receive.cpython-312-x86_64-linux-gnu.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/stlab24-04/ira2_ws/build/ur_rtde/CMakeFiles/rtde_receive.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_io.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_io.cpython-312-x86_64-linux-gnu.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_io.cpython-312-x86_64-linux-gnu.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/python3/dist-packages/rtde_io.cpython-312-x86_64-linux-gnu.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/lib/python3/dist-packages" TYPE SHARED_LIBRARY FILES "/home/stlab24-04/ira2_ws/build/ur_rtde/rtde_io.cpython-312-x86_64-linux-gnu.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_io.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_io.cpython-312-x86_64-linux-gnu.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/python3/dist-packages/rtde_io.cpython-312-x86_64-linux-gnu.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/stlab24-04/ira2_ws/build/ur_rtde/CMakeFiles/rtde_io.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/dashboard_client.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/dashboard_client.cpython-312-x86_64-linux-gnu.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/python3/dist-packages/dashboard_client.cpython-312-x86_64-linux-gnu.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/python3/dist-packages/dashboard_client.cpython-312-x86_64-linux-gnu.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/lib/python3/dist-packages" TYPE SHARED_LIBRARY FILES "/home/stlab24-04/ira2_ws/build/ur_rtde/dashboard_client.cpython-312-x86_64-linux-gnu.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/dashboard_client.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/dashboard_client.cpython-312-x86_64-linux-gnu.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/python3/dist-packages/dashboard_client.cpython-312-x86_64-linux-gnu.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/stlab24-04/ira2_ws/build/ur_rtde/CMakeFiles/dashboard_client.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/script_client.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/script_client.cpython-312-x86_64-linux-gnu.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/python3/dist-packages/script_client.cpython-312-x86_64-linux-gnu.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/python3/dist-packages/script_client.cpython-312-x86_64-linux-gnu.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/lib/python3/dist-packages" TYPE SHARED_LIBRARY FILES "/home/stlab24-04/ira2_ws/build/ur_rtde/script_client.cpython-312-x86_64-linux-gnu.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/python3/dist-packages/script_client.cpython-312-x86_64-linux-gnu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/python3/dist-packages/script_client.cpython-312-x86_64-linux-gnu.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/python3/dist-packages/script_client.cpython-312-x86_64-linux-gnu.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde-python" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/stlab24-04/ira2_ws/build/ur_rtde/CMakeFiles/script_client.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde_dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ur_rtde" TYPE FILE FILES
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/rtde.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/rtde_utility.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/dashboard_enums.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/dashboard_client.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/robot_state.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/script_client.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/rtde_control_interface.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/rtde_control_interface_doc.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/rtde_receive_interface.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/rtde_receive_interface_doc.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/rtde_io_interface.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/rtde_io_interface_doc.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/robotiq_gripper.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/thread_utility.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/ur_rtde/rtde_export.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde_dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/urcl" TYPE FILE FILES
    "/home/stlab24-04/ira2_ws/ur_rtde/include/urcl/log.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/urcl/default_log_handler.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/urcl/script_sender.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/urcl/tcp_server.h"
    "/home/stlab24-04/ira2_ws/ur_rtde/include/urcl/tcp_socket.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde_cmake" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ur_rtde/ur_rtdeTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ur_rtde/ur_rtdeTargets.cmake"
         "/home/stlab24-04/ira2_ws/build/ur_rtde/CMakeFiles/Export/bd705e6f6a388c4e60442b65e09c6344/ur_rtdeTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ur_rtde/ur_rtdeTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ur_rtde/ur_rtdeTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ur_rtde" TYPE FILE FILES "/home/stlab24-04/ira2_ws/build/ur_rtde/CMakeFiles/Export/bd705e6f6a388c4e60442b65e09c6344/ur_rtdeTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ur_rtde" TYPE FILE FILES "/home/stlab24-04/ira2_ws/build/ur_rtde/CMakeFiles/Export/bd705e6f6a388c4e60442b65e09c6344/ur_rtdeTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ur_rtde_cmake" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ur_rtde" TYPE FILE FILES
    "/home/stlab24-04/ira2_ws/ur_rtde/cmake/ur_rtdeConfig.cmake"
    "/home/stlab24-04/ira2_ws/build/ur_rtde/ur_rtde/ur_rtdeConfigVersion.cmake"
    "/home/stlab24-04/ira2_ws/build/ur_rtde/ur_rtde/ur_rtdeBuildConfig.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-build/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/stlab24-04/ira2_ws/build/ur_rtde/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
