# TestCase CMakefFile template 
file(GLOB_RECURSE SRCS *.cxx)

add_executable(testComponent ${SRCS})

target_include_directories(testComponent PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(testComponent common gtest gtest_main gmock)

add_test(NAME testComponent COMMAND testComponent)
