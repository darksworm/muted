#include <memory>
#include <utility>
#include "AMixerMicrophoneController.h"

namespace Microphone
{
    bool AMixerMicrophoneController::isMicrophoneMuted()
    {
        return stateProvider->getState() == MicrophoneState::MUTED;
    }

    void AMixerMicrophoneController::unmute()
    {
        if (isMicrophoneMuted())
        {
            executeOrThrow(microphoneToggleCommand);
        }
    }

    void AMixerMicrophoneController::mute()
    {
        if (!isMicrophoneMuted())
        {
            executeOrThrow(microphoneToggleCommand);
        }
    }

    AMixerMicrophoneController::AMixerMicrophoneController(CodeExecutor &executor) : codeExecutor(executor)
    {
        stateProvider = std::make_unique<AMixerMicrophoneStateProvider>(executor);
    }

    ExecutionResult AMixerMicrophoneController::executeOrThrow(std::string command)
    {
        auto result = codeExecutor.execute(std::move(command));
        if (result.exitCode != 0)
        {
            throw MicrophoneControlException();
        }

        return result;
    }
}