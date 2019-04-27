#include <iomanip>
#include "parser/error.hpp"
#include "evaluator.hpp"

using namespace std;

int main()
{
    Evaluator host;
    string str;
    while (cout << "polynomial> ", getline(cin, str))
    {
        try
        {
            cout << host.eval(str) << endl;
            cout << "| "
                 << setw(4) << "name"
                 << " | "
                 << setw(48) << left << "value"
                 << " |" << endl;
            cout << "| "
                 << string(4, '-') << " | "
                 << string(48, '-') << " |" << endl;
            for (auto it : host.get_variables())
            {
                cout << "| "
                     << setw(4) << it.first << " | "
                     << setw(48) << left << it.second.to_string() << " |" << endl;
            }
            cout << endl
                 << "| "
                 << setw(48) << left << "History"
                 << " |" << endl;
            for (auto it : host.get_history())
            {
                cout << "| "
                     << setw(48) << left << it.to_string() << " |" << endl;
            }
        }
        catch (Error e)
        {
            cerr << e << endl;
        }
        catch (string s)
        {
            cerr << s << endl;
        }
    }
    return 0;
}
