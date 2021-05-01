add_library(tray src/tray.h)

set_target_properties(tray PROPERTIES LINKER_LANGUAGE C)

if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK REQUIRED gtk+-3.0)

    target_link_libraries(tray PRIVATE ${GTK_LIBRARIES})
    target_compile_definitions(tray PRIVATE ${GTK_CFLAGS_OTHER})
    target_include_directories(tray PRIVATE ${GTK_INCLUDE_DIRS})
    target_link_directories(tray PRIVATE ${GTK_LIBRARY_DIRS})
endif()

if(APPLE)

endif()

if(WIN32)

endif()

