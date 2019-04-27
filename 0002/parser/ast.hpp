#pragma once

#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <iostream>
#include "visitor.hpp"

#define DECL_INHERIT_FUNCS(T)               \
    void accept(Visitor &visitor) const;    \
    bool operator==(const Expr &rhs) const; \
    std::ostream &print(std::ostream &out) const;

namespace ast
{

struct Expr
{
    virtual void accept(Visitor &visitor) const = 0;
    virtual bool operator==(const Expr &rhs) const = 0;
    bool operator!=(const Expr &rhs) const;
    virtual std::ostream &print(std::ostream &out) const = 0;
    friend std::ostream &operator<<(std::ostream &out, const Expr &value);
};

struct Ident final : public Expr
{
    std::string value;

    Ident(std::string value);

    DECL_INHERIT_FUNCS(Ident)
};

struct Monomial final : public Expr
{
    unsigned int coefficient;
    unsigned int power;

    Monomial(unsigned int coefficient, unsigned int power);

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

    Unary(Op op, std::shared_ptr<Expr> operand);

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

    Binary(std::shared_ptr<Expr> left, Op op, std::shared_ptr<Expr> right);

    DECL_INHERIT_FUNCS(Binary)
};

struct BinaryAssign final : public Expr
{
    std::shared_ptr<Expr> id;
    std::shared_ptr<Expr> value;

    BinaryAssign(std::shared_ptr<Expr> id, std::shared_ptr<Expr> value);

    DECL_INHERIT_FUNCS(BinaryAssign)
};

struct BinaryEval final : public Expr
{
    int x;
    std::shared_ptr<Expr> expr;

    BinaryEval(std::shared_ptr<Expr> expr, int x);

    DECL_INHERIT_FUNCS(BinaryEval)
};

} // namespace ast
