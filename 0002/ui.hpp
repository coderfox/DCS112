#include <string>
#include "evaluator.hpp"

void handle_help(bool extra = false);
void handle_add(Evaluator &host);
void handle_multiply(Evaluator &host);
void handle_minus(Evaluator &host);
void handle_evaluate(Evaluator &host);
void handle_equal(Evaluator &host);
void handle_derive(Evaluator &host);
void handle_plain(Evaluator &host, std::string input);
void handle_memory(Evaluator &host);
void handle_history(Evaluator &host);
void handle_exit();
