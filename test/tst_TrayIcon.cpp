#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include "lib/tray/TrayIconProvider.h"
#include "lib/tray/CrossPlatformTrayIcon.h"

using namespace GUI;
using namespace trompeloeil;

class ProviderMock : public TrayIconProvider
{
public:
    MAKE_MOCK1 (init, int(void * ), override);
    MAKE_MOCK1 (update, void(void * ), override);
    MAKE_MOCK1 (loop, int(int), override);
    MAKE_MOCK0 (exit, void(), override);
};

TEST_CASE("CrossPlatformTrayIcon", "[CrossPlatformTrayIcon]")
{
    SECTION("clearMenuItems removes all menu items")
    {
        ProviderMock providerMock;
        CrossPlatformTrayIcon icon(providerMock);

        icon.addTrayMenuItem({.text = "test", .checked = true});
        icon.addTrayMenuItem({.text = "other", .checked = false});
        icon.clearMenuItems();

        struct tray initStructure;

        REQUIRE_CALL(providerMock, init(ANY(void * )))
            .LR_SIDE_EFFECT(initStructure = *(tray *) _1)
            .RETURN(0)
            .TIMES(1);

        icon.build();

        // null menu item = terminating menu item
        CHECK(initStructure.menu->checked == 0);
        CHECK(initStructure.menu->disabled == 0);
        CHECK(initStructure.menu->text == nullptr);
        CHECK(initStructure.menu->cb == nullptr);
        CHECK(initStructure.menu->context == nullptr);
    }
}

TEST_CASE("TrayIcon", "[TrayIcon]")
{
    SECTION("build calls stateProvider.init")
    {
        ProviderMock providerMock;
        REQUIRE_CALL(providerMock, init(ne(nullptr)))
            .RETURN(0)
            .TIMES(1);

        CrossPlatformTrayIcon icon(providerMock);
        icon.build();
    }

    SECTION("data passed in addTrayMenuItem passed to stateProvider.init")
    {
        ProviderMock providerMock;
        CrossPlatformTrayIcon icon(providerMock);
        struct tray initStructure;

        REQUIRE_CALL(providerMock, init(ANY(void * )))
            .LR_SIDE_EFFECT(initStructure = *(tray *) _1)
            .RETURN(0)
            .TIMES(1);

        icon.addTrayMenuItem({.text = "test", .checked = true});
        icon.addTrayMenuItem({.text = "other", .checked = false});
        icon.build();

        auto elem = initStructure.menu;

        CHECK(elem->text == "test");
        CHECK(elem->checked == true);

        elem++;

        CHECK(elem->text == "other");
        CHECK(elem->checked == false);

        SECTION("and last element is null")
        {
            elem++;

            CHECK(elem->text == nullptr);
            CHECK(elem->disabled == 0);
            CHECK(elem->checked == 0);
            CHECK(elem->cb == nullptr);
            CHECK(elem->context == nullptr);
        }
    }

    SECTION("last tray menu item is null when no elements added")
    {
        ProviderMock providerMock;
        CrossPlatformTrayIcon icon(providerMock);
        struct tray initStructure;

        REQUIRE_CALL(providerMock, init(ANY(void * )))
            .LR_SIDE_EFFECT(initStructure = *(tray *) _1)
            .RETURN(0)
            .TIMES(1);

        icon.build();

        CHECK(initStructure.menu->text == nullptr);
        CHECK(initStructure.menu->disabled == 0);
        CHECK(initStructure.menu->checked == 0);
        CHECK(initStructure.menu->cb == nullptr);
        CHECK(initStructure.menu->context == nullptr);
    }

    SECTION("sets icon to icon.png")
    {
        ProviderMock providerMock;
        CrossPlatformTrayIcon icon(providerMock);
        struct tray initStructure;

        REQUIRE_CALL(providerMock, init(ANY(void * )))
            .LR_SIDE_EFFECT(initStructure = *(tray *) _1)
            .RETURN(0)
            .TIMES(1);

        icon.addTrayMenuItem({.text = "other", .checked = false});
        icon.build();

        CHECK(initStructure.icon == "icon.png");
    }

    SECTION("loop delegates to provider")
    {
        ProviderMock providerMock;
        CrossPlatformTrayIcon icon(providerMock);

        REQUIRE_CALL(providerMock, loop(0))
            .RETURN(0)
            .TIMES(1);

        REQUIRE_CALL(providerMock, loop(1))
            .RETURN(1)
            .TIMES(1);

        CHECK(icon.loop(0) == 0);
        CHECK(icon.loop(1) == 1);
    }

    SECTION("exit delegates to provider")
    {
        ProviderMock providerMock;
        CrossPlatformTrayIcon icon(providerMock);

        REQUIRE_CALL(providerMock, exit()).TIMES(1);

        icon.exit();
    }

    SECTION("update delegates to provider")
    {
        ProviderMock providerMock;
        CrossPlatformTrayIcon icon(providerMock);

        struct tray initStructure;

        REQUIRE_CALL(providerMock, init(_))
            .RETURN(0)
            .TIMES(1);

        REQUIRE_CALL(providerMock, update(ANY(void * )))
            .LR_SIDE_EFFECT(initStructure = *(tray *) _1)
            .TIMES(1);

        icon.build();
        icon.update();

        CHECK(initStructure.icon == "icon.png");
    }
}