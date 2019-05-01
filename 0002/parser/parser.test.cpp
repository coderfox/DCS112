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

#define PHANTOM_SPAN \
    Span(_phantom.begin(), _phantom.end())

TEST_CASE("class Parser > parsers")
{
    string _phantom = "hello";
    SECTION("term_integer")
    {
        PARSER("125");
        REQUIRE(parser.term_integer() == 125);
    }

    SECTION("term_ident")
    {
        PARSER("p");
        REQUIRE(*parser.term_ident() == ast::Ident(PHANTOM_SPAN, "p"));
    }

    SECTION("term_monomial")
    {
        {
            PARSER("5x^2")
            REQUIRE(*parser.term_monomial() == ast::Monomial(PHANTOM_SPAN, 5, 2));
        }
        {
            PARSER("x^2")
            REQUIRE(*parser.term_monomial() == ast::Monomial(PHANTOM_SPAN, 1, 2));
        }
        {
            PARSER("x")
            REQUIRE(*parser.term_monomial() == ast::Monomial(PHANTOM_SPAN, 1, 1));
        }
        {
            PARSER("5x")
            REQUIRE(*parser.term_monomial() == ast::Monomial(PHANTOM_SPAN, 5, 1));
        }
        {
            PARSER("5")
            REQUIRE(*parser.term_monomial() == ast::Monomial(PHANTOM_SPAN, 5, 0));
        }
    }

    SECTION("term_polynomial")
    {
        {
            PARSER("(1,2)(2,3)")
            REQUIRE(*parser.term_polynomial() ==
                    ast::Binary(
                        PHANTOM_SPAN,
                        make_shared<ast::Monomial>(PHANTOM_SPAN, 1, 2),
                        ast::Binary::ADD,
                        make_shared<ast::Monomial>(PHANTOM_SPAN, 2, 3)));
        }
        {
            PARSER("(1,2)")
            REQUIRE(*parser.term_polynomial() == ast::Monomial(PHANTOM_SPAN, 1, 2));
        }
    }

    SECTION("expr_terminal")
    {
        {
            PARSER("(1,2)(-2,3)")
            REQUIRE(*parser.expr_terminal() ==
                    ast::Binary(
                        PHANTOM_SPAN,
                        make_shared<ast::Monomial>(PHANTOM_SPAN, 1, 2),
                        ast::Binary::ADD,
                        make_shared<ast::Monomial>(PHANTOM_SPAN, -2, 3)));
        }
        {
            PARSER("x^2")
            REQUIRE(*parser.expr_terminal() == ast::Monomial(PHANTOM_SPAN, 1, 2));
        }
        {
            PARSER("p")
            REQUIRE(*parser.expr_terminal() == ast::Ident(PHANTOM_SPAN, "p"));
        }
        {
            PARSER("(2x^2-x^3)")
            REQUIRE(*parser.expr_terminal() ==
                    ast::Binary(
                        PHANTOM_SPAN,
                        make_shared<ast::Monomial>(PHANTOM_SPAN, 2, 2),
                        ast::Binary::SUBTRACT,
                        make_shared<ast::Monomial>(PHANTOM_SPAN, 1, 3)));
        }
    }

    SECTION("expr_negative")
    {
        {
            PARSER("-p")
            REQUIRE(*parser.expr_negative() ==
                    ast::Unary(
                        PHANTOM_SPAN,
                        ast::Unary::MINUS,
                        make_shared<ast::Ident>(PHANTOM_SPAN, "p")));
        }
        {
            PARSER("p")
            REQUIRE(*parser.expr_negative() == ast::Ident(PHANTOM_SPAN, "p"));
        }
    }

    SECTION("expr_derive")
    {
        {
            PARSER("p'")
            REQUIRE(*parser.expr_derive() ==
                    ast::Unary(
                        PHANTOM_SPAN,
                        ast::Unary::DERIVE,
                        make_shared<ast::Ident>(PHANTOM_SPAN, "p")));
        }
        {
            PARSER("(x^2+-x^3)'")
            REQUIRE(*parser.expr_derive() ==
                    ast::Unary(
                        PHANTOM_SPAN,
                        ast::Unary::DERIVE,
                        make_shared<ast::Binary>(
                            PHANTOM_SPAN,
                            make_shared<ast::Monomial>(PHANTOM_SPAN, 1, 2),
                            ast::Binary::ADD,
                            make_shared<ast::Unary>(
                                PHANTOM_SPAN,
                                ast::Unary::MINUS,
                                make_shared<ast::Monomial>(PHANTOM_SPAN, 1, 3)))));
        }
    }

    SECTION("expr_multiply")
    {
        {
            PARSER("p*q")
            REQUIRE(*parser.expr_multiply() ==
                    ast::Binary(
                        PHANTOM_SPAN,
                        make_shared<ast::Ident>(PHANTOM_SPAN, "p"),
                        ast::Binary::MULTIPLY,
                        make_shared<ast::Ident>(PHANTOM_SPAN, "q")));
        }
        {
            PARSER("p*q*r")
            REQUIRE(*parser.expr_multiply() ==
                    ast::Binary(
                        PHANTOM_SPAN,
                        make_shared<ast::Binary>(
                            PHANTOM_SPAN,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "p"),
                            ast::Binary::MULTIPLY,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "q")),
                        ast::Binary::MULTIPLY,
                        make_shared<ast::Ident>(PHANTOM_SPAN, "r")));
        }
        {
            PARSER("p*(q*r)")
            REQUIRE(*parser.expr_multiply() ==
                    ast::Binary(
                        PHANTOM_SPAN,
                        make_shared<ast::Ident>(PHANTOM_SPAN, "p"),
                        ast::Binary::MULTIPLY,
                        make_shared<ast::Binary>(
                            PHANTOM_SPAN,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "q"),
                            ast::Binary::MULTIPLY,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "r"))));
        }
    }

    SECTION("expr_sum_or_subtract")
    {
        {
            PARSER("p+q-(r*s)")
            REQUIRE(*parser.expr_sum_or_subtract() ==
                    ast::Binary(
                        PHANTOM_SPAN,
                        make_shared<ast::Binary>(
                            PHANTOM_SPAN,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "p"),
                            ast::Binary::ADD,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "q")),
                        ast::Binary::SUBTRACT,
                        make_shared<ast::Binary>(
                            PHANTOM_SPAN,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "r"),
                            ast::Binary::MULTIPLY,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "s"))));
        }
    }

    SECTION("expr_eval")
    {
        {
            PARSER("p+q!5")
            REQUIRE(*parser.expr_eval() ==
                    ast::BinaryEval(
                        PHANTOM_SPAN,
                        make_shared<ast::Binary>(
                            PHANTOM_SPAN,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "p"),
                            ast::Binary::ADD,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "q")),
                        5));
        }
        {
            PARSER("p+q!-26")
            REQUIRE(*parser.expr_eval() ==
                    ast::BinaryEval(
                        PHANTOM_SPAN,
                        make_shared<ast::Binary>(
                            PHANTOM_SPAN,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "p"),
                            ast::Binary::ADD,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "q")),
                        -26));
        }
        {
            PARSER("x^2+2x'!12")
            REQUIRE(*parser.expr_eval() ==
                    ast::BinaryEval(
                        PHANTOM_SPAN,
                        make_shared<ast::Unary>(
                            PHANTOM_SPAN,
                            ast::Unary::DERIVE,
                            make_shared<ast::Binary>(
                                PHANTOM_SPAN,
                                make_shared<ast::Monomial>(PHANTOM_SPAN, 1, 2),
                                ast::Binary::ADD,
                                make_shared<ast::Monomial>(PHANTOM_SPAN, 2, 1))),
                        12));
        }
    }

    SECTION("expr_equal")
    {
        {
            PARSER("o+p==q==r")
            REQUIRE(*parser.expr_equal() ==
                    ast::Binary(
                        PHANTOM_SPAN,
                        make_shared<ast::Binary>(
                            PHANTOM_SPAN,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "o"),
                            ast::Binary::ADD,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "p")),
                        ast::Binary::EQUAL,
                        make_shared<ast::Binary>(
                            PHANTOM_SPAN,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "q"),
                            ast::Binary::EQUAL,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "r"))));
        }
    }

    SECTION("expr")
    {
        {
            PARSER("o=p=q")
            REQUIRE(*parser.expr() ==
                    ast::BinaryAssign(
                        PHANTOM_SPAN,
                        make_shared<ast::Ident>(PHANTOM_SPAN, "o"),
                        make_shared<ast::BinaryAssign>(
                            PHANTOM_SPAN,
                            make_shared<ast::Ident>(PHANTOM_SPAN, "p"),
                            make_shared<ast::Ident>(PHANTOM_SPAN, "q"))));
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
#ifdef NO_COLOR_OUTPUT
            REQUIRE(e.to_string() ==
                    "INPUT:4: p=(q\n"
                    "             ^\n"
                    "Expected: ')'");
#else
            REQUIRE_NOTHROW(e.to_string());
#endif
        }
    }
}

TEST_CASE("class Parser > parsers # empty")
{
    PARSER("")
    REQUIRE_THROWS_AS(parser.expr(), Error);
}

TEST_CASE("class Parser > parsers # end expect")
{
    PARSER("2x^")
    REQUIRE_THROWS_AS(parser.expr(), Error);
    try
    {
        parser.expr();
    }
    catch (Error e)
    {
        REQUIRE_NOTHROW(e.to_string());
    }
}
