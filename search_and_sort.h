
// 2020/4/2 //

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

#include "binary_search_tree.h"
#include "link_hash_list.h"

typedef int INDEX;
typedef bool STATE;

const int NOT_FOUND = -1;

template <typename T>
class Search
{
    private:
        std::vector<T> testVec_;
        BSTree<T> testBSTree_;
        LHashList<T> testLHashList_;


        INDEX BinSearchRec_(const std::vector<T>& vec,
            int elem, int low, int high) const;
        void PrintVec_(const std::vector<T>& vec) const;

    public:
        explicit Search();
        explicit Search(const std::vector<T>& testVec);
        ~Search();
        std::vector<T> GetTestVec() const;
        INDEX SeqSearch(const T& elem) const; 
        INDEX BinSearchIte(const T& elem) const;
        INDEX BinSearchRec(const T& elem) const;
        STATE BSTreeSearch(const T& elem) const;
        STATE LHashListSearch(const T& elem) const;
        void PrintTestVec() const;
        void PrintTestBSTree() const;
        void PrintTestLHashList() const;
};

template <typename T>
INDEX Search<T>::BinSearchRec_(const std::vector<T>& vec, 
    int elem, int low, int high) const
{
    if(low > high)
    {
        return NOT_FOUND;
    }
    int mid = (low + high) / 2;
    if(elem == vec[mid])
    {
        return mid;
    }
    else if(elem < vec[mid])
    {
        return this->BinSearchRec_(vec, elem, low, high - 1);
    }
    else
    {
        return this->BinSearchRec_(vec, elem, low + 1, high);
    }
}

