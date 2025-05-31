cmake_minimum_required(VERSION 3.12)

project(dialog-layout VERSION 1.0.2 LANGUAGES C)

set(DIALOG_LAYOUT_SOURCES src/layout.c)
set(DIALOG_LAYOUT_HEADERS include/layout.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${DIALOG_LAYOUT_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include FILES ${DIALOG_LAYOUT_HEADERS})

# Create the static library
add_library(dialog-layout STATIC ${DIALOG_LAYOUT_SOURCES} ${DIALOG_LAYOUT_HEADERS})
add_library(dialog-layout::dialog-layout ALIAS dialog-layout)

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

# Update documentation
find_package(Doxygen REQUIRED)
if(DOXYGEN_FOUND)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

# Installation instructions
include(GNUInstallDirs)

install(TARGETS dialog-layout
    EXPORT dialog-layoutTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${DIALOG_LAYOUT_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export the target for find_package
install(EXPORT dialog-layoutTargets
    FILE dialog-layoutTargets.cmake
    NAMESPACE dialog-layout::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dialog-layout
)

# Create a Config and ConfigVersion file for find_package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/dialog-layoutConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/dialog-layoutConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/dialog-layoutConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/dialog-layout"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/dialog-layoutConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/dialog-layoutConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dialog-layout
)
