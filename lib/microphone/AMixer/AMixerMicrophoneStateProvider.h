#ifndef MUTED_AMIXERMICROPHONESTATEPROVIDER_H
#define MUTED_AMIXERMICROPHONESTATEPROVIDER_H

#include "../MicrophoneStateProvider.h"
#include "../../CodeExecutor.h"

namespace Microphone
{
    class AMixerMicrophoneStateProvider : MicrophoneStateProvider
    {
    private:
        const char *microphoneStateQuery = "amixer get Capture | grep off";
        CodeExecutor &codeExecutor;

    protected:
        bool isMicrophoneMuted();

    public:
        explicit AMixerMicrophoneStateProvider(CodeExecutor &codeExecutor);

        MicrophoneState getState() override;
    };

}
#endif
