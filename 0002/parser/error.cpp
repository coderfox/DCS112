#include <sstream>
#include <exception>
#include <iterator>
#include <string>
#include "error.hpp"

#define COLOR_OUTPUT

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
#ifdef COLOR_OUTPUT
    out << "\033[33m" << hint << "\033[0m"
        << error.total.substr(0, error.begin)
        << "\033[41m" << error.total.substr(error.begin, error.begin + error.length) << "\033[0m"
        << error.total.substr(error.begin + error.length) << endl
        << "\033[31m"
        << "Error: "
        << "\033[0m" << error.message;
#else
    out << hint << error.total << endl
        << string(hint.length() + error.begin, ' ')
        << string(error.length, '^') << endl
        << error.message;
#endif
    return out;
}
