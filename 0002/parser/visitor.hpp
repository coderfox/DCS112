#pragma once

namespace ast
{

struct Expr;
struct Ident;
struct Monomial;
struct Unary;
struct Binary;
struct BinaryAssign;
struct BinaryEval;
struct FnCall;

} // namespace ast

class Visitor
{
  public:
    virtual void visit(const ast::Ident &value) = 0;
    virtual void visit(const ast::Monomial &value) = 0;
    virtual void visit(const ast::Unary &value) = 0;
    virtual void visit(const ast::Binary &value) = 0;
    virtual void visit(const ast::BinaryAssign &value) = 0;
    virtual void visit(const ast::BinaryEval &value) = 0;
    virtual void visit(const ast::FnCall &value) = 0;
};
