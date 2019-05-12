#include "head.h"

DERIVED set(int, int);
void get(DERIVED &);

int main() {
    int n;
    int i, j;
    std::cin >> n;
    while(n--) {
        std::cin >> i >> j;
        DERIVED obj = set(i, j);
        get(obj);
    }
    return 0;
}

