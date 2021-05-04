#ifndef MUTED_TRAYICON_H
#define MUTED_TRAYICON_H

#include <vector>
#include <string>
#include <lib/external/tray/src/tray.h>
#include <lib/tray/TrayIconProvider.h>

namespace GUI
{
    class TrayIcon
    {
    public:
        virtual void build() = 0;

        virtual void addTrayMenuItem(struct tray_menu item) = 0;

        virtual int loop(int blocking) = 0;

        virtual void exit() = 0;

        virtual void clearMenuItems() = 0;

        virtual void update() = 0;
    };
}

#endif