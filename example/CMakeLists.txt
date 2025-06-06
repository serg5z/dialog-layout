cmake_minimum_required(VERSION 3.15)
project(dialog-layout-example VERSION 1.0.0 LANGUAGES C)

add_definitions(-DUNICODE -D_UNICODE)

# Add the dialog-layout library as a subdirectory
#add_subdirectory(dialog-layout)
add_subdirectory(.. dialog-layout-build)

# Define the example app and its resources
add_executable(dialog-layout-example WIN32
    main.c
    resource.h
    example.rc
    example.manifest
)

# Make sure the dialog-layout include directory is available
target_include_directories(dialog-layout-example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link with dialog-layout and Windows libraries
target_link_libraries(dialog-layout-example PRIVATE
    dialog-layout::dialog-layout
    comctl32
)

# On MSVC, make sure the .rc file is treated as a resource
if(MSVC)
    set_source_files_properties(example.rc PROPERTIES LANGUAGE RC)
endif()

