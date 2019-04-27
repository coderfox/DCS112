#include "evaluator.hpp"
#include "catch.hpp"

TEST_CASE("class Evaluator", "[evaluator]")
{
    Evaluator eval;

    REQUIRE(eval.eval("x^3-5x^2+3x+8") == Polynomial{1, -5, 3, 8});
    REQUIRE(eval.eval("(x^3-5x^2)+(3x^2+8)") == Polynomial{1, -2, 0, 8});
    REQUIRE(eval.eval("x^2+2x+1'!5") == Polynomial{12});
    REQUIRE(eval.eval("p=q=2x^2") == Polynomial{2, 0, 0});
    REQUIRE(eval.eval("p==q") == Polynomial{1});
    REQUIRE(eval.eval("p=x") == Polynomial{1, 0});
}
