#include <iostream>
#include "color.hpp"
#include "singleton.hpp"
#include "repository.hpp"
#include "credit_card.hpp"
#include "campus_card.hpp"
#include <fstream>
#include <iomanip>
#include "ui.hpp"
#include "binding_card.hpp"

using namespace std;

const char *DB_FILE = "card.db";

void handle_init();
void handle_help();
void handle_exit();

#define MAKE_OP(OP)      \
    else if (str == #OP) \
        op_##OP()

int main()
{
    handle_init();
    string str;
    while (cout << color::FG_CYAN << "card> " << color::OP_RESET, getline(cin, str), !cin.eof())
    {
        try
        {
            if (str == "help")
                handle_help();
            MAKE_OP(list);
            MAKE_OP(create);
            MAKE_OP(query);
            MAKE_OP(update);
            MAKE_OP(credit_transfer);
            MAKE_OP(credit_deposit);
            MAKE_OP(campus_deposit);
            MAKE_OP(consume);
            MAKE_OP(bind);
            else if (str == "exit")
            {
                break;
            }
            else
            {
                cout << color::FG_YELLOW << "Invalid operation: " << color::OP_RESET
                     << color::OP_UNDERLINE << (str.empty() ? "(empty)" : str) << color::OP_UNDERLINE_OFF << endl;
                handle_help();
            }
        }
        catch (std::exception &e)
        {
            cerr << color::FG_RED << e.what() << color::OP_RESET << endl;
        }
        handle_exit();
    }
    handle_exit();
    return 0;
}

void handle_init()
{
    ifstream fin(DB_FILE, ios::binary);
    Singleton<Repository<CreditCard>>::initialize(make_unique<Repository<CreditCard>>());
    Singleton<Repository<CreditCard>> credit_card_repo;
    credit_card_repo->read(fin);
    Singleton<Repository<BindingCard>>::initialize(make_unique<Repository<BindingCard>>());
    Singleton<Repository<BindingCard>> campus_card_repo;
    campus_card_repo->read(fin);
}

#define MAKE_HELP(OP, DESC)                     \
    cout << color::FG_YELLOW << setw(24) << #OP \
         << color::OP_RESET << "    " << DESC << endl;

void handle_help()
{
    cout << color::BG_CYAN << color::FG_MAGENTA << color::OP_BOLD
         << "Card Manage System v1.0 by xfoxfu" << color::OP_RESET << endl
         << color::BG_GREEN << "Help:" << color::OP_RESET << endl;

    MAKE_HELP(list, "list all cards");
    MAKE_HELP(create, "create card");
    MAKE_HELP(query, "get card information");
    // MAKE_HELP(update_card, "change card information");
    MAKE_HELP(credit_transfer, "transfer from credit card");
    MAKE_HELP(credit_deposit, "deposit to credit card");
    MAKE_HELP(campus_deposit, "deposit to campus card");
    MAKE_HELP(consume, "comsume entity by card");
    MAKE_HELP(bind, "bind campus card to credit card");
}

void handle_exit()
{
    ofstream fout(DB_FILE, ios::binary);
    Singleton<Repository<CreditCard>> credit_card_repo;
    credit_card_repo->write(fout);
    Singleton<Repository<BindingCard>> campus_card_repo;
    campus_card_repo->write(fout);
}
