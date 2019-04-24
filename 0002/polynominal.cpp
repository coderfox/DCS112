#include <map>
#include <list>
#include "polynominal.hpp"
#include "catch.hpp"

using namespace std;

Polynominal::Polynominal()
{
}
Polynominal::Polynominal(list<pair<unsigned int, int>> list)
{
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        _coefficients[iter->first] = iter->second;
    }
}
int &Polynominal::operator[](unsigned int rhs)
{
    return _coefficients[rhs];
}

// =====UNIT TESTS=====

TEST_CASE("class Polynominal", "[polynominal]")
{
    auto poly_empty = Polynominal();
    auto poly_sample_a = Polynominal(
        list<pair<unsigned int, int>>{
            make_pair(2, 1),
            make_pair(1, 2),
            make_pair(0, 1)});
    SECTION("get value from polynominal")
    {
        REQUIRE(poly_sample_a[3] == 0);
        REQUIRE(poly_sample_a[2] == 1);
        REQUIRE(poly_sample_a[1] == 2);
        REQUIRE(poly_sample_a[0] == 1);
    }
    SECTION("assign value to polynominal")
    {
        poly_empty[5] = 1;
        REQUIRE(poly_empty[5] == 1);
    }
}