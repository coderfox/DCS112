#include <algorithm>
#include "Sequence.h"

using namespace std;

Sequence::Sequence()
{
    a = new int[1000];
    msize = 0;
    mempty = true;
}
Sequence::~Sequence()
{
    delete[] a;
}
int Sequence::size()
{
    return msize;
}
bool Sequence::empty()
{
    return msize == 0;
}
bool Sequence::find(int value)
{
    return std::find(a, a + msize, value) != a + msize;
}
int &Sequence::at(int pos)
{
    return a[pos];
}
int Sequence::front()
{
    return a[0];
}
int Sequence::back()
{
    return a[msize - 1];
}
void Sequence::insert(int value)
{
    mempty = false;
    a[msize++] = value;
}
void Sequence::insert(int pos, int value)
{
    copy(a + pos, a + msize, a + pos + 1);
    a[pos] = value;
    msize++;
}
void Sequence::clear()
{
    msize = 0;
    mempty = true;
}
void Sequence::reverse()
{
    for (int pos = 0; pos < msize / 2; pos++)
    {
        std::swap(a[pos], a[msize - pos - 1]);
    }
}
void Sequence::reverse(int fir, int las)
{
    for (int pos = fir; pos <= (fir + las - 1) / 2; pos++)
    {
        std::swap(a[pos], a[las - (pos - fir) - 1]);
    }
}
void Sequence::replace(int value1, int value2)
{
    for (int pos = 0; pos < msize; pos++)
    {
        if (a[pos] == value1)
            a[pos] = value2;
    }
}
void Sequence::swap(Sequence &seq2)
{
    std::swap(this->a, seq2.a);
    std::swap(this->msize, seq2.msize);
}