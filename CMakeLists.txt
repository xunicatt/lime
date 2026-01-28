cmake_minimum_required(VERSION 3.14)

execute_process(COMMAND bash version OUTPUT_VARIABLE "${VERSION}")

project(lime VERSION "${VERSION}" LANGUAGES CXX)

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
  FILES
  "include/clime/http/http.h"
  "include/clime/http/methods.h"
  "include/clime/http/request.h"
  "include/clime/http/response.h"
  "include/clime/http/router.h"
  "include/clime/http/server.h"
  "include/clime/http/status.h"
  DESTINATION "include/clime/http"
)

install(
  FILES
  "include/clime/clime.h"
  DESTINATION "include/clime/"
)

install(
  FILES
  "include/lime/http/http.h"
  "include/lime/http/methods.h"
  "include/lime/http/request.h"
  "include/lime/http/response.h"
  "include/lime/http/router.h"
  "include/lime/http/server.h"
  "include/lime/http/status.h"
  DESTINATION "include/lime/http"
)

install(
  FILES
  "include/lime/json/json.h"
  DESTINATION "include/lime/json"
)

install(
  FILES
  "include/lime/threadpool/threadpool.h"
  DESTINATION "include/lime/threadpool"
)

install(
  FILES
  "include/lime/utils/logger.h"
  DESTINATION "include/lime/utils"
)

install(
  FILES
  "include/lime/lime.h"
  DESTINATION "include/lime/"
)

# Generate pkg-config file
configure_file(lime.pc.in lime.pc @ONLY)
install(
  FILES ${CMAKE_BINARY_DIR}/lime.pc
  DESTINATION lib/pkgconfig
)
