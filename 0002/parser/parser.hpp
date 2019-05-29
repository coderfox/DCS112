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
    unsigned int term_integer();
    std::shared_ptr<ast::Expr> term_ident();
    std::shared_ptr<ast::Expr> term_monomial();
    std::shared_ptr<ast::Expr> term_polynomial_single();
    std::shared_ptr<ast::Expr> term_polynomial();
    std::shared_ptr<ast::Expr> expr_terminal();
    std::shared_ptr<ast::Expr> expr_negative();
    std::shared_ptr<ast::Expr> expr_multiply();
    std::shared_ptr<ast::Expr> expr_sum_or_subtract();
    std::shared_ptr<ast::Expr> expr_derive();
    std::shared_ptr<ast::Expr> expr_eval();
    std::shared_ptr<ast::Expr> expr_equal();
    std::shared_ptr<ast::Expr> expr();
    void ensure_finished();
};
