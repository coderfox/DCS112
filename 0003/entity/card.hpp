#pragma once
#include "typedef.hpp"
#include "storable.hpp"
#include "identifiable.hpp"

class Card : public IStorable, public IIdentifiable
{
public:
    virtual ~Card();
    virtual void deposit(cent_t amount, std::string note = "") = 0;
    virtual void withdraw(cent_t amount, std::string note = "") = 0;
    virtual std::string to_str() const noexcept = 0;

    friend std::string to_string(const Card &card) noexcept;
};
