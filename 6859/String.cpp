#include <cstring>
#include <algorithm>
#include "String.h"

using namespace std;

void extend(char **src, int *size, int require_size)
{
    if (*size >= require_size)
        return;
    auto newsize = (*size * 2) > require_size ? (*size * 2) : require_size;
    char *res = new char[newsize];
    copy(*src, *src + *size, res);
    delete[](*src);
    *src = res;
    *size = newsize;
}

// constructors
String::String() : _length(0), _size(1)
{
    _buff = new char[1];
    _buff[0] = '\0';
}
String::String(const char *src)
{
    _length = strlen(src);
    _size = _length + 1;
    _buff = new char[_size];
    strcpy(_buff, src);
}
String::String(const String &src) : String()
{
    *this = src;
}
// destructor
String::~String()
{
    delete[] _buff;
}
// member methods
void String::assign(const char *src)
{
    *this = String(src);
}
void String::append(const char &other)
{
    if (_size < _length + 2)
        extend(&_buff, &_size, _length + 2);
    _buff[_length++] = other;
    _buff[_length] = '\0';
}
void String::clear()
{
    *this = String();
}
int String::compare(const String &other) const
{
    auto diff = strcmp(_buff, other._buff);
    if (diff < 0)
        return -1;
    else if (diff == 0)
        return 0;
    else
        return 1;
}
const char *String::c_str() const
{
    return _buff;
}
bool String::empty() const
{
    return _length == 0;
}
int String::find(const String &other, int pos) const
{
    char *ret = strstr(_buff, other._buff + pos);
    if (ret == NULL)
        return _length;
    else
        return ret - _buff;
}
int String::length() const
{
    return _length;
}
String String::substr(const int &pos, const int &count) const
{
    String ret;
    extend(&ret._buff, &ret._size, count + 1);
    copy(_buff + pos, _buff + pos + count, ret._buff);
    ret._buff[count] = '\0';
    return ret;
}
// overload operators
char &String::operator[](const int &index)
{
    return _buff[index];
}
void String::operator=(const String &other)
{
    extend(&_buff, &_size, other._size);
    strcpy(_buff, other._buff);
    _length = other._length;
    _size = other._size;
}
void String::operator=(const char *src)
{
    *this = String(src);
}
String String::operator+(const String &other) const
{
    String ret;
    extend(&ret._buff, &ret._size, _length + other._length + 1);
    strcpy(ret._buff, _buff);
    strcpy(ret._buff + _length, other._buff);
    ret._length = _length + other._length;
    return ret;
}
bool String::operator<(const String &other) const
{
    return compare(other) == -1;
}
bool String::operator<=(const String &other) const
{
    return compare(other) <= 0;
}
bool String::operator>(const String &other) const
{
    return compare(other) == 1;
}
bool String::operator>=(const String &other) const
{
    return compare(other) >= 0;
}
bool String::operator==(const String &other) const
{
    return compare(other) == 0;
}
bool String::operator!=(const String &other) const
{
    return compare(other) != 0;
}
// friend methods
std::ostream &operator<<(std::ostream &out, const String &str)
{
    out << str._buff;
    return out;
}
// non-meaning static property
char String::_error_sign = '\0'; // initial as any char is okay