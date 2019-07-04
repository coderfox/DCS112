#include "catch.hpp"
#include "datetime.hpp"
#include <sstream>

using namespace std;

TEST_CASE("DateTime", "[utils][date]")
{
    SECTION("serialize")
    {
        auto date = DateTime(1999, 9, 3, 15, 2, 8);
        stringstream ss;

        date.write(ss);
        DateTime obj;
        obj.read(ss);

        REQUIRE(date.year() == 1999);
        REQUIRE(date.month() == 9);
        REQUIRE(date.day() == 3);
        REQUIRE(date.hour() == 15);
        REQUIRE(date.minute() == 2);
        REQUIRE(date.second() == 8);
    }
    SECTION("IO")
    {
        DateTime date;
        stringstream ss("1999/09/03 15:02:18");

        ss >> date;
        REQUIRE(date == DateTime(1999, 9, 3, 15, 2, 18));

        stringstream out;
        out << date;
        REQUIRE(out.str() == "1999/09/03 15:02:08");
    }
    SECTION("string constructor")
    {
        DateTime date("1999 09 03 15 2 18");
        REQUIRE(date == DateTime(1999, 9, 3, 15, 2, 18));
    }
}
