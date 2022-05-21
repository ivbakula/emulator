# TestCase CMakefFile template 
file(GLOB_RECURSE SRCS *.cxx)

add_executable(testMtuBlock ${SRCS})

target_include_directories(testMtuBlock PUBLIC
  "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(testMtuBlock common gtest gtest_main gmock)

add_test(NAME testComponent COMMAND testComponent)
