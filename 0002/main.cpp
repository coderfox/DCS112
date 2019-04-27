#include <iomanip>
#include "parser/error.hpp"
#include "evaluator.hpp"

#define COLOR_OUTPUT

using namespace std;

int main()
{
    Evaluator host;
    string str;
#ifdef COLOR_OUTPUT
    while (cout << "\033[4;36m"
                << "polynomial>"
                << "\033[0m ",
           getline(cin, str))
#else
    while (cout << "polynomial> ", getline(cin, str))
#endif
    {
        try
        {
            auto poly = host.eval(str);
            cout << "Result = " << poly << endl;
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
    }
    return 0;
}
