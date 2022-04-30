# TestCase CMakefFile template 
file(GLOB_RECURSE SRCS *.cxx)

add_executable(testComponent ${SRCS})

target_include_directories(testComponent PUBLIC
  "${PROJECT_SOURCE_DIR}/if"
  "${PROJECT_SOURCE_DIR}/inc"
  "${CMAKE_CURRENT_SOURCE_DIR}/inc")

target_link_libraries(testComponent common gtest gtest_main gmock)

add_test(NAME testComponent COMMAND testComponent)
