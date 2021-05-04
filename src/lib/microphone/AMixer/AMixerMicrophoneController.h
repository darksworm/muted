#include "../MicrophoneController.h"
#include "../../CodeExecutor.h"
#include "AMixerMicrophoneStateProvider.h"

#include <memory>
#include <utility>

namespace Microphone
{
    class AMixerMicrophoneController : MicrophoneController
    {
    private:
        std::unique_ptr<AMixerMicrophoneStateProvider> stateProvider;
        CodeExecutor &codeExecutor;
        const char *microphoneToggleCommand = "amixer set Capture toggle";

    protected:
        bool isMicrophoneMuted();

        ExecutionResult executeOrThrow(std::string command);

    public:
        AMixerMicrophoneController(CodeExecutor &executor);

        void mute() override;

        void unmute() override;
    };

}