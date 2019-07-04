#include <exception>
#include <cctype>

using namespace std;

class NumberParseException : public exception
{
public:
    const char *str;
    explicit NumberParseException(const char *str) : str(str) {}
};

int parseNumber(const char *str);
bool isNumber(const char *str);

int parseNumber(const char *str)
{
    if (!isNumber(str))
        throw NumberParseException(str);
    int result = 0;
    int flag = 1;
    if (str != nullptr && (*str == '+' || *str == '-'))
    {
        str++;
        if (*str == '-')
            flag = -1;
    }
    for (auto *p = str; p != nullptr && *p != '\0'; p++)
    {
        result *= 10;
        result += *p - '0';
    }
    // if (result == 0)
    //     throw NumberParseException(str);
    return result * flag;
}
bool isNumber(const char *str)
{
    if (str != nullptr && (*str == '+' || *str == '-'))
        str++;
    for (auto *p = str; p != nullptr && *p != '\0'; p++)
    {
        if (!isdigit(*p))
            return false;
    }
    return true;
}
