#pragma once
#include "card.hpp"
#include <memory>
#include <string>
#include "typedef.hpp"
#include "storable.hpp"
#include "identifiable.hpp"

class Transaction final : public IStorable, public IIdentifiable
{
private:
    size_t _id;
    cent_diff_t _difference;
    time_t _time;
    std::string _note;

public:
    // constructors
    Transaction();
    Transaction(cent_diff_t difference, std::string note);
    Transaction(cent_t previous, cent_t current, std::string note);
    // getter and setter
    size_t id();
    // size_t id(size_t value);
    cent_diff_t difference();
    cent_diff_t difference(cent_diff_t value);
    time_t time();
    time_t time(time_t value);
    std::string note();
    std::string note(std::string value);
    // serialize
    void write(std::ostream &output) const;
    void read(std::istream &input);
    // identifier
    size_t id() const;
    void id(size_t value);
};
