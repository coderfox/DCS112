#include <map>
#include <list>
#include <sstream>
#include "polynomial.hpp"
#include "catch.hpp"

using namespace std;

TEST_CASE("class Polynomial > constructor", "[polynomial]")
{
    auto poly = Polynomial(
        list<pair<unsigned int, int>>{
            make_pair(2, 1),
            make_pair(1, 2),
            make_pair(0, 1)});
    auto poly_list = Polynomial{1, 2, 3};
    SECTION("list-pair constructor")
    {
        REQUIRE(poly[2] == 1);
        REQUIRE(poly[1] == 2);
        REQUIRE(poly[0] == 1);
    }
    SECTION("list constructor")
    {
        REQUIRE(poly_list[3] == 0);
        REQUIRE(poly_list[2] == 1);
        REQUIRE(poly_list[1] == 2);
        REQUIRE(poly_list[0] == 3);
    }
}

TEST_CASE("class Polynomial > accessor", "[polynomial]")
{
    auto poly_empty = Polynomial();
    SECTION("get value from polynomial")
    {
        REQUIRE(poly_empty[3] == 0);
        REQUIRE(poly_empty.get(3) == 0);
    }
    SECTION("assign value to polynomial")
    {
        poly_empty[5] = 1;
        REQUIRE(poly_empty[5] == 1);
        REQUIRE(poly_empty.get(5) == 1);
    }
}

TEST_CASE("class Polynomial > equal", "[polynomial]")
{
    auto poly1 = Polynomial{1, 2, 3};
    auto poly2 = Polynomial{1, 2, 3};
    auto poly3 = Polynomial{2, 3};
    auto poly4 = Polynomial{3, 1, 2, 3};
    REQUIRE(poly1 == poly2);
    REQUIRE_FALSE(poly1 == poly3);
    REQUIRE_FALSE(poly1 == poly4);
}
TEST_CASE("class Polynomial > negative", "[polynomial]")
{
    auto poly = Polynomial{5, 0, 6, 7, 8};
    REQUIRE(-poly == Polynomial{-5, 0, -6, -7, -8});
}
TEST_CASE("class Polynomial > add", "[polynomial]")
{
    auto poly_lhs = Polynomial{1, 2, 3, 4};
    auto poly_rhs = Polynomial{5, 0, 6, 7, 8};
    REQUIRE(poly_lhs + poly_rhs == Polynomial{5, 1, 8, 10, 12});
}
TEST_CASE("class Polynomial > subtract", "[polynomial]")
{
    auto poly_lhs = Polynomial{1, 2, 3, 4};
    auto poly_rhs = Polynomial{5, 0, 6, 1, 4};
    REQUIRE(poly_lhs - poly_rhs == Polynomial{-5, 1, -4, 2, 0});
}
TEST_CASE("class Polynomial > expr_multiply", "[polynomial]")
{
    auto poly_lhs = Polynomial{1, 2};
    auto poly_rhs = Polynomial{3, 4};
    REQUIRE(poly_lhs * poly_rhs == Polynomial{3, 10, 8});
}
TEST_CASE("class Polynomial > derive", "[polynomial]")
{
    auto poly = Polynomial{1, 2, 3, 4};
    REQUIRE(poly.derive() == Polynomial{3, 4, 3});
}
TEST_CASE("class Polynomial > eval", "[polynomial]")
{
    SECTION("normal")
    {
        auto poly = Polynomial{1, 2, 3, 4};
        REQUIRE(poly.eval(5) == 194);
    }
    SECTION("negative")
    {
        auto poly = Polynomial{1, 2, 3, 4};
        REQUIRE(poly.eval(-5) == -86);
    }
    SECTION("empty")
    {
        Polynomial poly;
        REQUIRE(poly.eval(5) == 0);
    }
}

TEST_CASE("class Polynomial > io", "[polynomial]")
{
    SECTION("normal polynomial")
    {
        auto poly = Polynomial{1, 2, 3};
        stringstream ss;
        ss << poly;
        REQUIRE(ss.str() == "x^2+2x+3");
    }
    SECTION("empty polynomial")
    {
        auto poly = Polynomial();
        stringstream ss;
        ss << poly;
        REQUIRE(ss.str() == "0");
    }
    SECTION("constant polynomial")
    {
        auto poly = Polynomial{1};
        stringstream ss;
        ss << poly;
        REQUIRE(ss.str() == "1");
    }
    SECTION("(x) polynomial")
    {
        auto poly = Polynomial{1, 0};
        stringstream ss;
        ss << poly;
        REQUIRE(ss.str() == "x");
    }
    SECTION("(x) polynomial with garbage")
    {
        auto poly = Polynomial{1, 0};
        poly[3];
        stringstream ss;
        ss << poly;
        REQUIRE(ss.str() == "x");
    }
    SECTION("polynomial with negative coefficients")
    {
        auto poly = Polynomial{-3, -1, -2};
        stringstream ss;
        ss << poly;
        REQUIRE(ss.str() == "-3x^2-x-2");
    }
}
