#pragma once

#include <exception>

#define _DEFINE_EXCEPTION(N, R)           \
    struct N : public std::exception      \
    {                                     \
        const char *what() const noexcept \
        {                                 \
            return R;                     \
        }                                 \
    }

_DEFINE_EXCEPTION(SingletonNotInitialized,
                  "Singleton is not initialized.");

_DEFINE_EXCEPTION(SingletonAlreadyInitialized,
                  "Singleton has already been initialized.");

_DEFINE_EXCEPTION(InsufficientBalance,
                  "Balance is insufficient to cover this transaction.");

_DEFINE_EXCEPTION(InvalidIdentifier,
                  "Invalid identifier provided for save(), use insert() instead.");

_DEFINE_EXCEPTION(EntityNotExists,
                  "Requested identity does not exist.");

#undef _DEFINE_EXCEPTION
