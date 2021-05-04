#ifndef MUTED_CROSSPLATFORMTRAYICON_H
#define MUTED_CROSSPLATFORMTRAYICON_H

#include "TrayIcon.h"

namespace GUI
{
    class CrossPlatformTrayIcon : public TrayIcon
    {
    private:
        TrayIconProvider &iconProvider;
        std::vector<struct tray_menu> menuItems;
        char *iconPath = "icon.png";
        struct tray tray = {};
    public:
        explicit CrossPlatformTrayIcon(TrayIconProvider &iconProvider) : iconProvider(iconProvider)
        {};

        void build() override
        {
            menuItems.push_back({nullptr, 0, 0, nullptr, nullptr});
            tray = {
                .icon = iconPath,
                .menu = &menuItems[0]
            };
            iconProvider.init(&tray);
        }

        void addTrayMenuItem(struct tray_menu item) override
        {
            menuItems.push_back(item);
        }

        int loop(int blocking) override
        {
            return iconProvider.loop(blocking);
        }

        void exit() override
        {
            iconProvider.exit();
        }

        void clearMenuItems() override
        {
            menuItems.clear();
        }

        void update() override
        {
            iconProvider.update(&tray);
        }
    };
}

#endif