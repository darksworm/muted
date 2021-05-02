#include "external/tray/CrossPlatformTrayIconProvider.h"
#include "../lib/TrayIcon.h"
#include "tray_icon.h"
#include "../lib/CrossPlatformTrayIcon.h"

int main(int argc, char *argv[])
{
    GUI::CrossPlatformTrayIconProvider provider;
    GUI::CrossPlatformTrayIcon trayIcon(provider);

    initializeTrayIcon(trayIcon);

    while (trayIcon.loop(1) == 0);
}