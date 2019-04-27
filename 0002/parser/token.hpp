#pragma once

#include <string>
#include "span.hpp"

struct Token : public HasSpan
{
    typedef enum
    {
        // Valued
        IDENTIFIER,
        INTEGER,
        VARIABLE,

        // Operators
        OP_ADD,
        OP_SUBTRACT,
        OP_MULTIPLY,
        OP_DERIVE,
        OP_LPAREN,
        OP_RPAREN,
        OP_POW,
        OP_EQ,
        OP_ASSIGN,
        OP_COMMA,
        OP_BANG,

        // Void
        VOID,
    } Type;

    Type type;

    Token(Type type, Span span);
    Token(Type type,
          std::string::const_iterator begin,
          std::string::const_iterator end);
    bool operator==(const Token &rhs) const;
    bool is(Type type) const;
    bool operator==(Type type) const;
    bool operator!=(Type type) const;
    std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &out, const Token &token);
};
