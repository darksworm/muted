#ifndef TRAY_ICON_PROVIDER_H
#define TRAY_ICON_PROVIDER_H

namespace GUI
{
    class TrayIconProvider
    {
    public:
        virtual int init(void *context) = 0;

        virtual int loop(int blocking) = 0;

        virtual void update(void *context) = 0;

        virtual void exit() = 0;
    };
}

#endif
