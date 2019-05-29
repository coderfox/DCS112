#include "printArray.h"

int main()
{
    int intArr[6] = {1, 2, 3, 4, 5, 6};
    double dblArr[4] = {1.2, 2.3, 3.4, 4.5};

    printValues(intArr); // 生成函数实例printValues(int (&) [6])
    printValues(dblArr); // 生成函数实例printValues(double (&) [4])
    return 0;
}
