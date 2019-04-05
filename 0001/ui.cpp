#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include "database/good.hpp"
#include "database/good_repo.hpp"
#include "ui.hpp"

using namespace std;

Op print_menu()
{
    // acquire user input
    Op operation;
    cout << endl
         << "Type an operation > ";
    do
    {
        operation = static_cast<Op>(cin.get());
    } while (!isgraph(operation));
    // print goodbye for quit
    if (operation == OP_QUIT)
        cout << "Goodbye" << endl;

    return operation;
}
void print_help()
{
    cout << "Garage Manage System (GMS) v1.0 by xfoxfu" << endl;
    cout << "Operations:" << endl;
    cout << "x -> Quit" << endl;
    cout << "i -> Import Good" << endl;
    cout << "e -> Export Good" << endl;
    cout << "l -> List All Goods" << endl;
    cout << "q -> Query Single Good By Name" << endl;
    cout << "h -> Print Help" << endl;
}
void import_good(GoodRepository &repo)
{
    // acquire user input
    string name;
    unsigned int count;
    cout << "Please input good name: ";
    cin >> name;
    cout << "Please input import count: ";
    cin >> count;

    Good good;
    // check whether good already exists
    if (repo.contains(name))
    {
        // increment good count
        good = repo.find_by_name(name);
        good.set_count(good.get_count() + count);
    }
    else
    {
        // create new good
        good = Good(name, count);
    }
    // save good
    repo.save(good);
    cout << "Import success!" << endl;
    cout << "Good Name:  " << good.get_name() << endl;
    cout << "Good Count: " << good.get_count() << endl;
}

void export_good(GoodRepository &repo)
{
    // acquire user input
    string name;
    unsigned int count;
    cout << "Please input good name: ";
    cin >> name;
    cout << "Please input export count: ";
    cin >> count;
    Good good;
    // check whether good exists
    if (!repo.contains(name))
    {
        // prompt good not exist
        cout << "Good does not exist!" << endl;
    }
    else
    {
        good = repo.find_by_name(name);
        // check good count satisfies
        if (good.get_count() < count)
        {
            cout << "Good insufficient!" << endl;
        }
        else
        {
            // all ok, perform reduce
            good.set_count(good.get_count() - count);
            repo.save(good);
            cout << "Export success!" << endl;
            cout << "Good Name:  " << good.get_name() << endl;
            cout << "Good Count: " << good.get_count() << endl;
            // remove if count is 0
            if (good.get_count() <= 0)
            {
                repo.remove(good);
            }
        }
    }
}

void query_good_all(GoodRepository &repo)
{
    cout << "|  Good Name | Count |" << endl;
    cout << "| ---------- | ----- |" << endl;
    auto list = repo.get_all();
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        auto good = *iter;
        cout << "| "
             << setw(10) << good.get_name() << " | "
             << setw(5) << good.get_count() << " |" << endl;
    }
}

void query_good_by_name(GoodRepository &repo)
{
    // acquire user input
    string name;
    cout << "Please input good name: ";
    cin >> name;
    // check if good exists
    if (!repo.contains(name))
    {
        cout << "Good does not exist!" << endl;
    }
    else
    {
        // output
        auto good = repo.find_by_name(name);
        cout << "Good Name:  " << good.get_name() << endl;
        cout << "Good Count: " << good.get_count() << endl;
    }
}