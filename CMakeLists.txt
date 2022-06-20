cmake_minimum_required (VERSION 3.0)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source build is not allowed")
endif()

project (jenum LANGUAGES CXX VERSION 0.0.1)

option(TESTS "Enable unit tests" OFF)
option(CHECKER "Enable static code analysing" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CHECKER)
   set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,android-*,bugprone-*,clang-analyzer-*,hicpp-*,misc-*,modernize-*,portability-*)
endif()

add_library(${PROJECT_NAME}
  INTERFACE
  )

target_include_directories(${PROJECT_NAME}
  INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/jenum>
  )

target_link_libraries(${PROJECT_NAME}
  )

enable_testing()

if (TESTS)
  add_subdirectory(tests)
endif()

configure_file(
  ${PROJECT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.pc.in
  ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.pc
  @ONLY
)

install(DIRECTORY include/${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

# generate jenum.pc
configure_file(${PROJECT_SOURCE_DIR}/jenum.pc.in ${PROJECT_BINARY_DIR}/jenum.pc.gen @ONLY)
file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/jenum.pc INPUT "${CMAKE_BINARY_DIR}/jenum.pc.gen")
install(FILES ${CMAKE_BINARY_DIR}/jenum.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
