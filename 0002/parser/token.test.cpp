#include "token.hpp"
#include "catch.hpp"

using namespace std;

TEST_CASE("class Token", "[parser][token]")
{
    string input = "sample";
    auto token = Token(Token::OP_POW, input.begin() + 1, input.end());
    SECTION("is")
    {
        REQUIRE(token.is(Token::OP_POW));
        REQUIRE_FALSE(token.is(Token::OP_SUBTRACT));
    }
    SECTION("to_string")
    {
        REQUIRE(token.to_string() == "OP_POW: (\"ample\")");
    }
    SECTION("operator==")
    {
        REQUIRE(token == Token(Token::OP_POW, input.begin() + 1, input.end()));
        REQUIRE_FALSE(token == Token(Token::OP_ADD, input.begin() + 1, input.end()));
        REQUIRE_FALSE(token == Token(Token::OP_POW, input.begin(), input.end()));
    }
}
