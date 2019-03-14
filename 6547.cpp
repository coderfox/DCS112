#include <string>

using std::string;

string MyStringPractise(const string &s1, const string &s2)
{
    int begin = s2.size() - 3;
    if (begin < 0)
        begin = 0;
    return s1.substr(0, 3) + s2.substr(begin, s2.size());
}

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

string MyStringPractise(const string &s1, const string &s2);

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    cout << MyStringPractise(s1, s2) << endl;
    return 0;
}