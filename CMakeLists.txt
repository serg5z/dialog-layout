set(CMAKE_VERBOSE_MAKEFILE ON)

project(dialog-layout)

if(NOT LIBRARY_OUTPUT_PATH)
  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
endif(NOT LIBRARY_OUTPUT_PATH)

add_subdirectory(src)
