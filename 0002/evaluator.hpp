#include <vector>
#include <map>
#include "polynomial.hpp"
#include "parser/ast.hpp"
#include "parser/visitor.hpp"

using namespace std;

class Evaluator final : public Visitor
{
  private:
    std::map<std::string, Polynomial> _context;
    std::vector<Polynomial> _state;

  public:
    Evaluator();

    Polynomial eval(std::string expr);
    std::vector<std::pair<std::string, Polynomial>> get_variables() const;
    std::vector<Polynomial> get_history() const;

    void visit(const ast::Ident &value);
    void visit(const ast::Monomial &value);
    void visit(const ast::Unary &value);
    void visit(const ast::Binary &value);
    void visit(const ast::BinaryAssign &value);
    void visit(const ast::BinaryEval &value);
};
