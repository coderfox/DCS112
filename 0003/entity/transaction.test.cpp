#include "catch.hpp"
#include "transaction.hpp"
#include <sstream>

using namespace std;

TEST_CASE("class Transaction", "[entity][transaction]")
{
    SECTION("serialize")
    {
        stringstream ss;
        auto obj_write = Transaction(-5, "some note");
        obj_write.id(42);

        obj_write.write(ss);
        Transaction obj_read;
        obj_read.read(ss);

        REQUIRE(obj_read.id() == 42);
        REQUIRE(obj_read.difference() == -5);
        REQUIRE(obj_read.time() == obj_write.time());
        REQUIRE(obj_read.note() == "some note");
    }
    SECTION("default id")
    {
        auto obj = Transaction();
        REQUIRE(obj.id() == numeric_limits<size_t>::max());
    }
    SECTION("set id")
    {
        auto obj = Transaction();
        size_t incr = 15;
        obj.set_id(incr);

        REQUIRE(obj.id() == 15);
        REQUIRE(incr == 16);
    }
}