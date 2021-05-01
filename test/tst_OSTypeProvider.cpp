#include <catch2/catch.hpp>
#include <iostream>
#include "../lib/OSTypeProvider.h"

using namespace OS;

TEST_CASE("OSTypeProvider", "[OSTypeProvider]")
{
    class SysInfoMockThrows
    {
    public:
        static std::string operatingSystemType() {
            throw std::runtime_error("");
        }
    };

    SECTION("getType throws when throwing mock passed")
    {
        OSTypeProvider<SysInfoMockThrows> provider;
        REQUIRE_THROWS(provider.getType());
    }

    #define SYS_INFO_MOCK(PREFIX, RETURN_VAL) \
        class PREFIX##SysInfoMock \
        { \
        public: \
            static std::string operatingSystemType() {\
                return RETURN_VAL; \
            } \
        }

    SECTION("getType calls operatingSystemType on template class 1/2")
    {
        SYS_INFO_MOCK(Mac, "osx");
        OSTypeProvider<MacSysInfoMock> provider;
        CHECK(provider.getType() == "osx");
    }

    SECTION("getType calls operatingSystemType on template class 2/2")
    {
        SYS_INFO_MOCK(Win, "windows");
        OSTypeProvider<WinSysInfoMock> provider;
        CHECK(provider.getType() == "windows");
    }

    #define CHECK_getEnumType(PREFIX, RETURN_VAL, EXPECTED_OS) \
        SECTION("getEnumType returns EXPECTED_OS for RETURN_VAL") \
        {\
            SYS_INFO_MOCK(PREFIX, RETURN_VAL); \
            OSTypeProvider<PREFIX##SysInfoMock> provider; \
            CHECK(provider.getEnumType() == (EXPECTED_OS)); \
        }

    CHECK_getEnumType(Empty, "", OperatingSystem::Unknown)
    CHECK_getEnumType(Random, "nothing", OperatingSystem::Unknown)
    CHECK_getEnumType(Win, "windows", OperatingSystem::Windows)
    CHECK_getEnumType(Debian, "linux", OperatingSystem::Linux)
    CHECK_getEnumType(Mac, "macos", OperatingSystem::MacOS)
}
