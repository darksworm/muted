#include <catch2/catch.hpp>

#include "lib/BashCodeExecutor.h"

TEST_CASE("BashCodeExecutor", "BashCodeExecutor")
{
    BashCodeExecutor executor;

    SECTION("echo yes has zero exit code and yes in output")
    {
        auto result = executor.execute("echo -n yes");

        CHECK(result.exitCode == 0);
        CHECK(result.output == "yes");
    }

    SECTION("exit 254 has 254 exit code")
    {
        auto result = executor.execute("exit 254");
        CHECK(result.exitCode == 254);
    }
}
