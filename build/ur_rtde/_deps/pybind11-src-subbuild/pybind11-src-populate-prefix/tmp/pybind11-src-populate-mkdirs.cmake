# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-src"
  "/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-build"
  "/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-subbuild/pybind11-src-populate-prefix"
  "/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-subbuild/pybind11-src-populate-prefix/tmp"
  "/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-subbuild/pybind11-src-populate-prefix/src/pybind11-src-populate-stamp"
  "/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-subbuild/pybind11-src-populate-prefix/src"
  "/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-subbuild/pybind11-src-populate-prefix/src/pybind11-src-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-subbuild/pybind11-src-populate-prefix/src/pybind11-src-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/stlab24-04/ira2_ws/build/ur_rtde/_deps/pybind11-src-subbuild/pybind11-src-populate-prefix/src/pybind11-src-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
