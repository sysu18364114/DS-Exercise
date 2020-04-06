
// 2020/3/31 //

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>

const int intNullTag = -1;
const int REC = 0;
const int ITE = 0;

template <typename T>
struct BNode
{
    public:
        T data_;
        BNode<T>* left_;
        BNode<T>* right_;

        explicit BNode();
        explicit BNode(T data);
        ~BNode();
        void PrintBNode() const;

    private:
        BNode(const BNode<T>& elem);
        BNode<T>& operator=(const BNode<T>& elem);
};

template <typename T>
BNode<T>::BNode():
    data_(), left_(nullptr), right_(nullptr) {}

template <typename T>
BNode<T>::BNode(T data):
    data_(data), left_(nullptr), right_(nullptr) {}

template <typename T>
BNode<T>::~BNode() {};

template <typename T>
void BNode<T>::PrintBNode() const
{
    std::cout << this->data_ << std::endl;
}

template <typename T>
class BTree
{
    private:
        int nodeNum_;
        BNode<T>* root_;

        BNode<T>* CreateBTreeRec(const std::vector<T>& elemVec, 
            const T& nullTag, int& ind);
        void DestoryTreeRec(BNode<T>* root);

        void PrevOrderPrintRec(const BNode<T>* root) const;
        void PrevOrderPrintIte(const BNode<T>* root) const;
        void InOrderPrintRec(const BNode<T>* root) const;
        void InOrderPrintIte(const BNode<T>* root) const;
        void PostOrderPrintRec(const BNode<T>* root) const;
        void PostOrderPrintIte(const BNode<T>* root) const;
        void LevelOrderPrintIte(const BNode<T>* root) const;
        void VisitBNode(const BNode<T>* node) const;

        int FindKLevelRec(const BNode<T>* root, int kLevel) const;

    public:
        explicit BTree();
        explicit BTree(const std::vector<T>& elemVec, const T& nullTag);
        ~BTree();

        void PrevOrderPrint(int mode = 0) const;
        void InOrderPrint(int mode = 0) const;
        void PostOrderPrint(int mode = 0) const;
        void LevelOrderPrint() const;

        int FindKLevel(int kLevel) const;
};

template <typename T>
BNode<T>* BTree<T>::CreateBTreeRec(const std::vector<T>& elemVec, 
    const T& nullTag, int& ind)
{
    BNode<T>* root = nullptr;
    if(elemVec[ind] != nullTag && ind < this->nodeNum_)
    {
        root = new BNode<T>(elemVec[ind]);
        root->left_ = this->CreateBTreeRec(elemVec, nullTag, ++ind);
        root->right_ = this->CreateBTreeRec(elemVec, nullTag, ++ind);
    }

    return root;
}

template <typename T>
void BTree<T>::DestoryTreeRec(BNode<T>* root)
{
    BNode<T>* temp = root;
    if(temp == nullptr)
    {
        return ;
    }
    else
    {
        this->DestoryTreeRec(temp->left_);
        this->DestoryTreeRec(temp->right_);
        delete temp;
        temp = nullptr;
    }
}

template <typename T>
void BTree<T>::PrevOrderPrintRec(const BNode<T>* root) const
{
    const BNode<T>* temp = root;
    if(temp == nullptr)
    {
        return ;
    }
    else
    {
        this->VisitBNode(temp);
        this->PrevOrderPrintRec(temp->left_);   
        this->PrevOrderPrintRec(temp->right_);   
    }
}

template <typename T>
void BTree<T>::PrevOrderPrintIte(const BNode<T>* root) const
{
    std::stack<const BNode<T>*> S;
    const BNode<T>* curr = root;
    if(curr == nullptr)
    {
        return ;
    }
    while(curr != nullptr || !S.empty())
    {
        while(curr != nullptr)
        {
            S.push(curr);
            this->VisitBNode(curr);
            curr = curr->left_;
        }
        const BNode<T>* top = S.top();
        S.pop();
        curr = top->right_;
    }
}

template <typename T>
void BTree<T>::InOrderPrintRec(const BNode<T>* root) const
{
    const BNode<T>* temp = root;
    if(temp == nullptr)
    {
        return ;
    }
    else
    {
        this->InOrderPrintRec(temp->left_);
        this->VisitBNode(temp);
        this->InOrderPrintRec(temp->right_);
    }
}

