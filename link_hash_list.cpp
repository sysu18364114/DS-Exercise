
// 2020/4/4 //

#include "link_hash_list.h"

int main()
{
    std::vector<int> vec1;
    for(int i = 0; i < 100; i++)
    {
        vec1.push_back(i);
    }
    LHashList<int> lHashList1(vec1);

    lHashList1.PrintLHashList();

    if(lHashList1.SearchElem(1001))
    {
        std::cout << "Successfully" << std::endl;
    }

    system("pause");
    return 0;
}