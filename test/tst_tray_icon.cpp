#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include "../lib/tray/TrayIcon.h"
#include "../src/tray_icon.h"

using namespace trompeloeil;

class TrayIconMock : public GUI::TrayIcon
{
    MAKE_MOCK1 (addTrayMenuItem, void(struct tray_menu), override);
    MAKE_MOCK0 (build, void(), override);
    MAKE_MOCK1 (loop, int(int), override);
    MAKE_MOCK0 (exit, void(), override);
};

TEST_CASE("initTrayIcon", "[initTrayIcon]")
{
    TrayIconMock mock;
    struct tray_menu receivedStruct;

    REQUIRE_CALL(mock, addTrayMenuItem(_))
        .LR_SIDE_EFFECT(receivedStruct = _1)
        .TIMES(1);

    REQUIRE_CALL(mock, build())
        .TIMES(1);

    initializeTrayIcon(mock);

    SECTION("adds Quit button")
    {
        CHECK(receivedStruct.text == "Quit");
        CHECK(receivedStruct.disabled == 0);
        CHECK(receivedStruct.context == nullptr);
        CHECK(receivedStruct.cb != nullptr);
    }
}