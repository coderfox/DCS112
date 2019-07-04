#pragma once
#include "typedef.hpp"
#include "card.hpp"
#include "storable.hpp"
#include "identifiable.hpp"
#include "transaction.hpp"
#include "credit_card.hpp"
#include <vector>

class CampusCard : public Card
{
private:
    cent_t _balance;
    Repository<Transaction> _transaction;

    size_t _card_no;
    size_t _stu_id;
    std::string _holder_name;
    std::string _school;

public:
    CampusCard();

    DEFN_GETTER_SETTER(cent_t, balance)
    DEFN_GETTER_SETTER(Repository<Transaction>, transaction)

    DEFN_GETTER_SETTER(size_t, card_no);
    DEFN_GETTER_SETTER(size_t, stu_id);
    DEFN_GETTER_SETTER(std::string, holder_name);
    DEFN_GETTER_SETTER(std::string, school);

    virtual void deposit(cent_t amount, std::string note = "");
    virtual void withdraw(cent_t amount, std::string note = "");

    void consume(cent_t amount);
    void transfer_from(CreditCard &target, cent_t amount);

    virtual void write(std::ostream &output) const;
    virtual void read(std::istream &input);

    size_t id() const;
    void id(size_t value);
    std::string to_str() const noexcept;
};
