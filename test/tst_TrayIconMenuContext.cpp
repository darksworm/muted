#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include "lib/tray/TrayIcon.h"
#include "tray_icon.h"

using namespace trompeloeil;

class TrayIconMock : public GUI::TrayIcon
{
    MAKE_MOCK1 (addTrayMenuItem, void(struct tray_menu), override);
    MAKE_MOCK0 (build, void(), override);
    MAKE_MOCK1 (loop, int(int), override);
    MAKE_MOCK0 (exit, void(), override);
    MAKE_MOCK0 (clearMenuItems, void(), override);
    MAKE_MOCK0 (update, void(), override);
};

class MicrophoneStateProviderMock : public Microphone::MicrophoneStateProvider
{
    MAKE_MOCK0 (getState, Microphone::MicrophoneState(), override);
};

class MicrophoneControllerMock : public Microphone::MicrophoneController
{
    MAKE_MOCK0 (mute, void(), override);
    MAKE_MOCK0 (unmute, void(), override);
};

TEST_CASE("newTrayIcon", "[newTrayIcon]")
{
    MicrophoneControllerMock micController;
    MicrophoneStateProviderMock stateProvider;

    TrayIconMock trayIcon;

    struct tray_menu quitButton{};
    struct tray_menu unmuteButton{};
    struct tray_menu muteButton{};

    SECTION("when microphone muted")
    {
        REQUIRE_CALL(stateProvider, getState())
            .RETURN(Microphone::MicrophoneState::MUTED)
            .TIMES(1);

        REQUIRE_CALL(trayIcon, addTrayMenuItem(_))
            .LR_SIDE_EFFECT(unmuteButton = _1)
            .TIMES(1);

        REQUIRE_CALL(trayIcon, addTrayMenuItem(_))
            .LR_SIDE_EFFECT(quitButton = _1)
            .TIMES(1);

        REQUIRE_CALL(trayIcon, build()).TIMES(1);

        auto context = Muted::newTrayIcon(&trayIcon, &micController, &stateProvider);

        SECTION("adds Quit button")
        {
            CHECK(std::string("Quit") == quitButton.text);
            CHECK(quitButton.disabled == 0);
            CHECK(quitButton.context == &trayIcon);
            CHECK(quitButton.cb == Muted::Callbacks::exitFromTrayMenu);
        }

        SECTION("adds unmute button when microphone muted")
        {
            CHECK(std::string("Unmute") == unmuteButton.text);
            CHECK(unmuteButton.disabled == 0);
            CHECK(unmuteButton.context == context);
            CHECK(unmuteButton.cb == Muted::Callbacks::unmuteFromTrayMenu);
        }
    }

    SECTION("when microphone not muted")
    {
        REQUIRE_CALL(stateProvider, getState())
            .RETURN(Microphone::MicrophoneState::LIVE)
            .TIMES(1);

        REQUIRE_CALL(trayIcon, addTrayMenuItem(_))
            .LR_SIDE_EFFECT(muteButton = _1)
            .TIMES(1);

        REQUIRE_CALL(trayIcon, addTrayMenuItem(_))
            .LR_SIDE_EFFECT(quitButton = _1)
            .TIMES(1);

        REQUIRE_CALL(trayIcon, build()).TIMES(1);

        auto context = Muted::newTrayIcon(&trayIcon, &micController, &stateProvider);

        SECTION("adds Quit button")
        {
            CHECK(std::string(quitButton.text) == "Quit");
            CHECK(quitButton.disabled == 0);
            CHECK(quitButton.context == &trayIcon);
            CHECK(quitButton.cb == Muted::Callbacks::exitFromTrayMenu);
        }

        SECTION("adds unmute button when microphone muted")
        {
            CHECK(std::string(muteButton.text) == "Mute");
            CHECK(muteButton.disabled == 0);
            CHECK(muteButton.context == context);
            CHECK(muteButton.cb == Muted::Callbacks::muteFromTrayMenu);
        }
    }
}

TEST_CASE("Muted::Callbacks::unmuteFromTrayMenu", "[unmuteFromTrayMenu]")
{
    SECTION("unmutes and updates menu")
    {
        MicrophoneControllerMock micController;
        MicrophoneStateProviderMock stateProvider;
        TrayIconMock trayIcon;

        REQUIRE_CALL(micController, unmute()).TIMES(1);
        REQUIRE_CALL(trayIcon, clearMenuItems()).TIMES(1);
        REQUIRE_CALL(trayIcon, addTrayMenuItem(_)).TIMES(2);
        REQUIRE_CALL(stateProvider, getState())
            .RETURN(Microphone::MicrophoneState::LIVE)
            .TIMES(1);
        REQUIRE_CALL(trayIcon, update()).TIMES(1);

        Muted::TrayIconContext context{
            .trayIcon = &trayIcon,
            .controller = &micController,
            .stateProvider = &stateProvider
        };

        struct tray_menu trayMenu{.context = &context};
        Muted::Callbacks::unmuteFromTrayMenu(&trayMenu);
    }
}

TEST_CASE("Muted::Callbacks::muteFromTrayMenu", "[muteFromTrayMenu]")
{
    SECTION("mutes and updates menu")
    {
        MicrophoneControllerMock micController;
        MicrophoneStateProviderMock stateProvider;
        TrayIconMock trayIcon;

        REQUIRE_CALL(micController, mute()).TIMES(1);
        REQUIRE_CALL(trayIcon, clearMenuItems()).TIMES(1);
        REQUIRE_CALL(trayIcon, addTrayMenuItem(_)).TIMES(2);
        REQUIRE_CALL(stateProvider, getState())
            .RETURN(Microphone::MicrophoneState::MUTED)
            .TIMES(1);
        REQUIRE_CALL(trayIcon, update()).TIMES(1);

        Muted::TrayIconContext context{
            .trayIcon = &trayIcon,
            .controller = &micController,
            .stateProvider = &stateProvider
        };

        struct tray_menu trayMenu{.context = &context};
        Muted::Callbacks::muteFromTrayMenu(&trayMenu);
    }
}

TEST_CASE("Muted::Callbacks::exitFromTrayMenu", "[exitFromTrayMenu]")
{
    SECTION("calls exit on trayIcon")
    {
        TrayIconMock trayIcon;
        REQUIRE_CALL(trayIcon, exit()).TIMES(1);

        struct tray_menu trayMenu{.context = &trayIcon};
        Muted::Callbacks::exitFromTrayMenu(&trayMenu);
    }
}

TEST_CASE("Muted::updateTrayIcon")
{
    SECTION("clears menu and adds elements anew and calls update")
    {
        TrayIconMock trayIcon;
        MicrophoneControllerMock controller;
        MicrophoneStateProviderMock stateProvider;

        REQUIRE_CALL(stateProvider, getState())
            .RETURN(Microphone::MicrophoneState::MUTED)
            .TIMES(1);

        REQUIRE_CALL(trayIcon, clearMenuItems()).TIMES(1);

        REQUIRE_CALL(trayIcon, addTrayMenuItem(_)).TIMES(2);

        REQUIRE_CALL(trayIcon, update()).TIMES(1);

        Muted::TrayIconContext context{
            .trayIcon = &trayIcon,
            .controller = &controller,
            .stateProvider = &stateProvider
        };

        Muted::updateTrayIcon(&context);
    }
}