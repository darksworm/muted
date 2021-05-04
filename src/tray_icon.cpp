#include <lib/tray/TrayIcon.h>
#include "tray_icon.h"

namespace Muted
{
    void createAndAddMenuItems(TrayIconContext *context);

    std::vector<tray_menu> createMenuItems(TrayIconContext *context);

    tray_menu createQuitButton(TrayIcon *icon);

    tray_menu createMicrophoneButton(TrayIconContext *context);

    void updateTrayIcon(TrayIconContext *context)
    {
        context->trayIcon->clearMenuItems();
        createAndAddMenuItems(context);
        context->trayIcon->update();
    }

    TrayIconContext *
    newTrayIcon(TrayIcon *icon, MicrophoneController *controller, MicrophoneStateProvider *provider)
    {
        auto *context = new TrayIconContext{
            .trayIcon = icon,
            .controller = controller,
            .stateProvider = provider
        };

        createAndAddMenuItems(context);
        icon->build();

        return context;
    }

    void createAndAddMenuItems(TrayIconContext *context)
    {
        for (auto &item : createMenuItems(context))
        {
            context->trayIcon->addTrayMenuItem(item);
        }
    }

    std::vector<tray_menu> createMenuItems(TrayIconContext *context)
    {
        std::vector<tray_menu> buttons{
            createQuitButton(context->trayIcon),
            createMicrophoneButton(context)
        };

        return buttons;
    }

    namespace Callbacks
    {
        void unmuteFromTrayMenu(tray_menu *menuItem)
        {
            auto context = (TrayIconContext *) menuItem->context;
            context->controller->unmute();
            updateTrayIcon(context);
        }

        void muteFromTrayMenu(tray_menu *menuItem)
        {
            auto context = (TrayIconContext *) menuItem->context;
            context->controller->mute();
            updateTrayIcon(context);
        }

        void exitFromTrayMenu(tray_menu *menuItem)
        {
            auto icon = (TrayIcon *) menuItem->context;
            icon->exit();
        }
    }

    tray_menu createUnmuteButton(TrayIconContext *context)
    {
        return {
            .text = "Unmute",
            .disabled = 0,
            .cb = Callbacks::unmuteFromTrayMenu,
            .context = context
        };
    }

    tray_menu createMuteButton(TrayIconContext *context)
    {
        return {
            .text = "Mute",
            .disabled = 0,
            .cb = Callbacks::muteFromTrayMenu,
            .context = context
        };
    }

    tray_menu createMicrophoneButton(TrayIconContext *context)
    {
        return context->stateProvider->getState() == MicrophoneState::MUTED
               ? createUnmuteButton(context)
               : createMuteButton(context);
    }

    tray_menu createQuitButton(TrayIcon *icon)
    {
        return {
            .text = "Quit",
            .disabled = 0,
            .cb = Callbacks::exitFromTrayMenu,
            .context = icon
        };
    }
}