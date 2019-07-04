#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    int count;
    cin >> count;
    for (int i = 0; i < count; i++)
    {
        string str;
        cin >> str;

        int weight = 10;
        int sum = 0;
        for (auto chr : str)
        {
            if (isdigit(chr))
                sum += (chr - '0') * (weight--);
        }
        sum = 11 - (sum % 11);
        char append = sum == 10 ? 'X' : (sum + '0');

        cout << str << '-' << append << endl;
    }
    return 0;
}

// 4
// 0-07-109219
// 0-534-95054
// 963-10-0604
// 1-890880-01