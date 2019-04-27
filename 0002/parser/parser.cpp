#include "parser.hpp"
#include "error.hpp"
#include "catch.hpp"

using namespace std;
using namespace ast;

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

Error Parser::make_error(std::string expected)
{
    return make_error(vector<string>{expected});
}
Error Parser::make_error(vector<string> expected)
{
    return Error(Span(_begin->get_span().begin, (_end - 1)->get_span().end),
                 _current >= _end ? Span(
                                        (_end - 1)->get_span().end,
                                        (_end - 1)->get_span().end)
                                  : _current->get_span(),
                 expected);
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
        throw make_error("INTEGER");
    }
}

// Ident      = @{ ALPHABETIC+ }
std::shared_ptr<Expr> Parser::term_ident()
{
    try
    {
        auto token = match(Token::IDENTIFIER);
        return make_shared<Ident>(string(token.get_span().begin, token.get_span().end));
    }
    catch (Token::Type)
    {
        throw make_error("IDENTIFIER");
    }
}

// Monomial   = { Integer | (Integer? ~ "x" ~ ("^" ~ Integer)? ) }
std::shared_ptr<Expr> Parser::term_monomial()
{
    unsigned int coefficient = 1;
    unsigned int power = 0;
    if (peak(Token::INTEGER))
    {
        coefficient = term_integer();
    }
    else if (!peak(Token::VARIABLE))
        throw make_error(vector<string>{"integer", "VARIABLE"});
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
                throw make_error("integer");
            }
        }
    }
    return make_shared<Monomial>(coefficient, power);
}

// PolySingle = { "(" ~ Integer ~ "," ~ Integer ~ ")" }
std::shared_ptr<ast::Expr> Parser::term_polynomial_single()
{
    unsigned int coefficient = 1;
    unsigned int power = 0;

    if (!peak(Token::OP_LPAREN))
        throw make_error("LPAREN");
    match(Token::OP_LPAREN);

    try
    {
        coefficient = term_integer();
    }
    catch (Error)
    {
        throw make_error("integer");
    }

    if (!peak(Token::OP_COMMA))
        throw make_error("COMMA");
    match(Token::OP_COMMA);

    try
    {
        power = term_integer();
    }
    catch (Error)
    {
        throw make_error("integer");
    }

    if (!peak(Token::OP_RPAREN))
        throw make_error("RPAROP_RPAREN");
    match(Token::OP_RPAREN);

    return make_shared<Monomial>(coefficient, power);
}

// Polynomial = { ("(" ~ Integer ~ "," ~ Integer ~ ")")+ }
std::shared_ptr<Expr> Parser::term_polynomial()
{
    auto mono = term_polynomial_single();
    while (peak(Token::OP_LPAREN))
    {
        mono = make_shared<Binary>(mono, Binary::ADD, term_polynomial_single());
    }
    return mono;
}

// Term       = { ("(" ~ Expr ~ ")") | Polynomial | Monomial | Ident }
std::shared_ptr<Expr> Parser::expr_terminal()
{
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
            throw make_error("OP_RPAREN");
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
        throw make_error(vector<string>{"OP_LPAREN", "polynomial", "monomial", "term_ident"});
}

// Expr4      = { ("-" ~ Term) | Term }
std::shared_ptr<Expr> Parser::expr_negative()
{
    if (peak(Token::OP_SUBTRACT))
    {
        match(Token::OP_SUBTRACT);
        return make_shared<Unary>(Unary::MINUS, expr_terminal());
    }
    else
        return expr_terminal();
}

// Expr2      = { Expr3 ~ ("*" ~ Expr3)* }
std::shared_ptr<Expr> Parser::expr_multiply()
{
    auto expr = expr_negative();
    while (peak(Token::OP_MULTIPLY))
    {
        match(Token::OP_MULTIPLY);
        expr = make_shared<Binary>(expr, Binary::MULTIPLY, expr_negative());
    }
    return expr;
}

// Expr1      = { Expr2 ~ (("+"|"-") ~ Expr2)* }
std::shared_ptr<Expr> Parser::expr_sum_or_subtract()
{
    auto expr = expr_multiply();
    while (peak(Token::OP_ADD) || peak(Token::OP_SUBTRACT))
    {
        if (peak(Token::OP_ADD))
        {
            match(Token::OP_ADD);
            expr = make_shared<Binary>(expr, Binary::ADD, expr_multiply());
        }
        else if (peak(Token::OP_SUBTRACT))
        {
            match(Token::OP_SUBTRACT);
            expr = make_shared<Binary>(expr, Binary::SUBTRACT, expr_multiply());
        }
    }
    return expr;
}

// Expr3      = { (Expr4 ~ "'") | Expr4 }
std::shared_ptr<Expr> Parser::expr_derive()
{
    auto expr = expr_sum_or_subtract();
    if (peak(Token::OP_DERIVE))
    {
        match(Token::OP_DERIVE);
        return make_shared<Unary>(Unary::DERIVE, expr);
    }
    else
        return expr;
}

// ExprEval  = { Expr1 ~ ("!" ~ "-"? ~ Integer)? }
std::shared_ptr<ast::Expr> Parser::expr_eval()
{
    auto expr = expr_derive();
    if (peak(Token::OP_BANG))
    {
        match(Token::OP_BANG);
        if (peak(Token::OP_SUBTRACT))
        {
            match(Token::OP_SUBTRACT);
            return make_shared<BinaryEval>(expr, -term_integer());
        }
        else
            return make_shared<BinaryEval>(expr, term_integer());
    }
    else
        return expr;
}

// Expr0      = { Expr1 ~ ("==" ~ Expr1)* }
std::shared_ptr<Expr> Parser::expr_equal()
{
    auto expr = expr_eval();
    while (peak(Token::OP_EQ))
    {
        match(Token::OP_EQ);
        try
        {
            auto &expr_bin = dynamic_cast<Binary &>(*expr);
            if (expr_bin.op != Binary::EQUAL)
                throw bad_cast();
            expr_bin.right = make_shared<Binary>(expr_bin.right, Binary::EQUAL, expr_eval());
        }
        catch (std::bad_cast)
        {
            expr = make_shared<Binary>(expr, Binary::EQUAL, expr_eval());
        }
    }
    return expr;
}

// Expr       = { (Expr0 ~ "=")* ~ Expr0 }
std::shared_ptr<Expr> Parser::expr()
{
    auto expr = expr_equal();
    while (peak(Token::OP_ASSIGN))
    {
        match(Token::OP_ASSIGN);
        try
        {
            auto &expr_bin = dynamic_cast<BinaryAssign &>(*expr);
            expr_bin.value = make_shared<BinaryAssign>(expr_bin.value, expr_equal());
        }
        catch (std::bad_cast)
        {
            expr = make_shared<BinaryAssign>(expr, expr_equal());
        }
    }
    return expr;
}
