
// 2020/3/31 //

#include "tripe_matrix.h"

int main()
{
    Elem<int> elem1(1, 1, 10);
    elem1.PrintElem();
    Elem<double*> elem2;
    elem2.PrintElem();

    std::vector<Elem<int> > cstVec1 = {
        Elem<int>(0, 0, 9),
        Elem<int>(0, 1, 10),
        Elem<int>(2, 2, 11)
    };
    Mat<int> mat1(3, 3, cstVec1);
    mat1.PrintMat();
    std::cout << mat1.CalculatePercent() << "%" << std::endl;

    Elem<std::string>(1, 1, "Chanhui Zhang").PrintElem();

    system("pause");
    return 0;
}