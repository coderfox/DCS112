#pragma once
#include "typedef.hpp"
#include "card.hpp"
#include "storable.hpp"
#include "identifiable.hpp"
#include "transaction.hpp"
#include "repository.hpp"
#include <vector>

class CreditCard : public Card
{
private:
    scent_t _balance;
    cent_t _credit;
    Repository<Transaction> _transaction;

    size_t _card_no;
    time_t _issue_time;
    std::string _holder_name;

public:
    CreditCard();

    DEFN_GETTER_SETTER(scent_t, balance);
    DEFN_GETTER_SETTER(cent_t, credit);
    DEFN_GETTER_SETTER(Repository<Transaction>, transaction);

    DEFN_GETTER_SETTER(size_t, card_no);
    DEFN_GETTER_SETTER(time_t, issue_time);
    DEFN_GETTER_SETTER(std::string, holder_name);

    void deposit(cent_t amount, std::string note = "");
    void withdraw(cent_t amount, std::string note = "");

    bool balance_coverable(cent_t amount) const noexcept;
    void transfer_to(Card &target, cent_t amount);
    void cash_deposit(cent_t amount);
    void cash_withdraw(cent_t amount);
    void consume(cent_t amount);

    void write(std::ostream &output) const;
    void read(std::istream &input);

    size_t id() const;
    void id(size_t value);
    std::string to_str() const noexcept;
};
