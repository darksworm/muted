set(BINARY ${CMAKE_PROJECT_NAME}_test)

find_package(Catch2 REQUIRED)

add_executable(
        tests test_main.cpp
        trompeloeil_catch.hpp
        tst_OSTypeProvider.cpp
        ../lib/OSTypeProvider.h
)

add_subdirectory(external/Catch2)
add_subdirectory(external/trompeloeil)

target_link_libraries(tests PRIVATE Catch2::Catch2)
target_link_libraries(tests PRIVATE trompeloeil)

include(CTest)
include(Catch)
catch_discover_tests(tests)