#include <iostream>
#include "color.hpp"
#include "ui.hpp"
#include "credit_card.hpp"
#include "campus_card.hpp"
#include "binding_card.hpp"
#include "singleton.hpp"
#include "repository.hpp"
#include <iomanip>

using namespace std;

void _prompt_input(const char *help, const char *prompt)
{
    cout << color::FG_GREEN << help << color::OP_RESET << endl
         << color::FG_CYAN << prompt << color::OP_RESET;
}
template <typename T>
class _safe_integer_input
{
public:
    T operator()()
    {
        bool ok = false;
        string str;
        T ret;
        do
        {
            getline(cin, str);
            try
            {
                ret = stoi(str);
                ok = true;
            }
            catch (std::exception &)
            {
            }
        } while (!ok);
        return ret;
    }
};

void _print_transaction_history(const Repository<Transaction> &repo)
{
    cout << color::FG_MAGENTA << '|'
         << setw(8) << "Diff" << '|'
         << setw(24) << "Time" << '|'
         << setw(36) << "Note" << '|'
         << color::OP_RESET << endl;
    auto list = repo.get_all();
    list.reverse();
    for (auto it : list)
    {
        auto time = it->time();
        cout << '|'
             << setw(8) << it->difference() << '|'
             << setw(24) << strtok(ctime(&time), "\n") << '|'
             << setw(36) << it->note() << '|' << endl;
    }
}

void _print_card(const Card &card, bool skip_transaction = false)
{
    cout << color::FG_YELLOW << card.to_str() << color::OP_RESET << endl;
    auto credit = dynamic_cast<const CreditCard *>(&card);
    if (credit != nullptr)
    {
        auto iss_time = credit->issue_time();
        cout << color::FG_GREEN << setw(16) << "id: " << color::OP_RESET
             << credit->card_no() << endl
             << color::FG_GREEN << setw(16) << "issue time: " << color::OP_RESET
             << ctime(&iss_time)
             << color::FG_GREEN << setw(16) << "holder name: " << color::OP_RESET
             << credit->holder_name() << endl
             << color::FG_GREEN << setw(16) << "balance: " << color::OP_RESET
             << credit->balance() << endl
             << color::FG_GREEN << setw(16) << "credit: " << color::OP_RESET
             << credit->credit() << endl;
        if (!skip_transaction)
        {
            cout << color::FG_YELLOW << "Transactions: " << color::OP_RESET << endl;
            _print_transaction_history(credit->transaction());
        }
    }
    auto campus = dynamic_cast<const BindingCard *>(&card);
    if (campus != nullptr)
    {
        cout << color::FG_GREEN << setw(16) << "id: " << color::OP_RESET
             << campus->card_no() << endl
             << color::FG_GREEN << setw(16) << "student id: " << color::OP_RESET
             << campus->stu_id() << endl
             << color::FG_GREEN << setw(16) << "holder name: " << color::OP_RESET
             << campus->holder_name() << endl
             << color::FG_GREEN << setw(16) << "balance: " << color::OP_RESET
             << campus->balance() << endl
             << color::FG_GREEN << setw(16) << "school: " << color::OP_RESET
             << campus->school() << endl
             << color::FG_GREEN << setw(16) << "binded card: " << color::OP_RESET;
        copy(campus->binding_cards().begin(), campus->binding_cards().end(), ostream_iterator<size_t>(cout, " "));
        cout << endl;
        if (!skip_transaction)
        {
            cout << color::FG_YELLOW << "Transactions: " << color::OP_RESET << endl;
            _print_transaction_history(campus->transaction());
        }
    }
}

void op_list()
{
    cout << color::FG_YELLOW << "Credit Card:" << color::OP_RESET << endl;
    cout << color::FG_MAGENTA << '|'
         << setw(4) << "ID" << '|'
         << setw(24) << "Holder" << '|'
         << setw(8) << "Balance" << '|'
         << setw(8) << "Credit" << '|' << color::OP_RESET << endl;
    Singleton<Repository<CreditCard>> credit_repo;
    for (auto it : credit_repo->get_all())
    {
        cout << '|'
             << setw(4) << it->card_no() << '|'
             << setw(24) << it->holder_name() << '|'
             << setw(8) << it->balance() << '|'
             << setw(8) << it->credit() << '|' << endl;
    }
    cout << color::FG_YELLOW << "Campus Card:" << color::OP_RESET << endl;
    cout << color::FG_MAGENTA << '|'
         << setw(4) << "ID" << '|'
         << setw(10) << "Stu ID" << '|'
         << setw(24) << "Holder" << '|'
         << setw(8) << "Balance" << '|' << color::OP_RESET << endl;
    Singleton<Repository<BindingCard>> campus_repo;
    for (auto it : campus_repo->get_all())
    {
        cout << '|'
             << setw(4) << it->card_no() << '|'
             << setw(10) << it->stu_id() << '|'
             << setw(24) << it->holder_name() << '|'
             << setw(8) << it->balance() << '|' << endl;
    }
}

