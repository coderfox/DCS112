#include "card.hpp"

Card::~Card() {}

std::string to_string(const Card &card) noexcept
{
    return card.to_str();
}
