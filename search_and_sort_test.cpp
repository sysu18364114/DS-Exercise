
// 2020/4/2 //

#include "search_and_sort.h"

#include <fstream>
#include <iterator>

int main()
{
    std::vector<int> testVec1 = {4, 5, 2, 7, 8, 9, 1, -1, -2, 20};
    Search<int> test1(testVec1);

    test1.PrintTestVec();
    std::cout << test1.SeqSearch(10) << std::endl;

    std::cout << test1.BinSearchIte(5) << std::endl;
    std::cout << test1.BinSearchRec(5) << std::endl;

    if(test1.BSTreeSearch(2) && test1.LHashListSearch(7))
    {
        std::cout << "2 and 7 Found" << std::endl;
    }

    std::ostream_iterator<int> stdOutInt(std::cout, " ");

    Sort<int> sort1(testVec1);
    std::vector<int> outputVec1 = sort1.StraightInsertSort();
    std::copy(outputVec1.begin(), outputVec1.end(), stdOutInt);
    std::cout << std::endl;

    std::vector<int> outputVec2 = sort1.ShellInsertSort();
    std::copy(outputVec2.begin(), outputVec2.end(), stdOutInt);
    std::cout << std::endl;

    std::vector<int> outputVec3 = sort1.BubbleSort();
    std::copy(outputVec3.begin(), outputVec3.end(), stdOutInt);
    std::cout << std::endl;

    std::vector<int> outputVec4 = sort1.QuickSort();
    std::copy(outputVec4.begin(), outputVec4.end(), stdOutInt);
    std::cout << std::endl;
    
    system("pause");
    return 0;
}