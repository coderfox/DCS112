#include "catch.hpp"
#include "credit_card.hpp"
#include <sstream>

using namespace std;

TEST_CASE("credit_card", "[entity][card][credit_card]")
{
    SECTION("initialize")
    {
        CreditCard card;
        REQUIRE(card.id() == numeric_limits<size_t>::max());
        REQUIRE(card.balance() == 0);
        REQUIRE(card.credit() == 0);
    }
    SECTION("deposit")
    {
        CreditCard card;
        card.balance(15);
        card.credit(20);

        card.cash_deposit(25);
        REQUIRE(card.balance() == 40);
    }
    SECTION("withdraw")
    {
        CreditCard card;
        card.balance(15);
        card.credit(20);

        card.cash_withdraw(5);
        REQUIRE(card.balance() == 10);
        card.consume(15);
        REQUIRE(card.balance() == -5);

        REQUIRE_THROWS_AS(card.cash_withdraw(16), InsufficientBalance);
    }
    SECTION("transaction record")
    {
        CreditCard card;
        card.id(0);
        card.balance(15);
        card.credit(20);

        card.cash_withdraw(5);
        auto record = card.transaction().find_by_id(0);
        REQUIRE(record.difference() == -5l);
        REQUIRE(record.note() == "cash withdraw");

        card.cash_deposit(5);
        record = card.transaction().find_by_id(1);
        REQUIRE(record.difference() == 5l);
        REQUIRE(record.note() == "cash deposit");

        CreditCard card2;
        card2.id(1);
        card2.balance(20);
        card2.credit(10);

        card.transfer_to(card2, 10);
        record = card.transaction().find_by_id(2);
        REQUIRE(record.difference() == -10);
        REQUIRE(record.note() == "transfer to credit card <1>");
        record = card2.transaction().find_by_id(0);
        REQUIRE(record.difference() == 10);
        REQUIRE(record.note() == "transfer from credit card <0>");
    }
    SECTION("serialize")
    {
        CreditCard card;
        card.id(0);
        card.balance(15);
        card.credit(20);
        card.cash_withdraw(5);
        card.cash_deposit(5);

        stringstream ss;
        card.write(ss);

        CreditCard read;
        read.read(ss);
        REQUIRE(read.id() == 0);
        REQUIRE(read.balance() == 15);
        REQUIRE(read.credit() == 20);
        auto record = card.transaction().find_by_id(0);
        REQUIRE(record.difference() == -5l);
        REQUIRE(record.note() == "cash withdraw");
        record = card.transaction().find_by_id(1);
        REQUIRE(record.difference() == 5l);
        REQUIRE(record.note() == "cash deposit");
    }
}
