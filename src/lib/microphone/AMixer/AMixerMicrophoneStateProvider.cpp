#include "AMixerMicrophoneStateProvider.h"

namespace Microphone
{
    MicrophoneState AMixerMicrophoneStateProvider::getState()
    {
        if (isMicrophoneMuted())
        {
            return MicrophoneState::MUTED;
        }
        else
        {
            return MicrophoneState::LIVE;
        }
    }

    bool AMixerMicrophoneStateProvider::isMicrophoneMuted()
    {
        return !codeExecutor.execute(microphoneStateQuery).exitCode;
    }

    AMixerMicrophoneStateProvider::AMixerMicrophoneStateProvider(CodeExecutor &codeExecutor)
        : codeExecutor(codeExecutor)
    {

    }
}