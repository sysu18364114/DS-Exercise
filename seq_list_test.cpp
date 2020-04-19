
// 2020/3/25 //

#include "SeqList.h"

int main()
{
    SeqList<int> sq1;

    sq1.CreateSeqList(std::vector<int>({-1, 20, 1, 3, 4}));

    std::vector<int> indVec = sq1.LocateELem(1);
    for(auto ele : indVec)
    {
        std::cout << ele << " ";
    }
    std::cout << std::endl;

    int res = 0;
    sq1.GetElem(1, res);
    std::cout << res << std::endl;

    sq1.PrintSeqList();

    sq1.SeqListInsert(3, 100);

    sq1.PrintSeqList();

    sq1.SeqListDelete(4, res);
    std::cout << res << std::endl;

    sq1.PrintSeqList();

    system("pause");
    return 0;
}