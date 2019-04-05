#ifndef H_UI
#define H_UI

#include "database/good_repo.hpp"

typedef enum : char
{
    OP_INVALID = -1,
    OP_QUIT = 'x',
    OP_IMPORT = 'i',
    OP_EXPORT = 'e',
    OP_LIST_ALL = 'l',
    OP_QUERY = 'q',
    OP_HELP = 'h',
} Op;

Op print_menu();
void print_help();
void import_good(GoodRepository &repo);
void export_good(GoodRepository &repo);
void query_good_all(GoodRepository &repo);
void query_good_by_name(GoodRepository &repo);

#endif
