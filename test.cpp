
// 2020/4/1 //


#include <iostream>
#include <cstdlib>
#include <iterator>
#include <functional>

using std::function;


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