# cmake minimum required version
cmake_minimum_required(VERSION 3.19)

# ----------------------------------------------
# Start face sdk project
# ----------------------------------------------
project(
  cpp_template
  VERSION 0.0.1
  LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(FetchContent)
include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ARTICRAFT_OUT "out")
set(CMAKE_INSTALL_PREFIX "install")

# ------------------------------------------------------------------
# Set default build to release
# ------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE STRING "Choose Release or Debug" FORCE)
endif()
# build type
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
  add_definitions(-DDEBUG -D_DEBUG)
  message("Debug mode:${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3")
  add_definitions(-DNDEBUG)
  message("Release mode:${CMAKE_C_FLAGS_RELEASE}")
endif()

message("Identifying the OS...")
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  message("This is Windows.")
  if(MSVC)
    add_compile_options(/utf-8)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE)
  endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
  message("This is Linux.")
  add_compile_options(-fPIC)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  message("This is MacOS.")
endif()

cpmaddpackage("gh:fmtlib/fmt#10.2.1")

file(GLOB_RECURSE SRC_NESTED src/*.cc)
set(FILTERED_MAIN_FILES "")
foreach(FILE ${SRC_NESTED})
  if(FILE MATCHES ".*[./\\]main.*")
    list(APPEND FILTERED_MAIN_FILES ${FILE})
  endif()
endforeach()
foreach(FILE ${FILTERED_MAIN_FILES})
  list(REMOVE_ITEM SRC_NESTED "${CMAKE_CURRENT_LIST_DIR}/src/main.cc")
endforeach()

add_library(lib_core OBJECT ${SRC_NESTED})
add_library(lib_core::lib_core ALIAS lib_core)
set_target_properties(lib_core PROPERTIES NO_SYSTEM_FROM_IMPORTED ON)
target_include_directories(lib_core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(lib_core PUBLIC fmt::fmt)

add_subdirectory(tests)
add_subdirectory(samples)

# ------------------------------------------------------------------
# Compile
# ------------------------------------------------------------------

message("Main files: ${FILTERED_MAIN_FILES}")
list(LENGTH FILTERED_MAIN_FILES MAIN_FILES_SIZE)
if(MAIN_FILES_SIZE EQUAL 1)
  add_executable(${CMAKE_PROJECT_NAME} ${FILTERED_MAIN_FILES})
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE lib_core)
  target_include_directories(${CMAKE_PROJECT_NAME}
                             PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
elseif(MAIN_FILES_SIZE GREATER 1)
  message(FATAL_ERROR "Multiple main files found: ${FILTERED_MAIN_FILES}")
else()
  add_library(${CMAKE_PROJECT_NAME} SHARED)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE lib_core)
  target_include_directories(${CMAKE_PROJECT_NAME}
                             PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
endif()

set_target_properties(
  ${CMAKE_PROJECT_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${ARTICRAFT_OUT}"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${ARTICRAFT_OUT}"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${ARTICRAFT_OUT}")
