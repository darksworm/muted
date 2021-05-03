#ifndef MUTED_CODEEXECUTOR_H
#define MUTED_CODEEXECUTOR_H

#include <string>

struct ExecutionResult
{
    std::string output;
    int exitCode;
};

class CodeExecutor
{
public:
    virtual ExecutionResult execute(std::string command) = 0;
};

#endif
