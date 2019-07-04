#include "catch.hpp"
#include "repository.hpp"
#include <sstream>

using namespace std;

struct Number : public IIdentifiable, public IStorable
{
    size_t _id;
    int value;

    Number() : Number(0)
    {
    }
    Number(int value) : _id(numeric_limits<size_t>::max()), value(value)
    {
    }

    bool operator==(int rhs) const
    {
        return value == rhs;
    }

    void write(std::ostream &output) const
    {
        ::write(output, _id);
        ::write(output, value);
    }
    void read(std::istream &input)
    {
        ::read(input, _id);
        ::read(input, value);
    }

    size_t id() const
    {
        return _id;
    }
    void id(size_t value)
    {
        _id = value;
    }
};

TEST_CASE("repository", "[entity][repository]")
{
    SECTION("serialize")
    {
        Repository<Number> numbers;
        numbers.insert(1);
        REQUIRE(numbers.find_by_id(0) == 1);
        numbers.insert(2);
        REQUIRE(numbers.find_by_id(1) == 2);
        numbers.insert(3);
        REQUIRE(numbers.find_by_id(2) == 3);

        stringstream ss;
        numbers.write(ss);

        Repository<Number> numbers_read;
        numbers_read.read(ss);

        REQUIRE(numbers.find_by_id(0) == 1);
        REQUIRE(numbers.find_by_id(1) == 2);
        REQUIRE(numbers.find_by_id(2) == 3);
    }
    /* SECTION("save without id")
    {
        Repository<Number> numbers;
        REQUIRE_THROWS_AS(numbers.save(1), InvalidIdentifier);
    } */
}
