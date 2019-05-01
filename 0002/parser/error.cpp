#include <iostream>
#include <sstream>
#include <exception>
#include <iterator>
#include <string>
#include <cassert>
#include "error.hpp"
#include "color.hpp"

using namespace std;

Error::Error(Span total_span,
             Span error_span,
             string message) : message(message)
{
    total = string(total_span.begin, total_span.end);
    begin = distance(total_span.begin, error_span.begin);
    length = distance(error_span.begin, error_span.end);
    if (length <= 0)
        length = 1;
}

string Error::to_string() const
{
    stringstream ss;
    ss << *this;
    return ss.str();
}

ostream &operator<<(ostream &out, const Error &error)
{
    string hint = "INPUT:" + to_string(error.begin) + ": ";
    out
        // output hint line
        << color::FG_YELLOW << hint << color::OP_RESET
        // output string before error
        << error.total.substr(0, error.begin)
        // output error section
        << color::BG_RED << color::OP_BOLD << error.total.substr(error.begin, error.length) << color::OP_RESET
        // output rest string
        << error.total.substr(error.begin + error.length) << endl
        // output hint line
        << string(hint.length() + error.begin, ' ')
        << color::FG_YELLOW << string(error.length, '^') << color::OP_RESET << endl
        // output error message
        << color::FG_RED << "Error: " << color::OP_RESET
        << color::OP_BOLD << error.message << color::OP_RESET;
    return out;
}
