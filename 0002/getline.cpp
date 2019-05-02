#include <iostream>
#include "getline.hpp"
#include "color.hpp"

using namespace std;

#ifndef NO_LINENOISE
#include "linenoise.hpp"

pair<bool, string> getline(string prompt)
{
    prompt = color::FG_CYAN + prompt + color::OP_RESET;
    string str;
    auto ret = linenoise::Readline(prompt.c_str(), str);
    // if (!str.empty())
    linenoise::AddHistory(str.c_str());

    return make_pair(!ret, str);
}

#else
pair<bool, string> getline(string prompt)
{
    cout << prompt;
    string str;
    getline(cin, str);
    return make_pair(!cin.eof(), str);
}
#endif