void op_create()
{
    string type;
    do
    {
        if (cin.eof())
            return;
        _prompt_input("card type: credit / campus", "card type> ");
        getline(cin, type);
    } while (type != "credit" && type != "campus");
    if (type == "credit")
    {
        CreditCard cc;
        _prompt_input("card number, or -1 for auto-generated", "card_no> ");
        size_t card_no = _safe_integer_input<size_t>()();
        cc.card_no(card_no);
        _prompt_input("initial balance", "balance> ");
        scent_t balance = _safe_integer_input<scent_t>()();
        cc.balance(balance);
        _prompt_input("initial credit", "credit> ");
        cent_t credit = _safe_integer_input<cent_t>()();
        cc.credit(credit);
        _prompt_input("holder name", "holder_name> ");
        string holder_name;
        getline(cin, holder_name);
        cc.holder_name(holder_name);

        Singleton<Repository<CreditCard>> repo;
        auto cc_ins = repo->insert(cc);
        _print_card(cc_ins);
    }
    else if (type == "campus")
    {
        BindingCard cc;
        _prompt_input("card number, or -1 for auto-generated", "card_no> ");
        size_t card_no = _safe_integer_input<size_t>()();
        cc.card_no(card_no);
        _prompt_input("initial balance", "balance> ");
        scent_t balance = _safe_integer_input<scent_t>()();
        cc.balance(balance);
        _prompt_input("student id", "stu_id> ");
        size_t stu_id = _safe_integer_input<size_t>()();
        cc.stu_id(stu_id);
        _prompt_input("holder name", "holder_name> ");
        string holder_name;
        getline(cin, holder_name);
        cc.holder_name(holder_name);
        _prompt_input("holder school", "school> ");
        string school;
        getline(cin, school);
        cc.school(school);

        Singleton<Repository<BindingCard>> repo;
        auto cc_ins = repo->insert(cc);
        _print_card(cc_ins);
    }
    cout << color::FG_GREEN << "card created successfully." << color::OP_RESET << endl;
}

void op_query()
{
    string type;
    do
    {
        if (cin.eof())
            return;
        _prompt_input("card type: credit / campus", "card type> ");
        getline(cin, type);
    } while (type != "credit" && type != "campus");
    _prompt_input("card number", "card_no> ");
    size_t card_no = _safe_integer_input<size_t>()();
    if (type == "credit")
    {
        Singleton<Repository<CreditCard>> repo;
        _print_card(repo->find_by_id(card_no));
    }
    else if (type == "campus")
    {
        Singleton<Repository<BindingCard>> repo;
        _print_card(repo->find_by_id(card_no));
    }
}

void op_update()
{
    /*     string type;
    do
    {
        if (cin.eof())
            return;
        _prompt_input("card type: credit / campus", "card type> ");
        getline(cin, type);
    } while (type != "credit" && type != "campus");
    _prompt_input("card number, or -1 for auto-generated", "card_no> ");
    size_t card_no = _safe_integer_input<size_t>()();
    if (type == "credit")
    {
        Singleton<Repository<CreditCard>> repo;
        auto card = repo->find_by_id(card_no);
    }
    else if (type == "campus")
    {
        Singleton<Repository<BindingCard>> repo;
        auto cc = repo->find_by_id(card_no);
        _print_card(cc);

        _prompt_input("card number, or empty line to skip changing", "card_no> ");
        size_t card_no = _safe_integer_input<size_t>()();
        cc.card_no(card_no);
        _prompt_input("initial balance, or empty line to skip changing", "balance> ");
        scent_t balance = _safe_integer_input<scent_t>()();
        cc.balance(balance);
        _prompt_input("student id, or empty line to skip changing", "stu_id> ");
        size_t stu_id = _safe_integer_input<size_t>()();
        cc.stu_id(stu_id);
        _prompt_input("holder name, or empty line to skip changing", "holder_name> ");
        string holder_name;
        getline(cin, holder_name);
        cc.holder_name(holder_name);
        _prompt_input("holder school", "school> ");
        string school;
        getline(cin, school);
        cc.school(school);

        repo->save(cc);
    } */
}

