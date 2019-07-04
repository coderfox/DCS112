#include "campus_card.hpp"
#include "credit_card.hpp"
#include <set>

class BindingCard : public CampusCard
{
private:
    std::set<size_t> _binding_cards;

public:
    DEFN_GETTER_SETTER(const std::set<size_t> &, binding_cards);

    void deposit(cent_t amount, std::string note = "");
    void withdraw(cent_t amount, std::string note = "");

    void bind(size_t remote);

    void write(std::ostream &output) const;
    void read(std::istream &input);
};
