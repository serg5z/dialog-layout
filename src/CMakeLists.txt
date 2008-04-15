include_directories(${dialog-layout_SOURCE_DIR}/include)

add_definitions(-D_WIN32_IE=0x0500)

set(sources
  layout.c)
  
add_library(layout STATIC ${sources})
