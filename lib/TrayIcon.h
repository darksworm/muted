#ifndef MUTED_TRAYICON_H
#define MUTED_TRAYICON_H

#include <external/tray/TrayIconProvider.h>
#include <vector>
#include <string>
#include <external/tray/src/tray.h>

namespace GUI
{
    class TrayIcon
    {
    public:
        virtual void build() = 0;

        virtual void addTrayMenuItem(struct tray_menu item) = 0;

        virtual int loop(int blocking) = 0;

        virtual void exit() = 0;
    };
}

#endif