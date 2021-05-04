add_library(tray src/tray.h)

set(LIBAPPINDICATOR_MINIMUM 0.4.90)
set_target_properties(tray PROPERTIES LINKER_LANGUAGE C)

IF(APPLE)
    target_compile_definitions(tray PUBLIC TRAY_APPKIT=1)
ELSEIF(WIN32)
    target_compile_definitions(tray PUBLIC TRAY_WINAPI=1)
ELSE()
    target_compile_definitions(tray PUBLIC TRAY_APPINDICATOR=1)

    find_package(PkgConfig REQUIRED)

    pkg_check_modules(GTK REQUIRED gtk+-3.0)

    target_link_libraries(tray PUBLIC ${GTK_LIBRARIES})
    target_include_directories(tray PUBLIC ${GTK_INCLUDE_DIRS})
    target_link_directories(tray PUBLIC ${GTK_LIBRARY_DIRS})

    pkg_check_modules(LIBAPPINDICATOR appindicator3-0.1>=${LIBAPPINDICATOR_MINIMUM})

    target_link_libraries(tray PUBLIC ${LIBAPPINDICATOR_LIBRARIES})
    target_include_directories(tray PUBLIC ${LIBAPPINDICATOR_INCLUDE_DIRS})
    target_link_directories(tray PUBLIC ${LIBAPPINDICATOR_LIBRARY_DIRS})
ENDIF()