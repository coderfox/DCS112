#include "parser.hpp"
#include "error.hpp"
#include "catch.hpp"

using namespace std;
using namespace ast;

#define MARK_SPAN_BEGIN \
    auto span_begin = _current

#define MARK_SPAN_GEN(d) \
    (span_begin->get_span() + (_current - d)->get_span())

// ===== Common Functions =====
Token Parser::match(Token::Type cur_ty)
{
    if (_current >= _end)
        throw cur_ty;

    auto &token = *_current;

    if (token != cur_ty)
        throw cur_ty;

    _current++;
    return token;
}

pair<Token, Token> Parser::match(Token::Type cur_ty, Token::Type next_ty)
{
    if (_current >= _end - 1)
        throw cur_ty;

    auto &cur = *_current;
    auto &next = *(_current + 1);

    if (cur != cur_ty)
        throw cur_ty;
    if (next != next_ty)
        throw next_ty;

    _current += 2;
    return make_pair(cur, next);
}

bool Parser::peak(Token::Type cur_ty)
{
    if (_current >= _end)
        return false;
    return *_current == cur_ty;
}

bool Parser::peak(Token::Type cur_ty, Token::Type next_ty)
{
    if (_current + 1 >= _end)
        return false;
    return *_current == cur_ty && *(_current + 1) == next_ty;
}

bool Parser::peak(Token::Type cur_ty, Token::Type next_ty, Token::Type next2_ty)
{
    if (_current + 2 >= _end)
        return false;
    return *_current == cur_ty &&
           *(_current + 1) == next_ty &&
           *(_current + 2) == next2_ty;
}

Error Parser::make_error(string message)
{
    return Error(_begin->get_span() + (_end - 1)->get_span(),
                 _current >= _end ? Span(
                                        (_end - 1)->get_span().end,
                                        (_end - 1)->get_span().end)
                                  : _current->get_span(),
                 message);
}

// ===== Constructors =====
Parser::Parser(const vector<Token> &input) : _begin(input.cbegin()),
                                             _end(input.cend()),
                                             _current(input.cbegin())
{
}

Parser::Parser(vector<Token>::const_iterator begin,
               vector<Token>::const_iterator end) : _begin(begin),
                                                    _end(end),
                                                    _current(begin)
{
}

// ===== Utilities =====
void Parser::reset()
{
    _current = _begin;
}

// ===== Parsers =====

// Integer    = @{ NUMBER+ }
unsigned int Parser::term_integer()
{
    try
    {
        auto token = match(Token::INTEGER);
        return stoi(string(token.get_span().begin, token.get_span().end));
    }
    catch (Token::Type)
    {
        throw make_error("Expected: integer");
    }
}

// Ident      = @{ ALPHABETIC+ }
shared_ptr<Expr> Parser::term_ident()
{
    try
    {
        MARK_SPAN_BEGIN;
        auto token = match(Token::IDENTIFIER);
        return make_shared<Ident>(MARK_SPAN_GEN(1), string(token.get_span().begin, token.get_span().end));
    }
    catch (Token::Type)
    {
        throw make_error("Expected: identifier");
    }
}

// Monomial   = { Integer | (Integer? ~ "x" ~ ("^" ~ Integer)? ) }
shared_ptr<Expr> Parser::term_monomial()
{
    MARK_SPAN_BEGIN;
    unsigned int coefficient = 1;
    unsigned int power = 0;
    if (peak(Token::INTEGER))
    {
        coefficient = term_integer();
    }
    else if (!peak(Token::VARIABLE))
        throw make_error("Expected: integer, variable");
    if (peak(Token::VARIABLE))
    {
        match(Token::VARIABLE);
        power = 1;
        if (peak(Token::OP_POW))
        {
            match(Token::OP_POW);
            try
            {
                power = term_integer();
            }
            catch (Error)
            {
                throw make_error("Expected: integer");
            }
        }
    }
    return make_shared<Monomial>(MARK_SPAN_GEN(1), coefficient, power);
}

// PolySingle = { "(" ~ "-"? ~ Integer ~ "," ~ Integer ~ ")" }
shared_ptr<ast::Expr> Parser::term_polynomial_single()
{
    MARK_SPAN_BEGIN;
    unsigned int coefficient = 1;
    unsigned int power = 0;

    if (!peak(Token::OP_LPAREN))
        throw make_error("Expected: polynomial_single");
    match(Token::OP_LPAREN);

    try
    {
        if (peak(Token::OP_SUBTRACT))
        {
            match(Token::OP_SUBTRACT);
            coefficient = -term_integer();
        }
        else
            coefficient = term_integer();
    }
    catch (Error)
    {
        throw make_error("Expected: integer");
    }

    if (!peak(Token::OP_COMMA))
        throw make_error("Expected: ','");
    match(Token::OP_COMMA);

    try
    {
        power = term_integer();
    }
    catch (Error)
    {
        throw make_error("Expected: integer");
    }

    if (!peak(Token::OP_RPAREN))
        throw make_error("Expected: ')'");
    match(Token::OP_RPAREN);

    return make_shared<Monomial>(MARK_SPAN_GEN(1), coefficient, power);
}

// Polynomial = { ("(" ~ Integer ~ "," ~ Integer ~ ")")+ }
shared_ptr<Expr> Parser::term_polynomial()
{
    MARK_SPAN_BEGIN;
    auto mono = term_polynomial_single();
    while (peak(Token::OP_LPAREN))
    {
        mono = make_shared<Binary>(MARK_SPAN_GEN(1), mono, Binary::ADD, term_polynomial_single());
    }
    return mono;
}

