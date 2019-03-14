#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

char *convertDecimalToHex(int value);
void convertDecimalToHex(int value, char *s);

int get_hex_digits(int value)
{
    return ceil(log2(value) / 4);
}

char *convertDecimalToHex(int value)
{
    char *res = new char[get_hex_digits(value) + 1];
    convertDecimalToHex(value, res);
    return res;
}

void convertDecimalToHex(int value, char *s)
{
    sprintf(s, "%x", value);
}

int main()
{
    int value;
    cin >> value;
    cout << hex << value << endl;
    char *res = new char[get_hex_digits(value) + 1];
    convertDecimalToHex(value, res);
    cout << res << endl;
    delete[] res;
    res = convertDecimalToHex(value);
    cout << res << endl;
    delete[] res;
    return 0;
}