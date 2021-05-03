#ifndef MUTED_BASHCODEEXECUTOR_H
#define MUTED_BASHCODEEXECUTOR_H

#include "CodeExecutor.h"

class BashCodeExecutor : public CodeExecutor
{
public:
    ExecutionResult execute(std::string command)
    {
        std::array<char, 128> buffer;
        std::string result;
        auto pipe = popen(command.c_str(), "r");

        if (!pipe)
        {
            throw std::runtime_error("popen() failed!");
        }

        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        {
            result += buffer.data();
        }

        return ExecutionResult {
            .output = std::string(result),
            .exitCode = WEXITSTATUS(pclose(pipe))
        };
    }
};

#endif
