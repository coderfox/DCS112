#include "ast.hpp"

using namespace std;
using namespace ast;

#define IMPL_ACCEPT(T)                     \
    void T::accept(Visitor &visitor) const \
    {                                      \
        visitor.visit(*this);              \
    }

// ===== Constructor =====

Expr::Expr(Span span) : HasSpan(span)
{
}

Ident::Ident(Span span, string value) : Expr(span), value(value)
{
}

Monomial::Monomial(
    Span span,
    int coefficient,
    unsigned int power) : Expr(span), coefficient(coefficient), power(power)
{
}

Unary::Unary(
    Span span,
    Op op,
    shared_ptr<Expr> operand) : Expr(span), op(op), operand(operand)
{
}

Binary::Binary(
    Span span,
    shared_ptr<Expr> left,
    Op op,
    shared_ptr<Expr> right) : Expr(span), left(left), op(op), right(right)
{
}

BinaryAssign::BinaryAssign(
    Span span,
    shared_ptr<Expr> id,
    shared_ptr<Expr> value) : Expr(span), id(id), value(value)
{
}

BinaryEval::BinaryEval(
    Span span,
    shared_ptr<Expr> expr, int x) : Expr(span), x(x), expr(expr)
{
}

FnCall::FnCall(Span span,
               string fn, shared_ptr<Expr> arg) : Expr(span), fn(fn), arg(arg)
{
}

// ===== Equal =====

bool Expr::operator!=(const Expr &rhs) const
{
    return !(*this == rhs);
}

bool Ident::operator==(const Expr &rhs) const
{
    return typeid(*this) == typeid(rhs) &&
           (value == dynamic_cast<const Ident &>(rhs).value);
}

bool Monomial::operator==(const Expr &rhs) const
{
    return typeid(*this) == typeid(rhs) &&
           (coefficient == dynamic_cast<const Monomial &>(rhs).coefficient) &&
           (power == dynamic_cast<const Monomial &>(rhs).power);
}

bool Unary::operator==(const Expr &rhs) const
{
    return typeid(*this) == typeid(rhs) &&
           (op == dynamic_cast<const Unary &>(rhs).op) &&
           (*operand == *dynamic_cast<const Unary &>(rhs).operand);
}

bool Binary::operator==(const Expr &rhs) const
{
    return typeid(*this) == typeid(rhs) &&
           (*left == *dynamic_cast<const Binary &>(rhs).left) &&
           (op == dynamic_cast<const Binary &>(rhs).op) &&
           (*right == *dynamic_cast<const Binary &>(rhs).right);
}

bool BinaryAssign::operator==(const Expr &rhs) const
{
    return typeid(*this) == typeid(rhs) &&
           (*id == *dynamic_cast<const BinaryAssign &>(rhs).id) &&
           (*value == *dynamic_cast<const BinaryAssign &>(rhs).value);
}

bool BinaryEval::operator==(const Expr &rhs) const
{
    return typeid(*this) == typeid(rhs) &&
           (*expr == *dynamic_cast<const BinaryEval &>(rhs).expr) &&
           (x == dynamic_cast<const BinaryEval &>(rhs).x);
}

bool FnCall::operator==(const Expr &rhs) const
{
    return typeid(*this) == typeid(rhs) &&
           (fn == dynamic_cast<const FnCall &>(rhs).fn) &&
           (*arg == *dynamic_cast<const FnCall &>(rhs).arg);
}

// ===== Accept =====

IMPL_ACCEPT(Ident)
IMPL_ACCEPT(Monomial)
IMPL_ACCEPT(Unary)
IMPL_ACCEPT(Binary)
IMPL_ACCEPT(BinaryAssign)
IMPL_ACCEPT(BinaryEval)
IMPL_ACCEPT(FnCall)

// ===== Output =====

ostream &operator<<(ostream &out, const Expr &value)
{
    return value.print(out);
}

ostream &Ident::print(ostream &out) const
{
    out << "Ident { " << value << " }";
    return out;
}

ostream &Monomial::print(ostream &out) const
{
    out << "Monomial { " << coefficient << "x^" << power << " }";
    return out;
}

ostream &Unary::print(ostream &out) const
{
    out << "Unary { (";
    switch (op)
    {
    case Unary::DERIVE:
        out << "Derive";
        break;
    case Unary::MINUS:
        out << "-";
        break;
    }
    out << ") " << *operand << " }";
    return out;
}

ostream &Binary::print(ostream &out) const
{
    out << "Binary { " << *left << " (";
    switch (op)
    {
    case Binary::ADD:
        out << '+';
        break;
    case Binary::SUBTRACT:
        out << '-';
        break;
    case Binary::MULTIPLY:
        out << '*';
        break;
    case Binary::EQUAL:
        out << "==";
        break;
    }
    out << ") " << *right << " }";
    return out;
}

ostream &BinaryEval::print(ostream &out) const
{
    out << "BinaryEval { "
        << *expr << " (!) "
        << x << " }";
    return out;
}

ostream &BinaryAssign::print(ostream &out) const
{
    out << "BinaryAssign { "
        << *id << " (=) "
        << *value << " }";
    return out;
}

ostream &FnCall::print(ostream &out) const
{
    out << "FnCall { "
        << fn << " "
        << *arg << " }";
    return out;
}