template <typename T>
void BTree<T>::InOrderPrintIte(const BNode<T>* root) const
{
    std::stack<const BNode<T>*> S;
    const BNode<T>* curr = root;
    if(curr == nullptr)
    {
        return ;
    }
    while(curr != nullptr || !S.empty())
    {
        while(curr != nullptr)
        {
            S.push(curr);
            curr = curr->left_;
        }
        const BNode<T>* top = S.top();
        S.pop();
        this->VisitBNode(top);
        curr = top->right_;
    }
}

template <typename T>
void BTree<T>::PostOrderPrintRec(const BNode<T>* root) const
{
    const BNode<T>* temp = root;
    if(temp == nullptr)
    {
        return ;
    }
    else
    {
        this->PostOrderPrintRec(temp->left_);
        this->PostOrderPrintRec(temp->right_);
        this->VisitBNode(temp);
    }
}

template <typename T>
void BTree<T>::PostOrderPrintIte(const BNode<T>* root) const
{
    std::stack<const BNode<T>*> S;
    const BNode<T>* prev = nullptr;
    const BNode<T>* curr = root;
    while(curr != nullptr || !S.empty())
    {
        while(curr != nullptr)
        {
            S.push(curr);
            curr = curr->left_;
        }
        const BNode<T>* top = S.top();
        if(top->right_ == nullptr || prev == top->right_)
        {
            this->VisitBNode(top);
            prev = top;
            S.pop();
        }
        else
        {
            curr = top->right_;
        }
    }
}

template <typename T>
void BTree<T>::LevelOrderPrintIte(const BNode<T>* root) const
{
    const BNode<T>* temp = root;
    std::queue<const BNode<T>*> Q;
    Q.push(temp);
    while(!Q.empty())
    {
        const BNode<T>* top = Q.front();
        Q.pop();
        this->VisitBNode(top);
        if(top->left_ != nullptr)
        {
            Q.push(top->left_);
        }
        if(top->right_ != nullptr)
        {
            Q.push(top->right_);
        }
    }
}

template <typename T>
void BTree<T>::VisitBNode(const BNode<T>* node) const
{
    std::cout << node->data_ << " ";
}

template <typename T>
int BTree<T>::FindKLevelRec(const BNode<T>* root, int kLevel) const
{
    const BNode<T>* curr = root;
    if(curr == nullptr || kLevel <= 0)
    {
        return 0;
    }
    if(kLevel == 1)
    {
        return 1;
    }

    int leftNum = this->FindKLevelRec(curr->left_, kLevel - 1);
    int rightNum = this->FindKLevelRec(curr->right_, kLevel - 1);

    return leftNum + rightNum;
}

template <typename T>
BTree<T>::BTree():
    nodeNum_(0), root_(nullptr) {}

template <typename T>
BTree<T>::BTree(const std::vector<T>& elemVec, const T& nullTag):
    nodeNum_(elemVec.size())
{
    int ind = 0;
    this->root_ = this->CreateBTreeRec(elemVec, nullTag, ind);
}

template <typename T>
BTree<T>::~BTree()
{
    this->DestoryTreeRec(this->root_);
}

template <typename T>
void BTree<T>::PrevOrderPrint(int mode) const
{
    if(mode == 0)
    {
        this->PrevOrderPrintRec(this->root_);
    }
    else if(mode == 1)
    {
        this->PrevOrderPrintIte(this->root_);
    }
    std::cout << std::endl;
}

template <typename T>
void BTree<T>::InOrderPrint(int mode) const
{
    if(mode == 0)
    {
        this->InOrderPrintRec(this->root_);
    }
    else if(mode == 1)
    {
        this->InOrderPrintIte(this->root_);
    }
    std::cout << std::endl;
}

template <typename T>
void BTree<T>::PostOrderPrint(int mode) const
{
    if(mode == 0)
    {
        this->PostOrderPrintRec(this->root_);
    }
    else if(mode == 1)
    {
        this->PostOrderPrintIte(this->root_);
    }
    std::cout << std::endl;
}

template <typename T>
void BTree<T>::LevelOrderPrint() const
{
    this->LevelOrderPrintIte(this->root_);
    std::cout << std::endl;
}

template <typename T>
int BTree<T>::FindKLevel(int kLevel) const
{
    return this->FindKLevelRec(this->root_, kLevel);
}

#endif