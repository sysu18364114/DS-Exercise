
// 2020/4/4 //

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>

const int lHashSize = 10;

template <typename T>
struct LNode
{
    T data_;
    LNode<T>* next_;

    LNode();
    LNode(T data);
    ~LNode();
    void PrintLNode() const;
};

template <typename T>
LNode<T>::LNode():
    data_(), next_(nullptr) {}

template <typename T>
LNode<T>::LNode(T data):
    data_(data), next_(nullptr) {}

template <typename T>
LNode<T>::~LNode() {}

template <typename T>
void LNode<T>::PrintLNode() const
{
    std::cout << "(" << this->data_ << ") ";
}

template <typename T>
struct Vertex
{
    bool state_; // "false": empty, "true": non-empty
    LNode<T>* first_;

    Vertex();
    ~Vertex();
};

template <typename T>
Vertex<T>::Vertex():
    state_(false), first_(nullptr) {}

template <typename T>
Vertex<T>::~Vertex() {}

template <typename T>
class LHashList
{
    private:
        std::vector<Vertex<T> > vexVec_;
        int elemNum_;

    public:
        LHashList();
        LHashList(const std::vector<T>& vec);
        ~LHashList();
        int HashFunc(const T& elem) const;
        bool SearchElem(const T& elem) const;
        void PrintLHashList() const;
};

template <typename T>
LHashList<T>::LHashList():
    vexVec_(), elemNum_(0) {}

template <typename T>
LHashList<T>::LHashList(const std::vector<T>& vec):
    elemNum_(vec.size())
{
    vexVec_.resize(lHashSize);
    for(int i = 0; i < this->elemNum_; i++)
    {
        std::cout << vec[i] << std::endl;
        int ind = this->HashFunc(vec[i]);
        LNode<T>* node = new LNode<T>(vec[i]);
        if(this->vexVec_[ind].state_ == false)
        {
            this->vexVec_[ind].first_ = node;
            this->vexVec_[ind].state_ = true;
        }
        else
        {
            node->next_ = this->vexVec_[ind].first_;
            this->vexVec_[ind].first_ = node;
        }
    }
}

template <typename T>
LHashList<T>::~LHashList()
{
    for(int i = 0; i < lHashSize; i++)
    {
        if(this->vexVec_[i].state_ == true)
        {
            LNode<T>* curr = this->vexVec_[i].first_;
            while(curr != nullptr)
            {
                LNode<T>* temp = curr;
                curr = curr->next_;
                delete temp;
            }
            this->vexVec_[i].first_ = nullptr;
        }
    }
}

template <typename T>
int LHashList<T>::HashFunc(const T& elem) const
{
    return static_cast<int>(elem) % lHashSize;
}

template <typename T>
bool LHashList<T>::SearchElem(const T& elem) const
{
    int ind = this->HashFunc(elem);
    LNode<T>* curr = this->vexVec_[ind].first_;
    while(curr != nullptr)
    {
        if(curr->data_ == elem)
        {
            return true;
        }
        curr = curr->next_;
    }
    return false;
}

template <typename T>
void LHashList<T>::PrintLHashList() const
{
    for(int i = 0; i < lHashSize; i++)
    {
        if(this->vexVec_[i].state_ == true)
        {
            std::cout << "Vertex <" << i + 1 << ">: ";
            LNode<T>* curr = this->vexVec_[i].first_;
            while(curr != nullptr)
            {
                curr->PrintLNode();
                curr = curr->next_;
            }
            std::cout << std::endl;
        }
    }
}