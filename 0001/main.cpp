#include "database/good.hpp"
#include "database/good_repo.hpp"
#include "ui.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const string FILENAME = "proj1.bin";

void read(GoodRepository &repo, string filename)
{
    ifstream fin(filename, ios::binary);
    repo.read(fin);
}
void write(const GoodRepository &repo, string filename)
{
    ofstream fout(filename, ios::binary);
    repo.write(fout);
}
int main()
{
    GoodRepository repo = GoodRepository();
    read(repo, FILENAME);
    print_help();
    Op op;
    while ((op = print_menu()) != OP_QUIT)
    {
        switch (op)
        {
        case OP_IMPORT:
            import_good(repo);
            break;
        case OP_EXPORT:
            export_good(repo);
            break;
        case OP_LIST_ALL:
            query_good_all(repo);
            break;
        case OP_QUERY:
            query_good_by_name(repo);
            break;
        case OP_HELP:
        default:
            print_help();
            break;
        }
        write(repo, FILENAME);
    }
    return 0;
}
