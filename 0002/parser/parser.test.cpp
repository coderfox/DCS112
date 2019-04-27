#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "catch.hpp"

using namespace std;

#define PARSER(str)            \
    auto input = string(str);  \
    auto lexer = Lexer(input); \
    lexer.parse();             \
    auto parser = Parser(lexer.cbegin(), lexer.cend());

TEST_CASE("class Parser > parsers")
{

    SECTION("term_integer")
    {
        PARSER("125");
        REQUIRE(parser.term_integer() == 125);
    }

    SECTION("term_ident")
    {
        PARSER("p");
        REQUIRE(*parser.term_ident() == ast::Ident("p"));
    }

    SECTION("term_monomial")
    {
        {
            PARSER("5x^2")
            REQUIRE(*parser.term_monomial() == ast::Monomial(5, 2));
        }
        {
            PARSER("x^2")
            REQUIRE(*parser.term_monomial() == ast::Monomial(1, 2));
        }
        {
            PARSER("x")
            REQUIRE(*parser.term_monomial() == ast::Monomial(1, 1));
        }
        {
            PARSER("5x")
            REQUIRE(*parser.term_monomial() == ast::Monomial(5, 1));
        }
        {
            PARSER("5")
            REQUIRE(*parser.term_monomial() == ast::Monomial(5, 0));
        }
    }

    SECTION("term_polynomial")
    {
        {
            PARSER("(1,2)(2,3)")
            REQUIRE(*parser.term_polynomial() ==
                    ast::Binary(
                        make_shared<ast::Monomial>(1, 2),
                        ast::Binary::ADD,
                        make_shared<ast::Monomial>(2, 3)));
        }
        {
            PARSER("(1,2)")
            REQUIRE(*parser.term_polynomial() == ast::Monomial(1, 2));
        }
    }

    SECTION("expr_terminal")
    {
        {
            PARSER("(1,2)(-2,3)")
            REQUIRE(*parser.expr_terminal() ==
                    ast::Binary(
                        make_shared<ast::Monomial>(1, 2),
                        ast::Binary::ADD,
                        make_shared<ast::Monomial>(-2, 3)));
        }
        {
            PARSER("x^2")
            REQUIRE(*parser.expr_terminal() == ast::Monomial(1, 2));
        }
        {
            PARSER("p")
            REQUIRE(*parser.expr_terminal() == ast::Ident("p"));
        }
        {
            PARSER("(2x^2-x^3)")
            REQUIRE(*parser.expr_terminal() ==
                    ast::Binary(
                        make_shared<ast::Monomial>(2, 2),
                        ast::Binary::SUBTRACT,
                        make_shared<ast::Monomial>(1, 3)));
        }
    }

    SECTION("expr_negative")
    {
        {
            PARSER("-p")
            REQUIRE(*parser.expr_negative() ==
                    ast::Unary(ast::Unary::MINUS,
                               make_shared<ast::Ident>("p")));
        }
        {
            PARSER("p")
            REQUIRE(*parser.expr_negative() == ast::Ident("p"));
        }
    }

    SECTION("expr_derive")
    {
        {
            PARSER("p'")
            REQUIRE(*parser.expr_derive() ==
                    ast::Unary(ast::Unary::DERIVE,
                               make_shared<ast::Ident>("p")));
        }
        {
            PARSER("(x^2+-x^3)'")
            REQUIRE(*parser.expr_derive() ==
                    ast::Unary(ast::Unary::DERIVE,
                               make_shared<ast::Binary>(
                                   make_shared<ast::Monomial>(1, 2),
                                   ast::Binary::ADD,
                                   make_shared<ast::Unary>(
                                       ast::Unary::MINUS,
                                       make_shared<ast::Monomial>(1, 3)))));
        }
    }

    SECTION("expr_multiply")
    {
        {
            PARSER("p*q")
            REQUIRE(*parser.expr_multiply() ==
                    ast::Binary(
                        make_shared<ast::Ident>("p"),
                        ast::Binary::MULTIPLY,
                        make_shared<ast::Ident>("q")));
        }
        {
            PARSER("p*q*r")
            REQUIRE(*parser.expr_multiply() ==
                    ast::Binary(
                        make_shared<ast::Binary>(
                            make_shared<ast::Ident>("p"),
                            ast::Binary::MULTIPLY,
                            make_shared<ast::Ident>("q")),
                        ast::Binary::MULTIPLY,
                        make_shared<ast::Ident>("r")));
        }
        {
            PARSER("p*(q*r)")
            REQUIRE(*parser.expr_multiply() ==
                    ast::Binary(
                        make_shared<ast::Ident>("p"),
                        ast::Binary::MULTIPLY,
                        make_shared<ast::Binary>(
                            make_shared<ast::Ident>("q"),
                            ast::Binary::MULTIPLY,
                            make_shared<ast::Ident>("r"))));
        }
    }

    SECTION("expr_sum_or_subtract")
    {
        {
            PARSER("p+q-(r*s)")
            REQUIRE(*parser.expr_sum_or_subtract() ==
                    ast::Binary(
                        make_shared<ast::Binary>(
                            make_shared<ast::Ident>("p"),
                            ast::Binary::ADD,
                            make_shared<ast::Ident>("q")),
                        ast::Binary::SUBTRACT,
                        make_shared<ast::Binary>(
                            make_shared<ast::Ident>("r"),
                            ast::Binary::MULTIPLY,
                            make_shared<ast::Ident>("s"))));
        }
    }

    SECTION("expr_eval")
    {
        {
            PARSER("p+q!5")
            REQUIRE(*parser.expr_eval() ==
                    ast::BinaryEval(
                        make_shared<ast::Binary>(
                            make_shared<ast::Ident>("p"),
                            ast::Binary::ADD,
                            make_shared<ast::Ident>("q")),
                        5));
        }
        {
            PARSER("p+q!-26")
            REQUIRE(*parser.expr_eval() ==
                    ast::BinaryEval(
                        make_shared<ast::Binary>(
                            make_shared<ast::Ident>("p"),
                            ast::Binary::ADD,
                            make_shared<ast::Ident>("q")),
                        -26));
        }
        {
            PARSER("x^2+2x'!12")
            REQUIRE(*parser.expr_eval() ==
                    ast::BinaryEval(
                        make_shared<ast::Unary>(
                            ast::Unary::DERIVE,
                            make_shared<ast::Binary>(
                                make_shared<ast::Monomial>(1, 2),
                                ast::Binary::ADD,
                                make_shared<ast::Monomial>(2, 1))),
                        12));
        }
    }

    SECTION("expr_equal")
    {
        {
            PARSER("o+p==q==r")
            REQUIRE(*parser.expr_equal() ==
                    ast::Binary(
                        make_shared<ast::Binary>(
                            make_shared<ast::Ident>("o"),
                            ast::Binary::ADD,
                            make_shared<ast::Ident>("p")),
                        ast::Binary::EQUAL,
                        make_shared<ast::Binary>(
                            make_shared<ast::Ident>("q"),
                            ast::Binary::EQUAL,
                            make_shared<ast::Ident>("r"))));
        }
    }

    SECTION("expr")
    {
        {
            PARSER("o=p=q")
            REQUIRE(*parser.expr() ==
                    ast::BinaryAssign(
                        make_shared<ast::Ident>("o"),
                        make_shared<ast::BinaryAssign>(
                            make_shared<ast::Ident>("p"),
                            make_shared<ast::Ident>("q"))));
        }
    }

    SECTION("#error")
    {
        PARSER("p=(q")
        REQUIRE_THROWS_AS(parser.expr(), Error);
        try
        {
            parser.reset();
            parser.expr();
        }
        catch (Error e)
        {
            REQUIRE(e.to_string() ==
                    "INPUT:4: p=(q\n"
                    "             ^\n"
                    "Expected: OP_RPAREN, ");
        }
    }
}

TEST_CASE("class Parser > parsers # empty")
{
    PARSER("")
    REQUIRE_THROWS_AS(parser.expr(), Error);
}
