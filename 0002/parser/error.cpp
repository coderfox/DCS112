#include <sstream>
#include <exception>
#include "error.hpp"

using namespace std;

Error::Error(Span total_span,
             Span error_span,
             std::vector<std::string> expected) : expected(expected)
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
    out << error.total << endl
        << string(error.begin, ' ')
        << string(error.length, '^') << endl
        << "Expected: ";
    copy(error.expected.cbegin(), error.expected.cend(), ostream_iterator<string>(out, ", "));
    return out;
}
