#include "catch.hpp"
#include "utils.hpp"
#include <sstream>

using namespace std;

TEST_CASE("util functions", "[utils]")
{
    SECTION("char")
    {
        stringstream ss;
        char val;

        write(ss, 'c');
        REQUIRE(ss.str() == "c");

        read(ss, val);
        REQUIRE(val == 'c');
    }
    SECTION("positive int")
    {
        stringstream ss;
        int val;

        write(ss, 0x32445533);
        REQUIRE(ss.str() == "\x33\x55\x44\x32");

        read(ss, val);
        REQUIRE(val == 0x32445533);
    }
    SECTION("negative int")
    {
        stringstream ss;
        int val;

        write(ss, -0x32445533);
        REQUIRE(ss.str() == "\xCD\xAA\xBB\xCD");

        read(ss, val);
        REQUIRE(val == -0x32445533);
    }
    SECTION("string")
    {
        stringstream ss;
        string str;

        write(ss, "Hello world!");
        REQUIRE(ss.str().length() == 13);
        // use appended '\0' to check binary data,
        // as string constructor will truncate '\0' by default,
        REQUIRE(ss.str() == string("Hello world!") + '\0');

        read(ss, str);
        REQUIRE(str == "Hello world!");
    }
}
