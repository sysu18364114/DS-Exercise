
// 2020/3/31 //

#include "binary_tree.h"

int main()
{
    BNode<int>(10).PrintBNode();

    std::vector<int> cstVec1 = {1, 2, 3, -1, -1, 4, -1, -1, 5, 6};
    
    BTree<int> bTree1(cstVec1, intNullTag);
    bTree1.PrevOrderPrint(REC);
    bTree1.InOrderPrint(ITE);
    bTree1.PostOrderPrint(ITE);
    bTree1.LevelOrderPrint();

    std::cout << bTree1.FindKLevel(3) << std::endl;

    system("pause");
    return 0;
}