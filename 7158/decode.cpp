#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

int main()
{
    string str;
    while (cin >> str, str != "x")
    {
        istringstream in(str);
        string res;

        char chr;
        while (in >> chr)
        {
            int count = 1;
            if (isdigit(in.peek()))
            {
                in >> count;
            }
            res.append(count, chr);
        }
        cout << res << endl;
    }
    return 0;
}