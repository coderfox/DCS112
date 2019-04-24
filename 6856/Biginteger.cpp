#include <algorithm>
#include <string>
#include "Biginteger.h"

using namespace std;

BigInteger::BigInteger() : size_(0)
{
    data_ = new int[1000];
}
BigInteger::BigInteger(const string &number)
{
    size_ = number.length();
    data_ = new int[size_];
    int *ptr = data_;
    for (auto iter = number.end() - 1; iter != number.begin() - 1; iter--)
    {
        *(ptr++) = *iter - '0';
    }
}
BigInteger::BigInteger(const BigInteger &other)
{
    size_ = other.size_;
    data_ = new int[size_];
    copy(other.data_, other.data_ + size_, data_);
}
BigInteger operator+(const BigInteger &lhs, const BigInteger &rhs)
{
    BigInteger result;
    result.data_[result.size_] = 0;
    for (int *lptr = lhs.data_, *rptr = rhs.data_;
         (lptr - lhs.data_) < lhs.size_ || (rptr - rhs.data_) < rhs.size_;
         lptr++, rptr++)
    {
        auto lval = (lptr - lhs.data_) < lhs.size_ ? *lptr : 0;
        auto rval = (rptr - rhs.data_) < rhs.size_ ? *rptr : 0;
        result.data_[result.size_] = lval + rval + result.data_[result.size_];
        result.data_[result.size_ + 1] = result.data_[result.size_] / 10;
        result.data_[result.size_] %= 10;
        result.size_++;
    }
    if (result.data_[result.size_] != 0) // Conditional jump or move depends on uninitialised value(s)
    {
        result.size_++;
    }
    return result;
}

BigInteger operator-(const BigInteger &lhs, const BigInteger &rhs)
{
    BigInteger result;
    result.size_ = lhs.size_;
    int cur = result.size_ - 1;
    for (int *lptr = lhs.data_ + lhs.size_ - 1, *rptr = rhs.data_ + lhs.size_ - 1;
         lptr >= lhs.data_ || rptr >= rhs.data_;
         lptr--, rptr--)
    {
        auto lval = (lptr < lhs.data_ + lhs.size_) ? *lptr : 0;
        auto rval = (rptr < rhs.data_ + rhs.size_) ? *rptr : 0;
        result.data_[cur] = lval - rval;
        {
            int ptr = cur;
            while (result.data_[ptr] < 0)
            {
                result.data_[ptr + 1]--;
                result.data_[ptr] += 10;
                ptr++;
            }
        }
        cur--;
    }
    while (result.size_ > 0 && result.data_[result.size_ - 1] == 0)
        result.size_--;
    return result;
}
ostream &operator<<(ostream &out, const BigInteger &Bint)
{
    if (Bint.size_ == 0)
        out << 0;
    for (int *ptr = Bint.data_ + Bint.size_ - 1; ptr >= Bint.data_; ptr--)
    {
        out << *ptr;
    }
    return out;
}
BigInteger::~BigInteger()
{
    delete[] data_;
}