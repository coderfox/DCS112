#pragma once

#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <iostream>
#include "visitor.hpp"
#include "span.hpp"

#define DECL_INHERIT_FUNCS(T)               \
    void accept(Visitor &visitor) const;    \
    bool operator==(const Expr &rhs) const; \
    std::ostream &print(std::ostream &out) const;

std::ostream &operator<<(std::ostream &out, const ast::Expr &value);

namespace ast
{

struct Expr : public HasSpan
{
    Expr(Span span);

    virtual void accept(Visitor &visitor) const = 0;
    virtual bool operator==(const Expr &rhs) const = 0;
    bool operator!=(const Expr &rhs) const;
    virtual std::ostream &print(std::ostream &out) const = 0;
    friend std::ostream & ::operator<<(std::ostream &out, const Expr &value);
};

struct Ident final : public Expr
{
    std::string value;

    Ident(Span span, std::string value);

    DECL_INHERIT_FUNCS(Ident)
};

struct Monomial final : public Expr
{
    int coefficient;
    unsigned int power;

    Monomial(Span span, int coefficient, unsigned int power);

    DECL_INHERIT_FUNCS(Monomial)
};

struct Unary final : public Expr
{
    typedef enum
    {
        MINUS,
        DERIVE,
    } Op;

    Op op;
    std::shared_ptr<Expr> operand;

    Unary(Span span, Op op, std::shared_ptr<Expr> operand);

    DECL_INHERIT_FUNCS(Unary)
};

struct Binary final : public Expr
{
    typedef enum
    {
        ADD,
        SUBTRACT,
        MULTIPLY,
        EQUAL,
    } Op;

    std::shared_ptr<Expr> left;
    Op op;
    std::shared_ptr<Expr> right;

    Binary(Span span, std::shared_ptr<Expr> left, Op op, std::shared_ptr<Expr> right);

    DECL_INHERIT_FUNCS(Binary)
};

struct BinaryAssign final : public Expr
{
    std::shared_ptr<Expr> id;
    std::shared_ptr<Expr> value;

    BinaryAssign(Span span, std::shared_ptr<Expr> id, std::shared_ptr<Expr> value);

    DECL_INHERIT_FUNCS(BinaryAssign)
};

struct BinaryEval final : public Expr
{
    int x;
    std::shared_ptr<Expr> expr;

    BinaryEval(Span span, std::shared_ptr<Expr> expr, int x);

    DECL_INHERIT_FUNCS(BinaryEval)
};

struct FnCall final : public Expr
{
    std::string fn;
    std::shared_ptr<Expr> arg;

    FnCall(Span span, std::string fn, std::shared_ptr<Expr> arg);

    DECL_INHERIT_FUNCS(FnCall)
};

} // namespace ast
