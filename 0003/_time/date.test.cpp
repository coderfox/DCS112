#include "catch.hpp"
#include "date.hpp"
#include <sstream>

using namespace std;

TEST_CASE("Date", "[utils][date]")
{
    SECTION("serialize")
    {
        auto date = Date(1999, 9, 13);
        stringstream ss;

        date.write(ss);
        Date obj;
        obj.read(ss);

        REQUIRE(date.year() == 1999);
        REQUIRE(date.month() == 9);
        REQUIRE(date.day() == 13);
    }
    SECTION("IO")
    {
        Date date;
        stringstream ss("1999/09/13");

        ss >> date;
        REQUIRE(date == Date(1999, 9, 13));

        stringstream out;
        out << date;
        REQUIRE(out.str() == "1999/09/13");
    }
    SECTION("string constructor")
    {
        Date date("1999 09 13");
        REQUIRE(date == Date(1999, 9, 13));
    }
}
