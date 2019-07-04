#pragma once
#include <cstddef>

class IIdentifiable
{
public:
    virtual ~IIdentifiable();
    virtual size_t id() const = 0;
    virtual void id(size_t value) = 0;
    void set_id(size_t &counter);
};
