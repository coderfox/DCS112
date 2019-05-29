#include <map>
#include <vector>
#include <sstream>
#include "lexer.hpp"
#include <iterator>
#include "catch.hpp"
#include "error.hpp"

using namespace std;

TEST_CASE("class Lexer > constructor & accessor", "[parser][lexer]")
{
    string input = "sample input";
    auto lexer = Lexer(input);
    auto lexer_iter = Lexer(input.cbegin(), input.cend());
    SECTION("lexer-string constructor")
    {
        stringstream ss;
        copy(lexer.cstr_begin(), lexer.cstr_end(), ostream_iterator<char>(ss));
        REQUIRE(ss.str() == input);
        REQUIRE(lexer.cstr_current() == lexer.cstr_begin());
        REQUIRE_FALSE(lexer.finished());
    }
    SECTION("lexer-iterator constructor")
    {
        stringstream ss;
        copy(lexer_iter.cstr_begin(), lexer_iter.cstr_end(), ostream_iterator<char>(ss));
        REQUIRE(ss.str() == input);
        REQUIRE(lexer_iter.cstr_current() == lexer.cstr_begin());
        REQUIRE_FALSE(lexer_iter.finished());
    }
}

TEST_CASE("class Lexer > sub-parsers", "[parser][lexer]")
{
    //              0         1         2
    //              012345678901234567890123456
    string input = "(5x^2+8x-16)' + 4x*8 =p,! ";
    auto lexer_void = Lexer(input.cbegin() + 25, input.cend());
    SECTION("integer")
    {
        auto lexer_integer = Lexer(input.cbegin() + 1, input.cend());
        auto lexer_integer2 = Lexer(input.cbegin() + 9, input.cend());
        REQUIRE(lexer_integer.integer() ==
                Token(Token::INTEGER, input.cbegin() + 1, input.cbegin() + 2));
        REQUIRE(lexer_integer2.integer() ==
                Token(Token::INTEGER, input.cbegin() + 9, input.cbegin() + 11));
    }
    SECTION("ident")
    {
        auto lexer_ident = Lexer(input.cbegin() + 22, input.cend());
        auto lexer_x = Lexer(input.cbegin() + 2, input.cend());
        REQUIRE(lexer_ident.ident() ==
                Token(Token::IDENTIFIER, input.cbegin() + 22, input.cbegin() + 23));
        REQUIRE(lexer_x.ident() ==
                Token(Token::VARIABLE, input.cbegin() + 2, input.cbegin() + 3));
    }
    SECTION("add")
    {
        auto lexer = Lexer(input.cbegin() + 5, input.cend());
        REQUIRE(lexer.add() ==
                Token(Token::OP_ADD, input.cbegin() + 5, input.cbegin() + 6));
    }
    SECTION("subtract")
    {
        auto lexer = Lexer(input.cbegin() + 8, input.cend());
        REQUIRE(lexer.subtract() ==
                Token(Token::OP_SUBTRACT, input.cbegin() + 8, input.cbegin() + 9));
    }
    SECTION("expr_multiply")
    {
        auto lexer = Lexer(input.cbegin() + 18, input.cend());
        REQUIRE(lexer.multiply() ==
                Token(Token::OP_MULTIPLY, input.cbegin() + 18, input.cbegin() + 19));
    }
    SECTION("derive")
    {
        auto lexer = Lexer(input.cbegin() + 12, input.cend());
        REQUIRE(lexer.derive() ==
                Token(Token::OP_DERIVE, input.cbegin() + 12, input.cbegin() + 13));
    }
    SECTION("lparen")
    {
        auto lexer = Lexer(input.cbegin() + 0, input.cend());
        REQUIRE(lexer.lparen() ==
                Token(Token::OP_LPAREN, input.cbegin() + 0, input.cbegin() + 1));
    }
    SECTION("rparen")
    {
        auto lexer = Lexer(input.cbegin() + 11, input.cend());
        REQUIRE(lexer.rparen() ==
                Token(Token::OP_RPAREN, input.cbegin() + 11, input.cbegin() + 12));
    }
    SECTION("pow")
    {
        auto lexer = Lexer(input.cbegin() + 3, input.cend());
        REQUIRE(lexer.pow() ==
                Token(Token::OP_POW, input.cbegin() + 3, input.cbegin() + 4));
    }
    SECTION("comma")
    {
        auto lexer = Lexer(input.cbegin() + 23, input.cend());
        REQUIRE(lexer.comma() ==
                Token(Token::OP_COMMA, input.cbegin() + 23, input.cbegin() + 24));
    }
    SECTION("bang")
    {
        auto lexer = Lexer(input.cbegin() + 24, input.cend());
        REQUIRE(lexer.bang() ==
                Token(Token::OP_BANG, input.cbegin() + 24, input.cbegin() + 25));
    }
    SECTION("whitespace")
    {
        auto lexer = Lexer(input.cbegin() + 25, input.cend());
        lexer.whitespace();
        REQUIRE(lexer.finished());
    }
    SECTION("void")
    {
        REQUIRE(lexer_void.integer() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.ident() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.add() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.subtract() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.multiply() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.derive() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.lparen() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.rparen() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.pow() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.comma() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
        REQUIRE(lexer_void.bang() ==
                Token(Token::VOID, input.cbegin() + 25, input.cbegin() + 25));
    }
}

TEST_CASE("class Lexer > parsers", "[parser][lexer]")
{
    //              0         1         2
    //              0123456789012345678901234567
    string input = "(5x^2+8x-16)' + 4X*8 =p==! ";
    auto lexer = Lexer(input.cbegin(), input.cend());
    auto lexer_parse = Lexer(input.cbegin(), input.cend());
    string wrong = "###";
    auto lexer_wrong = Lexer(wrong.cbegin(), wrong.cend());

    SECTION("advance")
    {
        REQUIRE(lexer.advance() == Token(Token::OP_LPAREN, input.cbegin() + 0, input.cbegin() + 1));
        REQUIRE(lexer.advance() == Token(Token::INTEGER, input.cbegin() + 1, input.cbegin() + 2));
        REQUIRE(lexer.advance() == Token(Token::VARIABLE, input.cbegin() + 2, input.cbegin() + 3));
        REQUIRE(lexer.advance() == Token(Token::OP_POW, input.cbegin() + 3, input.cbegin() + 4));
        REQUIRE(lexer.advance() == Token(Token::INTEGER, input.cbegin() + 4, input.cbegin() + 5));
        REQUIRE(lexer.advance() == Token(Token::OP_ADD, input.cbegin() + 5, input.cbegin() + 6));
        REQUIRE(lexer.advance() == Token(Token::INTEGER, input.cbegin() + 6, input.cbegin() + 7));
        REQUIRE(lexer.advance() == Token(Token::VARIABLE, input.cbegin() + 7, input.cbegin() + 8));
        REQUIRE(lexer.advance() == Token(Token::OP_SUBTRACT, input.cbegin() + 8, input.cbegin() + 9));
        REQUIRE(lexer.advance() == Token(Token::INTEGER, input.cbegin() + 9, input.cbegin() + 11));
        REQUIRE(lexer.advance() == Token(Token::OP_RPAREN, input.cbegin() + 11, input.cbegin() + 12));
        REQUIRE(lexer.advance() == Token(Token::OP_DERIVE, input.cbegin() + 12, input.cbegin() + 13));
        REQUIRE(lexer.advance() == Token(Token::OP_ADD, input.cbegin() + 14, input.cbegin() + 15));
        REQUIRE(lexer.advance() == Token(Token::INTEGER, input.cbegin() + 16, input.cbegin() + 17));
        REQUIRE(lexer.advance() == Token(Token::VARIABLE, input.cbegin() + 17, input.cbegin() + 18));
        REQUIRE(lexer.advance() == Token(Token::OP_MULTIPLY, input.cbegin() + 18, input.cbegin() + 19));
        REQUIRE(lexer.advance() == Token(Token::INTEGER, input.cbegin() + 19, input.cbegin() + 20));
        REQUIRE(lexer.advance() == Token(Token::OP_ASSIGN, input.cbegin() + 21, input.cbegin() + 22));
        REQUIRE(lexer.advance() == Token(Token::IDENTIFIER, input.cbegin() + 22, input.cbegin() + 23));
        REQUIRE(lexer.advance() == Token(Token::OP_EQ, input.cbegin() + 23, input.cbegin() + 25));
        REQUIRE(lexer.advance() == Token(Token::OP_BANG, input.cbegin() + 25, input.cbegin() + 26));
        REQUIRE(lexer.advance() == Token(Token::VOID, input.cend(), input.cend()));
    }
    SECTION("parse")
    {
        lexer_parse.parse();
        auto iter = lexer_parse.cbegin();
        REQUIRE(lexer_parse.token_count() == 21);
        REQUIRE(*(iter++) == Token(Token::OP_LPAREN, input.cbegin() + 0, input.cbegin() + 1));
        REQUIRE(*(iter++) == Token(Token::INTEGER, input.cbegin() + 1, input.cbegin() + 2));
        REQUIRE(*(iter++) == Token(Token::VARIABLE, input.cbegin() + 2, input.cbegin() + 3));
        REQUIRE(*(iter++) == Token(Token::OP_POW, input.cbegin() + 3, input.cbegin() + 4));
        REQUIRE(*(iter++) == Token(Token::INTEGER, input.cbegin() + 4, input.cbegin() + 5));
        REQUIRE(*(iter++) == Token(Token::OP_ADD, input.cbegin() + 5, input.cbegin() + 6));
        REQUIRE(*(iter++) == Token(Token::INTEGER, input.cbegin() + 6, input.cbegin() + 7));
        REQUIRE(*(iter++) == Token(Token::VARIABLE, input.cbegin() + 7, input.cbegin() + 8));
        REQUIRE(*(iter++) == Token(Token::OP_SUBTRACT, input.cbegin() + 8, input.cbegin() + 9));
        REQUIRE(*(iter++) == Token(Token::INTEGER, input.cbegin() + 9, input.cbegin() + 11));
        REQUIRE(*(iter++) == Token(Token::OP_RPAREN, input.cbegin() + 11, input.cbegin() + 12));
        REQUIRE(*(iter++) == Token(Token::OP_DERIVE, input.cbegin() + 12, input.cbegin() + 13));
        REQUIRE(*(iter++) == Token(Token::OP_ADD, input.cbegin() + 14, input.cbegin() + 15));
        REQUIRE(*(iter++) == Token(Token::INTEGER, input.cbegin() + 16, input.cbegin() + 17));
        REQUIRE(*(iter++) == Token(Token::VARIABLE, input.cbegin() + 17, input.cbegin() + 18));
        REQUIRE(*(iter++) == Token(Token::OP_MULTIPLY, input.cbegin() + 18, input.cbegin() + 19));
        REQUIRE(*(iter++) == Token(Token::INTEGER, input.cbegin() + 19, input.cbegin() + 20));
        REQUIRE(*(iter++) == Token(Token::OP_ASSIGN, input.cbegin() + 21, input.cbegin() + 22));
        REQUIRE(*(iter++) == Token(Token::IDENTIFIER, input.cbegin() + 22, input.cbegin() + 23));
        REQUIRE(*(iter++) == Token(Token::OP_EQ, input.cbegin() + 23, input.cbegin() + 25));
        REQUIRE(*(iter++) == Token(Token::OP_BANG, input.cbegin() + 25, input.cbegin() + 26));
    }
    SECTION("wrong")
    {
        REQUIRE_THROWS_AS(lexer_wrong.parse(), vector<Error>);
    }
}

TEST_CASE("class Lexer > parsers # fix last token", "[parser][lexer]")
{
    //              0123
    string input = "5x^2";
    auto lexer = Lexer(input.cbegin(), input.cend());
    lexer.parse();

    SECTION("advance parse")
    {
        REQUIRE(lexer.token_count() == 4);
        REQUIRE(*(lexer.cbegin() + 0) == Token(Token::INTEGER, input.cbegin() + 0, input.cbegin() + 1));
        REQUIRE(*(lexer.cbegin() + 1) == Token(Token::VARIABLE, input.cbegin() + 1, input.cbegin() + 2));
        REQUIRE(*(lexer.cbegin() + 2) == Token(Token::OP_POW, input.cbegin() + 2, input.cbegin() + 3));
        REQUIRE(*(lexer.cbegin() + 3) == Token(Token::INTEGER, input.cbegin() + 3, input.cbegin() + 4));
    }
}

TEST_CASE("class Lexer > parsers # fix single token", "[parser][lexer]")
{
    //                  012
    auto lexer = Lexer("999");
    lexer.parse();
    REQUIRE(lexer.token_count() == 1);
}

TEST_CASE("class Lexer > parsers # fix empty", "[parser][lexer]")
{
    auto lexer = Lexer("");
    REQUIRE_NOTHROW(lexer.parse());
    REQUIRE(lexer.token_count() == 0);
}

TEST_CASE("class Lexer > parsers # fix unexpected", "[parser][lexer]")
{
    auto lexer = Lexer("#");

    // REQUIRE_THROWS_AS(lexer.parse(), vector<Error>);
    try
    {
        lexer.parse();
    }
    catch (vector<Error> es)
    {
        for (auto it : es)
            REQUIRE_NOTHROW(it.to_string());
    }
}
