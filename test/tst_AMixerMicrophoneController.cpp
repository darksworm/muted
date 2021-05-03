#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include "../lib/CodeExecutor.h"
#include "../lib/microphone/AMixer/AMixerMicrophoneController.h"

class MockCodeExecutor : public CodeExecutor
{
public:
    MAKE_MOCK1 (execute, ExecutionResult(std::string), override);
};

TEST_CASE("AMixerMicrophoneController", "[AMixerMicrophoneController]")
{
    MockCodeExecutor executorMock;
    Microphone::AMixerMicrophoneController controller(executorMock);

    const char *microphoneToggleCommand = "amixer set Capture toggle";
    const char *microphoneStateQuery = "amixer get Capture | grep off";

    ExecutionResult microphoneOffResult{
        .exitCode = 0
    };
    ExecutionResult microphoneOnResult{
        .exitCode = 1
    };

    SECTION("mutes when not muted")
    {
        REQUIRE_CALL(executorMock, execute(microphoneStateQuery))
            .RETURN(microphoneOnResult)
            .TIMES(1);

        REQUIRE_CALL(executorMock, execute(microphoneToggleCommand))
            .RETURN(ExecutionResult{.exitCode = 0})
            .TIMES(1);

        controller.mute();
    }

    SECTION("unmutes when muted")
    {
        REQUIRE_CALL(executorMock, execute(microphoneStateQuery))
            .RETURN(microphoneOffResult)
            .TIMES(1);

        REQUIRE_CALL(executorMock, execute(microphoneToggleCommand))
            .RETURN(ExecutionResult{.exitCode = 0})
            .TIMES(1);

        controller.unmute();
    }

    SECTION("doesn't mute when already muted")
    {
        REQUIRE_CALL(executorMock, execute(microphoneStateQuery))
            .RETURN(microphoneOffResult)
            .TIMES(1);

        FORBID_CALL(executorMock, execute(microphoneToggleCommand));

        controller.mute();
    }

    SECTION("doesn't unmute when already unmuted")
    {
        REQUIRE_CALL(executorMock, execute(microphoneStateQuery))
            .RETURN(microphoneOnResult)
            .TIMES(1);

        FORBID_CALL(executorMock, execute(microphoneToggleCommand));

        controller.unmute();
    }

    struct ThrowExceptionCase
    {
        std::string description;
        ExecutionResult queryResult;
        std::function<void(void)> thrower;
    };

    struct ThrowExceptionCase tests[] = {
        {
            .description = "throws when mute fails",
            .queryResult = microphoneOnResult,
            .thrower = [&] { controller.mute(); }
        },
        {
            .description = "throws when unmute fails",
            .queryResult = microphoneOffResult,
            .thrower = [&] { controller.unmute(); }
        }
    };

    for (const auto &test: tests)
    {
        SECTION(test.description)
        {
            REQUIRE_CALL(executorMock, execute(microphoneStateQuery))
                .RETURN(test.queryResult)
                .TIMES(1);

            REQUIRE_CALL(executorMock, execute(microphoneToggleCommand))
                .RETURN(ExecutionResult{.exitCode = 254})
                .TIMES(1);

            REQUIRE_THROWS(test.thrower());
        }
    }
}