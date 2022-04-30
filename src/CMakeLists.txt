file(GLOB COMMON_SOURCES *.cxx)
add_library(common STATIC ${COMMON_SOURCES})

target_include_directories(common PUBLIC
  "${PROJECT_SOURCE_DIR}/if"
  "${PROJECT_SOURCE_DIR}/inc")
