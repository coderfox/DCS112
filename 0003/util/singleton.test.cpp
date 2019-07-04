#include "catch.hpp"
#include "singleton.hpp"

using namespace std;

TEST_CASE("singleton", "[singleton]")
{
    SECTION("int")
    {
        auto ptr = make_unique<int>(5);

        REQUIRE_THROWS_AS(Singleton<int>(), SingletonNotInitialized);

        Singleton<int>::initialize(move(ptr));
        REQUIRE(ptr == nullptr);
        REQUIRE_NOTHROW(Singleton<int>());
        REQUIRE(*Singleton<int>() == 5);
    }
}
