#include <sstream>
#include <algorithm>
#include "evaluator.hpp"
#include "parser/lexer.hpp"
#include "parser/parser.hpp"

Evaluator::Evaluator()
{
}

Polynomial Evaluator::eval(string code)
{
    _current_str = code;
    auto lexer = Lexer(_current_str);
    lexer.parse();
    // for (auto iter = lexer.cbegin(); iter != lexer.cend(); iter++)
    // {
    //     cout << *iter;
    // }
    auto parser = Parser(lexer.cbegin(), lexer.cend());
    auto expr = parser.expr();
    parser.ensure_finished();
    // cout << *expr << endl;
    expr->accept(*this);
    return _state.back();
}

vector<pair<string, Polynomial>> Evaluator::get_variables() const
{
    vector<pair<string, Polynomial>> vars;
    copy(_context.begin(), _context.end(), back_inserter(vars));
    return vars;
}

vector<Polynomial> Evaluator::get_history() const
{
    auto his = _state;
    reverse(his.begin(), his.end());
    return his;
}

void Evaluator::visit(const ast::Ident &value)
{
    try
    {
        _state.push_back(_context.at(value.value));
    }
    catch (out_of_range &)
    {
        throw Error(
            Span(_current_str.begin(), _current_str.end()),
            value.get_span(),
            "Undefined variable " + value.value);
    }
}

void Evaluator::visit(const ast::Monomial &value)
{
    _state.push_back(Polynomial({make_pair(value.power, value.coefficient)}));
}

void Evaluator::visit(const ast::Unary &value)
{
    value.operand->accept(*this);
    auto poly = _state.back();
    _state.pop_back();
    if (value.op == ast::Unary::DERIVE)
    {
        _state.push_back(poly.derive());
    }
    else if (value.op == ast::Unary::MINUS)
    {
        _state.push_back(-poly);
    }
}

void Evaluator::visit(const ast::Binary &value)
{
    value.left->accept(*this);
    auto left = _state.back();
    _state.pop_back();
    value.right->accept(*this);
    auto right = _state.back();
    _state.pop_back();

    switch (value.op)
    {
    case ast::Binary::ADD:
        _state.push_back(left + right);
        break;
    case ast::Binary::EQUAL:
        _state.push_back(left == right ? Polynomial{1} : Polynomial{0});
        break;
    case ast::Binary::MULTIPLY:
        _state.push_back(left * right);
        break;
    case ast::Binary::SUBTRACT:
        _state.push_back(left - right);
        break;
    }
}

void Evaluator::visit(const ast::BinaryAssign &value)
{
    string id;
    try
    {
        auto left = dynamic_cast<const ast::Ident &>(*value.id);
        id = left.value;
    }
    catch (bad_cast &)
    {
        stringstream ss;
        ss << "Invalid left operand ("
           << *value.id
           << ") of BinaryAssign";
        throw Error(
            Span(_current_str.begin(), _current_str.end()),
            value.get_span(), ss.str());
    }
    value.value->accept(*this);
    auto right = _state.back();
    // do not pop_back value to pass it as return value
    _context[id] = right;
}

void Evaluator::visit(const ast::BinaryEval &value)
{
    value.expr->accept(*this);
    auto poly = _state.back();
    _state.pop_back();
    _state.push_back(Polynomial{poly.eval(value.x)});
}
