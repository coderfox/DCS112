#include <string>
#include <vector>
#include <functional>
#include <utility>
#include "token.hpp"

class Lexer
{
  private:
    std::string::const_iterator _begin;
    std::string::const_iterator _end;
    std::string::const_iterator _current;
    std::vector<Token> _tokens;

    // ===== Common Functions =====
    char match(std::function<bool(char)> cur_cond);
    std::pair<char, char> match(std::function<bool(char, char)> cond);
    bool match(char cur);
    bool match(char cur, char next);
    char progress();

  public:
    // ===== Constructors =====
    explicit Lexer(const std::string &input);
    Lexer(std::string::const_iterator begin, std::string::const_iterator end);

    // ===== Accessors =====
    std::vector<Token>::const_iterator cbegin() const;
    std::vector<Token>::const_iterator cend() const;
    std::string::const_iterator cstr_begin() const;
    std::string::const_iterator cstr_end() const;
    std::string::const_iterator cstr_current() const;
    bool finished() const;
    size_t token_count() const;

    // ===== Parsers =====
    Token integer();
    Token ident();
    Token add();
    Token subtract();
    Token multiply();
    Token derive();
    Token lparen();
    Token rparen();
    Token pow();
    Token eq();
    Token assign();
    Token comma();
    Token bang();
    void whitespace();

    //===== Parse Function =====
    void parse();
    Token advance();
};
