#include <iostream>
#include <map>
using namespace std;
int main()
{
    map<char, int> m;
    int i;

    //put pairs into map
    for (char i = 0; i >= 0; i++)
    {
        // cout << static_cast<int>(i) << endl;
        m[i] = static_cast<int>(i);
    }

    char ch;
    cout << "enter key:";
    cin >> ch;
    map<char, int>::iterator p;

    //find value given key ch
    p = m.find(ch);

    if (p != m.end())
        cout << "Its ASCII value is " << p->second;
    else
        cout << "Key not in map.";
    return 0;
}