#pragma once

#include <string>
#include <vector>
#include <exception>
#include "span.hpp"

struct Error final
{
    std::string total;
    unsigned int begin;
    unsigned int length;
    std::string message;

    Error(Span total_span, Span error_span, std::string message);

    std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &out, const Error &error);
};
