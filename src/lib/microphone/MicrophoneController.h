#ifndef MUTED_MICROPHONECONTROLLER_H
#define MUTED_MICROPHONECONTROLLER_H

#include <stdexcept>

namespace Microphone
{
    class MicrophoneControlException : std::exception {};

    class MicrophoneController
    {
    public:
        virtual void mute() = 0;

        virtual void unmute() = 0;
    };
}
#endif
