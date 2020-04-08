
// 2020/4/3 //

#include "binary_search_tree.h"

int main()
{
    std::vector<int> vec1 = {25, 18, 69, 5, 20, 32, 45};
    BSTree<int> testBSTree1(vec1);

    if(testBSTree1.SearchBSNode(181))
    {
        std::cout << "Successfully" << std::endl;
    }
    else
    {
        std::cout << "Failed" << std::endl;
    }

    testBSTree1.PreOrderPrint();

    if(testBSTree1.DeleteBSNode(32))
    {
        std::cout << "Successfully" << std::endl;
    }
    else
    {
        std::cout << "Failed" << std::endl;
    }

    testBSTree1.PreOrderPrint();

    if(testBSTree1.DeleteBSNode(5))
    {
        std::cout << "Successfully" << std::endl;
    }
    else
    {
        std::cout << "Failed" << std::endl;
    }

    testBSTree1.PreOrderPrint();

    if(testBSTree1.DeleteBSNode(25))
    {
        std::cout << "Successfully" << std::endl;
    }
    else
    {
        std::cout << "Failed" << std::endl;
    }

    testBSTree1.PreOrderPrint();    

    system("pause");
    return 0;
}