void op_credit_transfer()
{
    _prompt_input("source card number", "card_no> ");
    size_t card_no_src = _safe_integer_input<size_t>()();
    Singleton<Repository<CreditCard>> repo;
    if (!repo->contains(card_no_src))
    {
        cout << color::FG_RED << "card not exist" << endl;
        return;
    }
    auto &csrc = repo->find_by_id(card_no_src);
    _print_card(csrc, true);

    _prompt_input("target card number", "card_no> ");
    size_t card_no_target = _safe_integer_input<size_t>()();
    if (!repo->contains(card_no_target))
    {
        cout << color::FG_RED << "card not exist" << endl;
        return;
    }
    auto &ctar = repo->find_by_id(card_no_target);
    _print_card(ctar, true);

    _prompt_input("amount", "balance> ");
    cent_t amount = _safe_integer_input<cent_t>()();

    csrc.transfer_to(ctar, amount);

    cout << color::FG_GREEN << "transferred successfully." << color::OP_RESET << endl
         << color::FG_GREEN << "source card balance: " << color::OP_RESET
         << csrc.balance() << endl
         << color::FG_GREEN << "target card balance: " << color::OP_RESET
         << ctar.balance() << endl;
}

void op_credit_deposit()
{
    _prompt_input("source card number", "card_no> ");
    size_t card_no_src = _safe_integer_input<size_t>()();
    Singleton<Repository<CreditCard>> repo;
    if (!repo->contains(card_no_src))
    {
        cout << color::FG_RED << "card not exist" << endl;
        return;
    }
    auto &csrc = repo->find_by_id(card_no_src);
    _print_card(csrc, true);

    _prompt_input("amount", "balance> ");
    cent_t amount = _safe_integer_input<cent_t>()();

    csrc.cash_deposit(amount);

    cout << color::FG_GREEN << "deposited successfully." << color::OP_RESET << endl
         << color::FG_GREEN << "card balance: " << color::OP_RESET
         << csrc.balance() << endl;
}

void op_campus_deposit()
{
    _prompt_input("campus card number", "card_no> ");
    size_t card_no_src = _safe_integer_input<size_t>()();
    Singleton<Repository<BindingCard>> repo_cam;
    if (!repo_cam->contains(card_no_src))
    {
        cout << color::FG_RED << "card not exist" << endl;
        return;
    }
    auto &csrc = repo_cam->find_by_id(card_no_src);
    _print_card(csrc, true);

    _prompt_input("credit card number", "card_no> ");
    size_t card_no_target = _safe_integer_input<size_t>()();
    Singleton<Repository<CreditCard>> repo_cre;
    if (!repo_cre->contains(card_no_target))
    {
        cout << color::FG_RED << "card not exist" << endl;
        return;
    }
    auto &ctar = repo_cre->find_by_id(card_no_target);
    _print_card(ctar, true);

    _prompt_input("amount", "balance> ");
    cent_t amount = _safe_integer_input<cent_t>()();

    csrc.transfer_from(ctar, amount);

    cout << color::FG_GREEN << "transferred successfully." << color::OP_RESET << endl
         << color::FG_GREEN << "campus card balance: " << color::OP_RESET
         << csrc.balance() << endl
         << color::FG_GREEN << "credit card balance: " << color::OP_RESET
         << ctar.balance() << endl;
}

void op_consume()
{
    string type;
    scent_t remain_balance = 0;
    do
    {
        if (cin.eof())
            return;
        _prompt_input("card type: credit / campus", "card type> ");
        getline(cin, type);
    } while (type != "credit" && type != "campus");
    if (type == "credit")
    {
        _prompt_input("card number", "card_no> ");
        size_t card_no = _safe_integer_input<size_t>()();
        Singleton<Repository<CreditCard>> repo;
        auto &cc = repo->find_by_id(card_no);
        _print_card(cc, true);

        _prompt_input("amount", "balance> ");
        cent_t amount = _safe_integer_input<cent_t>()();
        cc.consume(amount);
        remain_balance = cc.balance();
    }
    else if (type == "campus")
    {
        _prompt_input("card number", "card_no> ");
        size_t card_no = _safe_integer_input<size_t>()();
        Singleton<Repository<BindingCard>> repo;
        auto &cc = repo->find_by_id(card_no);
        _print_card(cc, true);

        _prompt_input("amount", "balance> ");
        cent_t amount = _safe_integer_input<cent_t>()();
        cc.consume(amount);
        remain_balance = cc.balance();
    }
    cout << color::FG_GREEN << "consumed successfully." << color::OP_RESET << endl
         << color::FG_GREEN << "remaining balance: " << color::OP_RESET
         << remain_balance << endl;
}

void op_bind()
{
    _prompt_input("campus card number", "card_no> ");
    size_t cm_card_no = _safe_integer_input<size_t>()();
    Singleton<Repository<BindingCard>> cm_repo;
    auto &cm = cm_repo->find_by_id(cm_card_no);
    _print_card(cm, true);

    _prompt_input("credit card number", "card_no> ");
    size_t cc_card_no = _safe_integer_input<size_t>()();
    Singleton<Repository<CreditCard>> cc_repo;
    auto &cc = cc_repo->find_by_id(cc_card_no);
    _print_card(cc, true);

    cm.bind(cc.id());
    cout << color::FG_GREEN << "bind success" << color::OP_RESET << endl;
}