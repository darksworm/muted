set(BINARY ${CMAKE_PROJECT_NAME}_test)

add_executable(
        tests main.cpp
        trompeloeil_catch.hpp
        tst_OSTypeProvider.cpp
        ../lib/OSTypeProvider.h
        tst_TrayIcon.cpp tst_tray_icon.cpp)

add_subdirectory(external/trompeloeil)
target_link_libraries(tests PRIVATE trompeloeil)

find_package(Catch2 REQUIRED)
target_link_libraries(tests PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)

catch_discover_tests(tests)