cmake_minimum_required(VERSION 3.25.3)
project(dsa)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/headers")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(TEST_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/headers")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall")

set(CUNIT_INCLUDE_DIR $ENV{CUNIT_INCLUDE_DIR})
set(CLANG_INCLUDE_DIR $ENV{CLANG_INCLUDE_DIR})
set(LIBC_INCLUDE_DIR $ENV{LIBC_INCLUDE_DIR})

file(GLOB_RECURSE SRCS "${SRC_DIR}/*.c")
file(GLOB_RECURSE HEADERS "${HEADER_DIR}/**/*.h")

add_library(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIR} ${CUNIT_INCLUDE_DIR} ${CLANG_INCLUDE_DIR} ${LIBC_INCLUDE_DIR})

find_library(CUNIT_LIBRARY NAMES cunit PATHS ${CUNIT_INCLUDE_DIR})

if(NOT CUNIT_LIBRARY)
  message(FATAL_ERROR "CUnit not found")
endif()

enable_testing()
file(GLOB TEST_SRCS "${TEST_DIR}/*.c")
foreach(TEST_SRC ${TEST_SRCS})
  get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_SRC})
  target_link_libraries(${TEST_NAME} ${PROJECT_NAME} ${CUNIT_LIBRARY})
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(
    doc
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
  )
endif()

add_custom_target(
  tidy
  COMMAND clang-tidy -header-filter=".*" -warnings-as-errors="*" ${SRCS} ${TEST_SRCS} -- -W -Wall -I${HEADER_DIR} -I${TEST_HEADER_DIR} -I${CUNIT_INCLUDE_DIR} -isystem"${CLANG_INCLUDE_DIR}" -isystem"${LIBC_INCLUDE_DIR}" -isystem"${CUNIT_INCLUDE_DIR}"
)
