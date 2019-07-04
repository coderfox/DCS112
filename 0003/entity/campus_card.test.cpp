#include "catch.hpp"
#include "campus_card.hpp"
#include <sstream>

using namespace std;

TEST_CASE("campus_card", "[entity][card][campus_card]")
{
    SECTION("initialize")
    {
        CampusCard card;
        REQUIRE(card.id() == numeric_limits<size_t>::max());
        REQUIRE(card.balance() == 0);
    }
    SECTION("consume")
    {
        CampusCard card;
        card.balance(15);

        card.consume(5);
        REQUIRE(card.balance() == 10);
        REQUIRE_THROWS_AS(card.consume(11), InsufficientBalance);
    }
    SECTION("credit card transfer")
    {
        CampusCard campus;
        campus.balance(15);
        CreditCard credit;
        credit.balance(10);
        credit.credit(10);

        campus.transfer_from(credit, 20);
        REQUIRE_THROWS_AS(campus.transfer_from(credit, 20), InsufficientBalance);
    }
    SECTION("transaction record")
    {
        CampusCard campus;
        campus.id(10);
        campus.balance(15);
        CreditCard credit;
        credit.id(1);
        credit.balance(10);
        credit.credit(10);

        campus.consume(5);
        auto record = campus.transaction().find_by_id(0);
        REQUIRE(record.difference() == -5l);
        REQUIRE(record.note() == "consume");

        campus.transfer_from(credit, 20);
        record = credit.transaction().find_by_id(0);
        REQUIRE(record.difference() == -20);
        REQUIRE(record.note() == "transfer to campus card <10>");
        record = campus.transaction().find_by_id(1);
        REQUIRE(record.difference() == 20);
        REQUIRE(record.note() == "transfer from credit card <1>");
    }
    SECTION("serialize")
    {
        CampusCard card;
        card.balance(10);
        card.card_no(114);
        card.stu_id(114514);
        card.holder_name("TianSuoHaoEr");
        card.school("Tokyo University");
        card.consume(5);

        stringstream ss;
        card.write(ss);

        CampusCard read;
        read.read(ss);
        REQUIRE(card.balance() == 5);
        REQUIRE(card.card_no() == 114);
        REQUIRE(card.stu_id() == 114514);
        REQUIRE(card.holder_name() == "TianSuoHaoEr");
        REQUIRE(card.school() == "Tokyo University");
        auto record = card.transaction().find_by_id(0);
        REQUIRE(record.difference() == -5l);
        REQUIRE(record.note() == "consume");
    }
}
