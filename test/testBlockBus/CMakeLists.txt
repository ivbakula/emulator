# TestCase CMakefFile template 
file(GLOB_RECURSE SRCS *.cxx)

add_executable(testBlockBus ${SRCS})

target_include_directories(testBlockBus PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(testBlockBus common gtest gtest_main gmock)

add_test(NAME testComponent COMMAND testComponent)
