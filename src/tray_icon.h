#ifndef TRAY_ICON_SRC_H
#define TRAY_ICON_SRC_H

void initializeTrayIcon(GUI::TrayIcon &trayIcon)
{
    trayIcon.addTrayMenuItem(
        {
            .text = "Quit",
            .disabled = 0,
            .cb = [](tray_menu *) { exit(1); },
            .context = nullptr
        }
    );

    trayIcon.build();
}

#endif