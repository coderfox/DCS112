#include <string>
#include <vector>
#include <functional>
#include <utility>
#include "token.hpp"
#include "ast.hpp"
#include "error.hpp"

class Parser
{
  private:
    std::vector<Token>::const_iterator _begin;
    std::vector<Token>::const_iterator _end;
    std::vector<Token>::const_iterator _current;

    // ===== Common Functions =====
    Token match(Token::Type cur_ty);
    std::pair<Token, Token> match(Token::Type cur_ty, Token::Type next_ty);
    bool peak(Token::Type cur_ty);
    bool peak(Token::Type cur_ty, Token::Type next_ty);
    bool peak(Token::Type cur_ty, Token::Type next_ty, Token::Type next2_ty);
    Error make_error(std::string expected, bool to_end = false);

  public:
    // ===== Constructors =====
    explicit Parser(const std::vector<Token> &input);
    Parser(std::vector<Token>::const_iterator begin, std::vector<Token>::const_iterator end);

    // ===== Utilities =====
    void reset();

    // ===== Parsers =====
    // Integer    = @{ NUMBER+ }
    unsigned int term_integer();
    // Ident      = @{ ALPHABETIC+ }
    std::shared_ptr<ast::Expr> term_ident();
    // Monomial   = { Integer | (Integer? ~ "x" ~ ("^" ~ Integer)? ) }
    std::shared_ptr<ast::Expr> term_monomial();
    // PolySingle = { "(" ~ Integer ~ "," ~ Integer ~ ")" }
    std::shared_ptr<ast::Expr> term_polynomial_single();
    // Polynomial = { ( PolySingle )+ }
    std::shared_ptr<ast::Expr> term_polynomial();
    // Term       = { ("(" ~ Expr ~ ")") | Polynomial | Monomial | Ident }
    std::shared_ptr<ast::Expr> expr_terminal();
    // Negative      = { ("-" ~ Term) | Term }
    std::shared_ptr<ast::Expr> expr_negative();
    // Multiply      = { Negative ~ ("*" ~ Negative)* }
    std::shared_ptr<ast::Expr> expr_multiply();
    // SumOrSubtract      = { Multiply ~ (("+"|"-") ~ Multiply)* }
    std::shared_ptr<ast::Expr> expr_sum_or_subtract();
    // Derive      = { (SubOrSubtract ~ "'") | SubOrSubtract }
    std::shared_ptr<ast::Expr> expr_derive();
    // ExprEval  = { Derive ~ ("!" ~ Integer)? }
    std::shared_ptr<ast::Expr> expr_eval();
    // Expr0      = { ExprEval ~ ("==" ~ ExprEval)* }
    std::shared_ptr<ast::Expr> expr_equal();
    // Expr       = { (Expr0 ~ "=")* ~ Expr0 }
    std::shared_ptr<ast::Expr> expr();
    void ensure_finished();
};
