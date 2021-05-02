set(BINARY ${CMAKE_PROJECT_NAME}_test)

add_executable(muted main.cpp ../lib/TrayIcon.h tray_icon.h ../lib/CrossPlatformTrayIcon.h)

add_subdirectory(external/tray)
add_subdirectory(external/glfw)

target_link_libraries(muted PUBLIC tray)
target_link_libraries(muted PUBLIC glfw)