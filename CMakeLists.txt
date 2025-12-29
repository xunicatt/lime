cmake_minimum_required(VERSION 3.14)
project(lime VERSION 2.0.0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Werror)

set(
  SOURCES
  src/lime/http/methods.cc
  src/lime/http/request.cc
  src/lime/http/response.cc
  src/lime/http/router.cc
  src/lime/http/server.cc
  src/lime/http/status.cc
  src/lime/json/json.cc
  src/lime/json/parser.cc
  src/lime/threadpool/threadpool.cc
  src/lime/utils/logger.cc
  src/clime/http/methods.cc
  src/clime/http/request.cc
  src/clime/http/response.cc
  src/clime/http/router.cc
  src/clime/http/server.cc
)

add_library(lime SHARED ${SOURCES})
target_include_directories(lime PUBLIC include)

# Install library and headers
install(
  TARGETS lime
  EXPORT limeTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/clime include/lime
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
)

# Generate pkg-config file
configure_file(lime.pc.in lime.pc @ONLY)
install(
  FILES ${CMAKE_BINARY_DIR}/lime.pc
  DESTINATION lib/pkgconfig
)
