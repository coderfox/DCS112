#include <iostream>
#include "6750/Stack.hpp"
using namespace std;

int main()
{
    freopen("6750.out", "w", stdout);
    Stack s1;

    int n, opt, num;
    cin >> n;
    while (n--)
    {
        cin >> opt;
        if (opt == 0)
        {
            // push
            int num;
            cin >> num;
            s1.push(num); // leak
            cout << "push " << num << endl;
        }
        else if (opt == 1)
        {
            // pop
            if (!s1.empty())
            {
                int num = s1.top();
                s1.pop();
                cout << "pop " << num << endl;
            }
            else
            {
                cout << "stack is empty!" << endl;
            }
        }
    }

    cout << "s1 = s1" << endl;
    s1 = s1; // leak

    Stack s2;
    s2.push(1);
    s2 = s1; // leak
    cout << "s2 = s1" << endl;

    s1.clear();
    cout << "s1 is empty: " << (s1.empty() ? "True" : "False") << endl;

    while (!s2.empty())
    {
        int num = s2.top();
        s2.pop();
        cout << "pop " << num << endl;
    }

    return 0;
}