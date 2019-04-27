#include "ast.hpp"

using namespace std;
using namespace ast;

#define IMPL_ACCEPT(T)                     \
    void T::accept(Visitor &visitor) const \
    {                                      \
        visitor.visit(*this);              \
    }

// ===== Constructor =====

Ident::Ident(string value) : value(value)
{
}

Monomial::Monomial(unsigned int coefficient,
                   unsigned int power) : coefficient(coefficient), power(power)
{
}

Unary::Unary(Op op, shared_ptr<Expr> operand) : op(op), operand(operand)
{
}

Binary::Binary(shared_ptr<Expr> left,
               Op op,
               shared_ptr<Expr> right) : left(left), op(op), right(right)
{
}

BinaryAssign::BinaryAssign(
    shared_ptr<Expr> id,
    shared_ptr<Expr> value) : id(id), value(value)
{
}

BinaryEval::BinaryEval(
    shared_ptr<Expr> expr, int x) : x(x), expr(expr)
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

// ===== Accept =====

IMPL_ACCEPT(Ident)
IMPL_ACCEPT(Monomial)
IMPL_ACCEPT(Unary)
IMPL_ACCEPT(Binary)
IMPL_ACCEPT(BinaryAssign)
IMPL_ACCEPT(BinaryEval)

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
