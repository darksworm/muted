#include <iostream>

int main(int argc, char *argv[])
{
#ifdef TRAY_APPINDICATOR
    std::cout << "yes";
#endif
}
