
// 2020/3/26 //

#include "LinkList.h"

int main()
{
    LinkList<int> list1;
    std::vector<int> vec1 = {1, 2, 3, 4, 5};

    list1.CreateList(vec1);
    list1.PrintLinkList();

    list1.ListDelete(1);
    list1.PrintLinkList();

    list1.ListDelete(4);
    list1.PrintLinkList();

    list1.ListInsert(1, -1);
    list1.PrintLinkList();

    list1.ListInsert(4, -2);
    list1.PrintLinkList();

    if(list1.LocateElem(3))
    {
        std::cout << "3 search successful" << std::endl;
    }
    else
    {
        std::cout << "3 search failed" << std::endl;
    }

    // LinkList<int> list2;

    // list2.CreateList();
    // list2.PrintLinkList();

    list1.Reverse();
    list1.PrintLinkList();
    int mid = list1.MiddleElem();
    std::cout << mid << std::endl;

    std::vector<int> vec2({8, 9, 10, 21, 22});
    std::vector<int> vec3({1, 4, 7, 12, 23});
    LinkList<int> list2;
    LinkList<int> list3;
    list2.CreateList(vec2);
    list3.CreateList(vec3);

    list2.Merge(list3);
    list2.PrintLinkList();

    system("pause");
    return 0;
}