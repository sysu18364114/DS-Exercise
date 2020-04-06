
// 2020/4/1 //

#include <iostream>
#include <cstdlib>

void test(int x)
{
    std::cout << x << std::endl;
}

int main()
{
    int x = 0;
    test(++x);

    system("pause");
    return 0;
}