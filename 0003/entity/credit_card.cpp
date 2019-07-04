#include "credit_card.hpp"
#include "exceptions.hpp"
#include "utils.hpp"

using namespace std;

CreditCard::CreditCard()
{
    _balance = 0;
    _credit = 0;
    _card_no = numeric_limits<size_t>::max();
    _issue_time = time(nullptr);
    _holder_name = "INVALID";
}

IMPL_GETTER_SETTER(CreditCard, scent_t, balance);
IMPL_GETTER_SETTER(CreditCard, cent_t, credit);
IMPL_GETTER_SETTER(CreditCard, Repository<Transaction>, transaction);

IMPL_GETTER_SETTER(CreditCard, size_t, card_no);
IMPL_GETTER_SETTER(CreditCard, time_t, issue_time);
IMPL_GETTER_SETTER(CreditCard, std::string, holder_name);

void CreditCard::deposit(cent_t amount, string note)
{
    _balance += amount;
    _transaction.insert(amount, note);
}

void CreditCard::withdraw(cent_t amount, string note)
{
    if (_balance + _credit >= amount)
    {
        _balance -= amount;
        _transaction.insert(-static_cast<cent_diff_t>(amount), note);
    }
    else
    {
        throw InsufficientBalance();
    }
}

bool CreditCard::balance_coverable(cent_t amount) const noexcept
{
    return _balance >= amount;
}

void CreditCard::transfer_to(Card &target, cent_t amount)
{
    withdraw(amount, "transfer to " + to_string(target));
    target.deposit(amount, "transfer from " + to_string(*this));
}

void CreditCard::cash_deposit(cent_t amount)
{
    deposit(amount, "cash deposit");
}

void CreditCard::cash_withdraw(cent_t amount)
{
    withdraw(amount, "cash withdraw");
}

void CreditCard::consume(cent_t amount)
{
    withdraw(amount, "consume");
}

void CreditCard::write(ostream &output) const
{
    ::write(output, _balance);
    ::write(output, _credit);
    _transaction.write(output);
    ::write(output, _card_no);
    ::write(output, _issue_time);
    ::write(output, _holder_name);
}

void CreditCard::read(istream &input)
{
    ::read(input, _balance);
    ::read(input, _credit);
    _transaction.read(input);
    ::read(input, _card_no);
    ::read(input, _issue_time);
    ::read(input, _holder_name);
}

size_t CreditCard::id() const
{
    return _card_no;
}

void CreditCard::id(size_t value)
{
    _card_no = value;
}

std::string CreditCard::to_str() const noexcept
{
    return "credit card <" + to_string(id()) + ">";
}
