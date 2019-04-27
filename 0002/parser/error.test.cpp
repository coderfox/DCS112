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
        vector<string>{"hello", "world"});
    SECTION("to_string")
    {
        REQUIRE(error.to_string() == "sample error input\n"
                                     "       ^^^^^\n"
                                     "Expected: hello, world, ");
    }
}
