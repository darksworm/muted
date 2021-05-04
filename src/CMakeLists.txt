set(BINARY ${CMAKE_PROJECT_NAME}_test)

add_executable(
        muted
        main.cpp
        tray_icon.h
        tray_icon.cpp
        lib/tray/TrayIcon.h
        lib/tray/CrossPlatformTrayIcon.h
        lib/microphone/MicrophoneController.h
        lib/microphone/MicrophoneStateProvider.h
        lib/microphone/AMixer/AMixerMicrophoneController.h
        lib/CodeExecutor.h
        lib/BashCodeExecutor.h
        lib/microphone/AMixer/AMixerMicrophoneStateProvider.h
        lib/microphone/AMixer/AMixerMicrophoneController.cpp
        lib/microphone/AMixer/AMixerMicrophoneStateProvider.cpp
)

add_subdirectory(lib/external/tray)
add_subdirectory(lib/external/glfw)

target_link_libraries(muted PUBLIC tray)
target_link_libraries(muted PUBLIC glfw)