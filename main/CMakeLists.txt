set(Main_SRCS main.cxx)

add_executable(${PROJECT} ${Main_SRCS})

target_link_libraries(${PROJECT} common)

target_include_directories(${PROJECT} PUBLIC
  "${PROJECT_SOURCE_DIR}/if"
  "${PROJECT_SOURCE_DIR}/inc")