// Term       = { ("(" ~ Expr ~ ")") | Polynomial | Monomial | Ident }
shared_ptr<Expr> Parser::expr_terminal()
{
    // MARK_SPAN_BEGIN;
    if (peak(Token::OP_LPAREN, Token::INTEGER, Token::OP_COMMA))
    {
        return term_polynomial();
    }
    else if (peak(Token::OP_LPAREN))
    {
        match(Token::OP_LPAREN);
        auto ret = expr();
        if (peak(Token::OP_RPAREN))
        {
            match(Token::OP_RPAREN);
            return ret;
        }
        else
            throw make_error("Expected: ')'");
    }
    else if (peak(Token::INTEGER) || peak(Token::VARIABLE))
    {
        return term_monomial();
    }
    else if (peak(Token::IDENTIFIER))
    {
        return term_ident();
    }
    else
        throw make_error("Expected: (expr), polynomial, monomial, identifier");
}

// Expr4      = { ("-" ~ Term) | Term }
shared_ptr<Expr> Parser::expr_negative()
{
    MARK_SPAN_BEGIN;
    if (peak(Token::OP_SUBTRACT))
    {
        match(Token::OP_SUBTRACT);
        return make_shared<Unary>(MARK_SPAN_GEN(1), Unary::MINUS, expr_terminal());
    }
    else
        return expr_terminal();
}

// Expr2      = { Expr3 ~ ("*" ~ Expr3)* }
shared_ptr<Expr> Parser::expr_multiply()
{
    MARK_SPAN_BEGIN;
    auto expr = expr_negative();
    while (peak(Token::OP_MULTIPLY))
    {
        match(Token::OP_MULTIPLY);
        expr = make_shared<Binary>(MARK_SPAN_GEN(1), expr, Binary::MULTIPLY, expr_negative());
    }
    return expr;
}

// Expr1      = { Expr2 ~ (("+"|"-") ~ Expr2)* }
shared_ptr<Expr> Parser::expr_sum_or_subtract()
{
    MARK_SPAN_BEGIN;
    auto expr = expr_multiply();
    while (peak(Token::OP_ADD) || peak(Token::OP_SUBTRACT))
    {
        if (peak(Token::OP_ADD))
        {
            match(Token::OP_ADD);
            expr = make_shared<Binary>(MARK_SPAN_GEN(1), expr, Binary::ADD, expr_multiply());
        }
        else if (peak(Token::OP_SUBTRACT))
        {
            match(Token::OP_SUBTRACT);
            expr = make_shared<Binary>(MARK_SPAN_GEN(1), expr, Binary::SUBTRACT, expr_multiply());
        }
    }
    return expr;
}

// Expr3      = { (Expr4 ~ "'") | Expr4 }
shared_ptr<Expr> Parser::expr_derive()
{
    MARK_SPAN_BEGIN;
    auto expr = expr_sum_or_subtract();
    if (peak(Token::OP_DERIVE))
    {
        match(Token::OP_DERIVE);
        return make_shared<Unary>(MARK_SPAN_GEN(1), Unary::DERIVE, expr);
    }
    else
        return expr;
}

// ExprEval  = { Expr1 ~ ("!" ~ "-"? ~ Integer)? }
shared_ptr<ast::Expr> Parser::expr_eval()
{
    MARK_SPAN_BEGIN;
    auto expr = expr_derive();
    if (peak(Token::OP_BANG))
    {
        match(Token::OP_BANG);
        if (peak(Token::OP_SUBTRACT))
        {
            match(Token::OP_SUBTRACT);
            return make_shared<BinaryEval>(MARK_SPAN_GEN(1), expr, -term_integer());
        }
        else
            return make_shared<BinaryEval>(MARK_SPAN_GEN(1), expr, term_integer());
    }
    else
        return expr;
}

// Expr0      = { Expr1 ~ ("==" ~ Expr1)* }
shared_ptr<Expr> Parser::expr_equal()
{
    MARK_SPAN_BEGIN;
    auto expr = expr_eval();
    while (peak(Token::OP_EQ))
    {
        match(Token::OP_EQ);
        try
        {
            auto &expr_bin = dynamic_cast<Binary &>(*expr);
            if (expr_bin.op != Binary::EQUAL)
                throw bad_cast();
            expr_bin.right = make_shared<Binary>(MARK_SPAN_GEN(1), expr_bin.right, Binary::EQUAL, expr_eval());
        }
        catch (bad_cast &)
        {
            expr = make_shared<Binary>(MARK_SPAN_GEN(1), expr, Binary::EQUAL, expr_eval());
        }
    }
    return expr;
}

// Expr       = { (Expr0 ~ "=")* ~ Expr0 }
shared_ptr<Expr> Parser::expr()
{
    MARK_SPAN_BEGIN;
    auto expr = expr_equal();
    while (peak(Token::OP_ASSIGN))
    {
        match(Token::OP_ASSIGN);
        try
        {
            auto &expr_bin = dynamic_cast<BinaryAssign &>(*expr);
            expr_bin.value = make_shared<BinaryAssign>(MARK_SPAN_GEN(2), expr_bin.value, expr_equal());
        }
        catch (bad_cast &)
        {
            expr = make_shared<BinaryAssign>(MARK_SPAN_GEN(2), expr, expr_equal());
        }
    }
    return expr;
}

void Parser::ensure_finished()
{
    if (_current != _end)
    {
        throw make_error("Expected: END_OF_INPUT");
    }
}
