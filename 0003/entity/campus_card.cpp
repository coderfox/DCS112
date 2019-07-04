#include "campus_card.hpp"
#include "exceptions.hpp"
#include "utils.hpp"

using namespace std;

CampusCard::CampusCard()
{
    _balance = 0;
    _card_no = numeric_limits<size_t>::max();
    _stu_id = 0;
    _holder_name = "INVALID";
    _school = "INVALID";
}

IMPL_GETTER_SETTER(CampusCard, cent_t, balance)
IMPL_GETTER_SETTER(CampusCard, Repository<Transaction>, transaction)

IMPL_GETTER_SETTER(CampusCard, size_t, card_no);
IMPL_GETTER_SETTER(CampusCard, size_t, stu_id);
IMPL_GETTER_SETTER(CampusCard, std::string, holder_name);
IMPL_GETTER_SETTER(CampusCard, std::string, school);

void CampusCard::deposit(cent_t amount, string note)
{
    _balance += amount;
    _transaction.insert(amount, note);
}

void CampusCard::withdraw(cent_t amount, string note)
{
    if (_balance >= amount)
    {
        _balance -= amount;
        _transaction.insert(-static_cast<cent_diff_t>(amount), note);
    }
    else
    {
        throw InsufficientBalance();
    }
}

void CampusCard::consume(cent_t amount)
{
    withdraw(amount, "consume");
}

void CampusCard::transfer_from(CreditCard &source, cent_t amount)
{
    source.transfer_to(*this, amount);
}

void CampusCard::write(ostream &output) const
{
    ::write(output, _balance);
    _transaction.write(output);
    ::write(output, _card_no);
    ::write(output, _stu_id);
    ::write(output, _holder_name);
    ::write(output, _school);
}

void CampusCard::read(istream &input)
{
    ::read(input, _balance);
    _transaction.read(input);
    ::read(input, _card_no);
    ::read(input, _stu_id);
    ::read(input, _holder_name);
    ::read(input, _school);
}

size_t CampusCard::id() const
{
    return _card_no;
}

void CampusCard::id(size_t value)
{
    _card_no = value;
}

std::string CampusCard::to_str() const noexcept
{
    return "campus card <" + to_string(id()) + ">";
}
