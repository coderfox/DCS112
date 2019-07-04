#include "binding_card.hpp"
#include "singleton.hpp"

using namespace std;

IMPL_GETTER_SETTER(BindingCard, const set<size_t> &, binding_cards);

void BindingCard::deposit(cent_t amount, std::string note)
{
    CampusCard::deposit(amount, note);
}

void BindingCard::withdraw(cent_t amount, std::string note)
{
    try
    {
        CampusCard::withdraw(amount, note);
        return;
    }
    catch (InsufficientBalance)
    {
        auto repo = Singleton<Repository<CreditCard>>();
        for (auto it : _binding_cards)
        {
            auto &cc = repo->find_by_id(it);
            if (cc.balance_coverable(amount))
            {
                transfer_from(cc, amount);
                CampusCard::withdraw(amount, note);
                return;
            }
        }
        for (auto it : _binding_cards)
        {
            auto &cc = repo->find_by_id(it);
            try
            {
                transfer_from(cc, amount);
                CampusCard::withdraw(amount, note);
                return;
            }
            catch (InsufficientBalance)
            {
            }
        }
    }
}

void BindingCard::bind(size_t remote)
{
    _binding_cards.insert(remote);
}

void BindingCard::write(std::ostream &output) const
{
    CampusCard::write(output);
    ::write(output, _binding_cards.size());
    for (auto iter : _binding_cards)
    {
        ::write(output, iter);
    }
}

void BindingCard::read(std::istream &input)
{
    CampusCard::read(input);
    size_t cnt = 0;
    ::read(input, cnt);
    for (size_t i = 0; i < cnt; i++)
    {
        size_t data;
        ::read(input, data);
        _binding_cards.insert(data);
    }
}
