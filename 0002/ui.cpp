#include <iostream>
#include <iomanip>
#include <sstream>
#include "ui.hpp"
#include "color.hpp"
#include "getline.hpp"

using namespace std;

void print_help_item(const char *name, const char *desc)
{
    cout << color::FG_YELLOW << setw(12) << name
         << color::OP_RESET << "    " << desc << endl;
}

void print_help_item(const char *name, const char *desc, const char *example)
{
    cout << color::FG_YELLOW << left << setw(24) << name
         << color::OP_RESET << "  " << left << setw(24) << desc
         << "  " << color::FG_GREEN << example
         << color::OP_RESET << endl;
}

void handle_help(bool extra)
{
    cout << color::BG_CYAN << color::FG_MAGENTA << color::OP_BOLD
         << "Polynomial Calculator v1.0 by xfoxfu" << color::OP_RESET << endl
         << color::BG_GREEN << "Help:" << color::OP_RESET << endl;

    print_help_item("help", "get help");
    print_help_item("help-extra", "get detailed help");
    print_help_item("add", "calculate sum of 2 polynomials");
    print_help_item("mul", "calculate product of 2 polynomials");
    print_help_item("minus", "calculate difference of 2 polynomials");
    print_help_item("eval", "calculate value of a polynomial");
    // print_help_item("his", "get calculation history");
    print_help_item("memory", "get variable memory");
    print_help_item("equal", "determine if 2 polynomials equal");
    print_help_item("derive", "derive a polynomial");
    print_help_item("exit", "exit calculator");
    print_help_item("(expr)", "simplify the given expression");

    if (extra)
    {
        cout << color::BG_GREEN << "Grammars:" << color::OP_RESET << endl;
        // Integer    = @{ NUMBER+ }
        // Ident      = @{ ALPHABETIC+ }
        print_help_item("variable", "", "p q p5");
        // Monomial   = { Integer | (Integer? ~ "x" ~ ("^" ~ Integer)? ) }
        print_help_item("monomial", "COEFFICIENT x ^ POWER", "2x^2 x^3 5x 27");
        // PolySingle = { "(" ~ Integer ~ "," ~ Integer ~ ")" }
        // Polynomial = { ( PolySingle )+ }
        print_help_item("polynomial", "(COEFFICIENT, POWER)", "(2,5)(-7,2)");
        // Term       = { ("(" ~ Expr ~ ")") | Polynomial | Monomial | Ident }
        // Negative      = { ("-" ~ Term) | Term }
        print_help_item("unary expr negative", "- expr", "-5x^2 -(8x+9)");
        // Derive      = { (SubOrSubtract ~ "'") | SubOrSubtract }
        print_help_item("unary expr derive", "expr'", "2x+9'");
        // ExprEval  = { Derive ~ ("!" ~ Integer)? }
        print_help_item("unary expr eval", "expr!NUMBER", "x^2+2x!5 p!25");
        // SumOrSubtract      = { Multiply ~ (("+"|"-") ~ Multiply)* }
        print_help_item("binary expr add", "expr + expr", "5x+9");
        print_help_item("binary expr minus", "expr - expr", "4x^2-7x+8");
        // Multiply      = { Negative ~ ("*" ~ Negative)* }
        print_help_item("binary expr multiply", "expr * expr", "42x*(68x+15)");
        // Expr0      = { ExprEval ~ ("==" ~ ExprEval)* }
        print_help_item("binary expr equality", "expr == expr", "5x+9==24x+8");
        // Expr       = { (Expr0 ~ "=")* ~ Expr0 }
        print_help_item("binary expr assign", "expr = expr", "p=x^2+2x+1");

        cout << color::BG_GREEN << "Operator Precedence: (High to Low)" << color::OP_RESET << endl;
        print_help_item("- (unary)", "left-associative");
        print_help_item("*", "left-associative");
        print_help_item("+ -", "left-associative");
        print_help_item("'", "cannot appear twice without brackets");
        print_help_item("!", "cannot appear twice without brackets");
        print_help_item("==", "right-associative");
        print_help_item("=", "right-associative");
    }
}

void print_result(string res)
{
    cout << color::FG_GREEN << "Result = " << color::OP_RESET
         << res << endl;
}
void eval_print(Evaluator &host, string expr)
{
    auto poly = host.eval(expr);
    print_result(poly.to_string());
}

void handle_add(Evaluator &host)
{
    auto lhs = getline("lhs> ").second;
    host.eval_discard(lhs);
    auto rhs = getline("rhs> ").second;
    host.eval_discard(rhs);

    stringstream ss;
    ss << "( " << lhs << " )+( " << rhs << " )";
    eval_print(host, ss.str());
}

void handle_multiply(Evaluator &host)
{
    auto lhs = getline("lhs> ").second;
    host.eval_discard(lhs);
    auto rhs = getline("rhs> ").second;
    host.eval_discard(rhs);

    stringstream ss;
    ss << "( " << lhs << " )*( " << rhs << " )";
    eval_print(host, ss.str());
}

void handle_minus(Evaluator &host)
{
    auto lhs = getline("lhs> ").second;
    host.eval_discard(lhs);
    auto rhs = getline("rhs> ").second;
    host.eval_discard(rhs);

    stringstream ss;
    ss << "( " << lhs << " )-( " << rhs << " )";
    eval_print(host, ss.str());
}

void handle_evaluate(Evaluator &host)
{
    auto lhs = getline("polynomial> ").second;
    host.eval_discard(lhs);
    auto rhs = getline("x= ").second;
    auto rhs_parsed = host.eval_discard(rhs);

    stringstream ss;
    ss << "( " << lhs << " )!( " << rhs << " )";
    eval_print(host, ss.str());
}

void handle_equal(Evaluator &host)
{
    auto lhs = getline("lhs> ").second;
    host.eval_discard(lhs);
    auto rhs = getline("rhs> ").second;
    host.eval_discard(rhs);

    if (lhs == rhs)
        print_result("True");
    else
        print_result("False");
}

void handle_derive(Evaluator &host)
{
    auto lhs = getline("polynomial> ").second;
    host.eval_discard(lhs);

    stringstream ss;
    ss << "( " << lhs << " )'";
    eval_print(host, ss.str());
}

void handle_plain(Evaluator &host, string input)
{
    eval_print(host, input);
}

void handle_memory(Evaluator &host)
{
    cout << "| "
         << setw(4) << "name"
         << " | "
         << setw(48) << left << "value"
         << " |" << endl;
    cout << "| "
         << string(4, '-') << " | "
         << string(48, '-') << " |" << endl;
    for (auto it : host.get_variables())
    {
        cout << "| "
             << setw(4) << it.first << " | "
             << setw(48) << left << it.second.to_string() << " |" << endl;
    }
}

void handle_history(Evaluator &host)
{
    for (auto it : host.get_history())
    {
        cout << "| "
             << setw(48) << left << it.to_string() << " |" << endl;
    }
}

void handle_exit()
{
    cout << color::BG_MAGENTA << "Goodbye~" << color::OP_RESET << endl;
}
