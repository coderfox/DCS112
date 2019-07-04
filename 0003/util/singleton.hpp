#pragma once
#include <memory>
#include "exceptions.hpp"

template <class T>
class Singleton
{
private:
    static std::unique_ptr<T> _data;

public:
    Singleton();
    static void initialize(std::unique_ptr<T> data);
    T &operator*();
    T *operator->();
    T &self();
};

template <class T>
std::unique_ptr<T> Singleton<T>::_data = nullptr;

template <class T>
Singleton<T>::Singleton()
{
    if (_data == nullptr)
    {
        throw SingletonNotInitialized();
    }
}

template <class T>
void Singleton<T>::initialize(std::unique_ptr<T> data)
{
    if (_data == nullptr)
    {
        _data = move(data);
    }
    else
    {
        throw SingletonAlreadyInitialized();
    }
}

template <class T>
T &Singleton<T>::operator*()
{
    return *_data;
}

template <class T>
T *Singleton<T>::operator->()
{
    return _data.get();
}

template <class T>
T &Singleton<T>::self()
{
    return *_data;
}