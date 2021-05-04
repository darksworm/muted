#ifndef TRAY_ICON_SRC_H
#define TRAY_ICON_SRC_H

#include "lib/microphone/MicrophoneController.h"
#include "lib/microphone/MicrophoneStateProvider.h"

using namespace Microphone;
using namespace GUI;

namespace Muted
{
    struct TrayIconContext
    {
        TrayIcon *trayIcon;
        MicrophoneController *controller;
        MicrophoneStateProvider *stateProvider;
    };

    void updateTrayIcon(TrayIconContext *context);

    TrayIconContext *newTrayIcon(TrayIcon *icon, MicrophoneController *controller, MicrophoneStateProvider *provider);

    namespace Callbacks
    {
        void unmuteFromTrayMenu(tray_menu *menuItem);

        void muteFromTrayMenu(tray_menu *menuItem);

        void exitFromTrayMenu(tray_menu *menuItem);
    }
}
#endif