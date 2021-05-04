#ifndef MUTED_CROSS_PLATFORM_TRAY_ICON_PROVIDER_H
#define MUTED_CROSS_PLATFORM_TRAY_ICON_PROVIDER_H

#include "TrayIconProvider.h"
#include "lib/external/tray/src/tray.h"

namespace GUI
{
    class CrossPlatformTrayIconProvider : public GUI::TrayIconProvider
    {
        int init(void *context) override
        {
            return tray_init((struct tray *)context);
        }

        int loop(int blocking) override
        {
            return tray_loop(blocking);
        }

        void update(void *context) override
        {
            tray_update((struct tray *)context);
        }

        void exit() override
        {
            tray_exit();
        }
    };
}

#endif
