#include <iostream>
#include <iomanip>
#include "color.hpp"
#include "parser/error.hpp"
#include "evaluator.hpp"
#include "getline.hpp"
#include "ui.hpp"

#ifndef NO_LINENOISE
#include "linenoise.hpp"
#endif

using namespace std;

int main()
{
    Evaluator host;
    handle_help();

    pair<bool, string> input;
    while (input = getline("calculator> "), input.first)
    {
        auto str = input.second;
        if (str.empty())
            continue;

        try
        {
            if (str == "help")
                handle_help();
            else if (str == "help-extra")
                handle_help(true);
            else if (str == "add")
                handle_add(host);
            else if (str == "mul")
                handle_multiply(host);
            else if (str == "minus")
                handle_minus(host);
            else if (str == "eval")
                handle_evaluate(host);
            else if (str == "equal")
                handle_equal(host);
            else if (str == "derive")
                handle_derive(host);
            else if (str == "history")
                handle_history(host);
            else if (str == "memory")
                handle_memory(host);
            else if (str == "exit")
            {
                break;
            }
            else
                handle_plain(host, str);
        }
        catch (Error e)
        {
            cerr << e << endl;
        }
        catch (vector<Error> es)
        {
            for (auto it : es)
            {
                cout << it << endl;
            }
        }
    }
    handle_exit();

    return 0;
}
