#include "error.hpp"
#include "catch.hpp"

using namespace std;

TEST_CASE("class Error", "[parser][error]")
{
    //              0123456789012345678
    string input = "sample error input";
    auto error = Error(
        Span(input.cbegin(), input.cend()),
        Span(input.cbegin() + 7, input.cbegin() + 12),
        "Expected: hello, world, ");
    SECTION("to_string")
    {
#ifdef NO_COLOR_OUTPUT
        REQUIRE(error.to_string() == "INPUT:7: sample error input\n"
                                     "                ^^^^^\n"
                                     "Expected: hello, world, ");
#else
        REQUIRE_NOTHROW(error.to_string());
#endif
    }
}
TEST_CASE("class Error # empty", "[parser][error]")
{
    string input = "";
    auto error = Error(
        Span(input.cend(), input.cend()),
        Span(input.cend(), input.cend()),
        "Expected: hello, world, ");
    SECTION("to_string")
    {
        REQUIRE_NOTHROW(error.to_string());
    }
}
