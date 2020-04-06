
// 2020/3/31 //

#ifndef TRIPE_MATRIX_H
#define TRIPE_MATRIX_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

template <typename T>
struct Elem
{
    // items
    int row;
    int col;
    T data;

    // functions
    explicit Elem();
    explicit Elem(int row, int col, T data);
    ~Elem();
    void PrintElem() const;
};

template <typename T>
Elem<T>::Elem():
    row(-1), col(-1), data() {}

template <typename T>
Elem<T>::Elem(int row, int col, T data):
    row(row), col(col), data(data) {}

template <typename T>
Elem<T>::~Elem() {}

template <typename T>
void Elem<T>::PrintElem() const
{
    std::cout << this->row << " " << this->col 
        << " " << this->data << std::endl;
}

template <typename T>
class Mat
{
    private:
        int matOrder;
        int elemNum;
        std::vector<Elem<T> > elemVec;

    public:
        explicit Mat();
        explicit Mat(int matOrder, int elemNum, const std::vector<Elem<T> >& elemVec);
        ~Mat();
        void PrintMat() const;
        double CalculatePercent() const;
};

template <typename T>
Mat<T>::Mat()
{
    std::cout << "Please enter the order of matrix: ";
    std::cin >> this->matOrder;
    if(this->matOrder <= 0)
    {
        std::cout << "Order exists error!" << std::endl;
        system("pause");
        std::abort();
    }
    std::cout << "Please enter the number of non-zero element: ";
    std::cin >> this->elemNum;
    std::cout << "Please enter the message of each element: " << std::endl;
    for(int i = 0; i < this->elemNum; i++)
    {
        Elem<T> temp;
        std::cin >> temp.row >> temp.col >> temp.data;
        this->elemVec.push_back(temp);
    }
}

template <typename T>
Mat<T>::Mat(int matOrder, int elemNum, const std::vector<Elem<T> >& elemVec):
    matOrder(matOrder), elemNum(elemNum), elemVec(elemVec) {}

template <typename T>
Mat<T>::~Mat() {}

template <typename T>
void Mat<T>::PrintMat() const
{
    T init = T();
    std::vector<T> initVec(this->matOrder, init);
    std::vector<std::vector<T> > outputMat(this->matOrder, initVec);
    for(int i = 0; i < this->elemNum; i++)
    {
        outputMat[this->elemVec[i].row][this->elemVec[i].col] = this->elemVec[i].data;
    }

    for(auto vec : outputMat)
    {
        for(auto elem : vec)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
double Mat<T>::CalculatePercent() const
{
    return 100 * (double(this->elemNum) / (this->matOrder * this->matOrder));
}

#endif