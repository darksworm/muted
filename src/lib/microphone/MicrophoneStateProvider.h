#ifndef MUTED_MICROPHONESTATEPROVIDER_H
#define MUTED_MICROPHONESTATEPROVIDER_H

namespace Microphone
{
    enum class MicrophoneState
    {
        MUTED, LIVE
    };

    class MicrophoneStateProvider
    {
    public:
        virtual MicrophoneState getState() = 0;
    };
}

#endif
