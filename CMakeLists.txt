cmake_minimum_required(VERSION 3.12)
project(dialog-layout C)

# List your source files here
set(DIALOG_LAYOUT_SOURCES
    src/layout.c
)

# Add header files for IDEs (not needed for build)
set(DIALOG_LAYOUT_HEADERS
    include/layout.h
)

# Create the static library
add_library(dialog-layout STATIC ${DIALOG_LAYOUT_SOURCES} ${DIALOG_LAYOUT_HEADERS})

target_include_directories(dialog-layout PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(dialog-layout PUBLIC c_std_99)
if(MSVC)
    target_compile_options(dialog-layout PRIVATE /W4)
else()
    target_compile_options(dialog-layout PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS dialog-layout
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES ${DIALOG_LAYOUT_HEADERS} DESTINATION include)
