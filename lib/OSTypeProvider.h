#ifndef OSTYPEPROVIDER_H
#define OSTYPEPROVIDER_H
#include <string>

namespace OS
{
    enum class OperatingSystem
    {
        Unknown, MacOS, Windows, Linux
    };

    template<class T>
    class OSTypeProvider
    {
    public:
        std::string getType()
        {
            return T::operatingSystemType();
        }

        OperatingSystem getEnumType()
        {
            auto type = getType();

            if (type == "windows")
            {
                return OperatingSystem::Windows;
            }

            if (type == "linux")
            {
                return OperatingSystem::Linux;
            }

            if (type == "macos")
            {
                return OperatingSystem::MacOS;
            }

            return OperatingSystem::Unknown;
        }
    };
}
#endif