template <typename T>
void Search<T>::PrintVec_(const std::vector<T>& vec) const
{
    for(auto elem : vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


template <typename T>
Search<T>::Search():
    testVec_(), testBSTree_(), testLHashList_() {}

template <typename T>
Search<T>::Search(const std::vector<T>& testVec):
    testVec_(testVec), testBSTree_(testVec), testLHashList_(testVec) {}

template <typename T>
Search<T>::~Search() {}

template <typename T>
std::vector<T> Search<T>::GetTestVec() const
{
    return this->testVec_;
}

template <typename T>
INDEX Search<T>::SeqSearch(const T& elem) const
{
    int len = this->testVec_.size();
    for(int i = 0; i < len; i++)
    {
        if(elem == testVec_[i])
        {
            return i;
        }
    }

    return NOT_FOUND;
}

template <typename T>
INDEX Search<T>::BinSearchIte(const T& elem) const
{
    std::vector<T> copy(this->testVec_);
    std::sort(copy.begin(), copy.end());
    std::cout << "Sorted vector: ";
    this->PrintVec_(copy);

    int low = 0, high = copy.size() - 1, mid = 0;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(copy[mid] == elem)
        {
            return mid;
        }
        else if(copy[mid] < elem)
        {
            low = mid + 1;
        }
        else if(copy[mid] > elem)
        {
            high = mid - 1;
        }
    }

    return NOT_FOUND;
}

template <typename T>
INDEX Search<T>::BinSearchRec(const T& elem) const
{
    std::vector<T> copy(this->testVec_);
    std::sort(copy.begin(), copy.end());
    std::cout << "Sorted vector: ";
    this->PrintVec_(copy);
    return this->BinSearchRec_(copy, elem, 0, copy.size() - 1);
}

template <typename T>
STATE Search<T>::LHashListSearch(const T& elem) const
{
    return this->testLHashList_.SearchElem(elem);
}

template <typename T>
STATE Search<T>::BSTreeSearch(const T& elem) const
{
    return this->testBSTree_.SearchBSNode(elem);
}

template <typename T>
void Search<T>::PrintTestVec() const
{
    this->PrintVec_(this->testVec_);
}

template <typename T>
void Search<T>::PrintTestBSTree() const
{
    this->testBSTree_.PreOrderPrint();
}

template <typename T>
void Search<T>::PrintTestLHashList() const
{
    this->testLHashList_.PrintLHashList();
}

template <typename T>
class Sort
{
    private:
        std::vector<T> testVec_;

        void InsertEmptyElem_(std::vector<T>& vec);
        void EraseEmptyElem_(std::vector<T>& vec);
        void ShellInsert_(std::vector<T>& vec, int delta);
        int Partition_(std::vector<T>& vec, int low, int high);
        void QuickSort_(std::vector<T>& vec, int low, int high);
        void PrintVec_(const std::vector<T>& vec) const;

    public:
        Sort();
        Sort(std::vector<T> testVec);
        ~Sort();
        std::vector<T> StraightInsertSort();
        std::vector<T> ShellInsertSort();
        std::vector<T> BubbleSort();
        std::vector<T> QuickSort();
        void PrintTestVec() const;
};

template <typename T>
void Sort<T>::InsertEmptyElem_(std::vector<T>& vec)
{
    T emptyElem = T();
    vec.insert(vec.begin(), emptyElem);
}

template <typename T>
void Sort<T>::EraseEmptyElem_(std::vector<T>& vec)
{
    vec.erase(vec.begin());
}

template <typename T>
void Sort<T>::ShellInsert_(std::vector<T>& vec, int delta)
{
    int len = vec.size() - 1, ind = 0;
    for(int i = delta + 1; i <= len; i++) // "vec[0]" is a support space
    {
        if(vec[i] < vec[i - delta])
        {
            vec[0] = vec[i];
            for(ind = i - delta; ind > 0 && vec[ind] > vec[0]; ind -= delta)
            {
                vec[ind + delta] = vec[ind];
            }
            vec[ind + delta] = vec[0];
        }
    }
}

template <typename T>
int Sort<T>::Partition_(std::vector<T>& vec, int low, int high)
{
    int left = low, right = high, pivot = vec[low];
    while(left < right)
    {
        while(left < right && vec[right] > pivot)
        {
            right--;
        }
        while(left < right && vec[left] <= pivot)
        {
            left++;
        }
        if(left < right)
        {
            std::swap(vec[left++], vec[right--]);
        }
    }
    if(vec[left] > pivot)
    {
        std::swap(vec[left - 1], vec[low]);
        return left - 1;
    }
    else
    {
        std::swap(vec[left], vec[low]);
        return left;
    }
}

template <typename T>
void Sort<T>::QuickSort_(std::vector<T>& vec, int low, int high)
{
    int mid = 0;
    if(low >= high)
    {
        return ;
    }
    else
    {
        mid = this->Partition_(vec, low, high);
        this->QuickSort_(vec, low, mid - 1);
        this->QuickSort_(vec, mid + 1, high);
    }
}

template <typename T>
void Sort<T>::PrintVec_(const std::vector<T>& vec) const
{
    for(auto elem : vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template <typename T>
Sort<T>::Sort():
    testVec_() {}

template <typename T>
Sort<T>::Sort(std::vector<T> testVec):
    testVec_(testVec) {}

template <typename T>
Sort<T>::~Sort() {}

template <typename T>
std::vector<T> Sort<T>::StraightInsertSort()
{
    int len = this->testVec_.size();
    std::vector<T> supVec(this->testVec_);
    this->InsertEmptyElem_(supVec);
    
    for(int i = 2; i <= len; i++)
    {
        if(supVec[i] < supVec[i - 1])
        {
            supVec[0] = supVec[i];
            supVec[i] = supVec[i - 1];
            int j = 0;
            for(j = i - 2; supVec[j] > supVec[0]; j--)
            {
                supVec[j + 1] = supVec[j];
            }
            supVec[j + 1] = supVec[0];
        }
    }

    this->EraseEmptyElem_(supVec);
    return supVec;
}

template <typename T>
std::vector<T> Sort<T>::ShellInsertSort()
{
    int len = this->testVec_.size() / 2;
    std::vector<T> supVec(this->testVec_);
    this->InsertEmptyElem_(supVec);

    while(len > 0)
    {
        this->ShellInsert_(supVec, len);
        len /= 2;
    }

    this->EraseEmptyElem_(supVec);
    return supVec;
}

template <typename T>
std::vector<T> Sort<T>::BubbleSort()
{
    int len = this->testVec_.size();
    std::vector<T> supVec(this->testVec_);
    for(int i = 0; i < len - 1; i++)
    {
        int flag = false;
        for(int j = 0; j < len - i - 1; j++)
        {
            if(supVec[j] > supVec[j + 1])
            {
                std::swap(supVec[j], supVec[j + 1]);
                flag = true;
            }
        }
        if(flag == false)
        {
            break;
        }
    }

    return supVec;
}

template <typename T>
std::vector<T> Sort<T>::QuickSort()
{
    int len = this->testVec_.size();
    std::vector<T> supVec(this->testVec_);

    this->QuickSort_(supVec, 0, len - 1);

    return supVec;
}

template <typename T>
void Sort<T>::PrintTestVec() const
{
    this->PrintVec_(this->testVec_);
}