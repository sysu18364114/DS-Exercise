
// 2020/3/25 //

#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#include <iostream>
#include <cstdlib>
#include <vector>

const int MaxSize = 10;
const int FoundFailed = -1;

template <typename T>
class SeqList
{
    private:
        T* elem;
        int len;

    public:
        SeqList();
        ~SeqList();

        bool CreateSeqList();
        bool CreateSeqList(std::vector<T> arr);
        bool GetElem(int pos, T& ele) const;
        std::vector<int> LocateELem(T ele) const;
        bool SeqListInsert(int pos, T ele);
        bool SeqListDelete(int pos, T& ele);
        void PrintSeqList() const;
};

template <typename T>
SeqList<T>::SeqList()
{
    this->elem = new T[MaxSize];
    this->len = MaxSize;
}

template <typename T>
SeqList<T>::~SeqList()
{
    delete[] this->elem;
    this->len = 0;
}

template <typename T>
bool SeqList<T>::CreateSeqList()
{
    std::cout << "The maximum size is: " << MaxSize << std::endl;

    int N = 0;
    std::cin >> N;
    if(N <= MaxSize)
    {
        for(int i = 0; i < N; i++)
        {
            std::cin >> elem[i];
        }
        this->len = N;

        return true;
    }
    else
    {
        std::cout << "Length longer than maximum size" << std::endl;
        return false;
    }
}

template <typename T>
bool SeqList<T>::CreateSeqList(std::vector<T> arr)
{
    int N = arr.size();
    if(N <= MaxSize)
    {
        for(int i = 0; i < N; i++)
        {
            elem[i] = arr[i];
        }
        this->len = N;

        return true;
    }
    else
    {
        std::cout << "Length longer than maximum size" << std::endl;
        return false;
    }
}

template <typename T>
bool SeqList<T>::GetElem(int pos, T& ele) const
{
    if(pos < 1 || pos > MaxSize)
    {
        std::cout << "Index out of range" << std::endl;
        return false;
    }
    
    ele = this->elem[pos - 1];

    return true;
}

template <typename T>
std::vector<int> SeqList<T>::LocateELem(T ele) const
{
    std::vector<int> res;
    for(int i = 0; i < this->len; i++)
    {
        if(this->elem[i] == ele)
        {
            res.push_back(i);
        }
    }

    return res;
}

template <typename T>
bool SeqList<T>::SeqListInsert(int pos, T ele)
{
    if(this->len == MaxSize)
    {
        std::cout << "List full" << std::endl;
        return false;
    }
    
    if(pos < 1 || pos > MaxSize + 1)
    {
        std::cout << "Index out of range" << std::endl;
        return false;
    }

    for(int i = this->len; i >= pos - 1; i--)
    {
        this->elem[i + 1] = this->elem[i];
    }
    this->elem[pos - 1] = ele;
    this->len++;

    return true;
}

template <typename T>
bool SeqList<T>::SeqListDelete(int pos, T& ele)
{
    if(pos < 1 || pos > MaxSize)
    {
        std::cout << "Index out of range" << std::endl;

        return false;
    }

    ele = this->elem[pos - 1];
    for(int i = pos - 1; i < this->len; i++)
    {
        this->elem[i] = this->elem[i + 1];
    }
    this->len--;

    return true;
}

template <typename T>
void SeqList<T>::PrintSeqList() const
{
    if(this->len == 0)
    {
        std::cout << "Empty" << std::endl;
    }
    else
    {
        for(int i = 0; i < this->len; i++)
        {
            std::cout << this->elem[i] << " ";
        }
        std::cout << std::endl;
    }
}

#endif