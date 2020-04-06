
// 2020/4/2 //

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

template <typename T>
struct BSNode
{
    public:
        T data_;
        int count_;
        BSNode<T>* left_;
        BSNode<T>* right_;

        explicit BSNode();
        explicit BSNode(const T& data);
        explicit BSNode(const BSNode<T>& elem);
        ~BSNode();
        void PrintBSNode() const;

    private:
        BSNode<T>& operator=(const BSNode<T>& elem);
};

template <typename T>
BSNode<T>::BSNode():
    data_(), count_(0), left_(nullptr), right_(nullptr) {}

template <typename T>
BSNode<T>::BSNode(const T& data):
    data_(data), count_(1), left_(nullptr), right_(nullptr) {}

template <typename T>
BSNode<T>::BSNode(const BSNode<T>& elem):
    data_(*elem), count_(1), left_(nullptr), right_(nullptr) {}

template <typename T>
BSNode<T>::~BSNode() {};

template <typename T>
void BSNode<T>::PrintBSNode() const
{
    std::cout << "<Data: " << this->data_ << ", Count: " << this->count_ << ">" << std::endl;
}

template <typename T>
class BSTree
{
    private:
        BSNode<T>* root_;
        int nodeNum_;

        void DestoryBSTree_(BSNode<T>* root);
        void InsertBSNode_(BSNode<T>*& root, const T& elem);
        bool DeleteBSNode_(BSNode<T>*& root, const T& elem);
        bool SearchBSNode_(const BSNode<T>* root, const T& elem) const;
        void PreOrderPrint_(const BSNode<T>* root) const;

    public:
        BSTree();
        BSTree(const std::vector<T>& elemVec);
        ~BSTree();
        void InsertBSNode(const T& elem);
        bool DeleteBSNode(const T& elem);
        bool SearchBSNode(const T& elem) const;
        void PreOrderPrint() const;
};

template <typename T>
void BSTree<T>::DestoryBSTree_(BSNode<T>* root)
{
    BSNode<T>* temp = root;
    if(temp == nullptr)
    {
        return ;
    }
    else
    {
        this->DestoryBSTree_(temp->left_);   
        this->DestoryBSTree_(temp->right_);
        delete temp;
        temp = nullptr;   
    }
}

template <typename T>
void BSTree<T>::InsertBSNode_(BSNode<T>*& root, const T& elem)
{
    BSNode<T>** temp = &root;
    if(*temp == nullptr)
    {
        BSNode<T>* node = new BSNode<T>(elem);
        node->data_ = elem;
        *temp = node;
    }
    else if((*temp)->data_ == elem)
    {
        (*temp)->count_++;
    }
    else if((*temp)->data_ > elem)
    {
        this->InsertBSNode_((*temp)->left_, elem);
    }
    else if((*temp)->data_ < elem)
    {
        this->InsertBSNode_((*temp)->right_, elem);
    }
}

template <typename T>
bool BSTree<T>::DeleteBSNode_(BSNode<T>*& root, const T& elem)
{
    BSNode<T>* target = root;
    BSNode<T>* parent = nullptr;
    if(root == nullptr)
    {
        return false;
    }
    while(target != nullptr)
    {
        if(target->data_ == elem)
        {
            break;
        }
        parent = target;
        if(target->data_ > elem)
        {
            target = target->left_;
        }
        else
        {
            target = target->right_;
        }
    }
    if(target == nullptr)
    {
        return false;
    }

    if(target->right_ != nullptr && target->left_ != nullptr)
    {
        BSNode<T>* prev = target;
        BSNode<T>* curr = target->left_;
        while(curr->right_ != nullptr)
        {
            prev = curr;
            curr = curr->right_;
        }
        target->data_ = curr->data_;
        if(prev != target)
        {
            prev->right_ = curr->left_;
        }
        else
        {
            prev->left_ = curr->left_;
        }
        delete curr;
    }
    else
    {
        BSNode<T>* curr = nullptr;
        if(target->right_ == nullptr)
        {
            curr = target;
            target = target->left_;
        }
        else if(target->left_ == nullptr)
        {
            curr = target;
            target = target->right_;
        }

        if(parent == nullptr)
        {
            root = target;
        }
        else if(curr == parent->left_)
        {
            parent->left_ = target;
        }
        else
        {
            parent->right_ = target;
        }
        delete curr;
    }

    this->nodeNum_--;
    return true;
}

template <typename T>
bool BSTree<T>::SearchBSNode_(const BSNode<T>* root, const T& elem) const
{
    bool tag = false;
    if(root == nullptr)
    {
        return false;
    }
    if(root->data_ == elem)
    {
        return true;
    }
    else if(root->data_ > elem)
    {
        tag = SearchBSNode_(root->left_, elem);
    }
    else if(root->data_ < elem)
    {
        tag = SearchBSNode_(root->right_, elem);
    }

    return tag;
}

template <typename T>
void BSTree<T>::PreOrderPrint_(const BSNode<T>* root) const
{
    const BSNode<T>* temp = root;
    if(temp == nullptr)
    {
        return ;
    }
    else
    {
        temp->PrintBSNode();
        this->PreOrderPrint_(temp->left_);
        this->PreOrderPrint_(temp->right_);
    }
}

template <typename T>
BSTree<T>::BSTree():
    root_(nullptr), nodeNum_(0) {}

template <typename T>
BSTree<T>::BSTree(const std::vector<T>& elemVec):
    nodeNum_(elemVec.size()), root_(nullptr)
{
    for(int i = 0; i < this->nodeNum_; i++)
    {
        this->InsertBSNode(elemVec[i]);
    }
}

template <typename T>
BSTree<T>::~BSTree()
{
    this->DestoryBSTree_(this->root_);
}

template <typename T>
void BSTree<T>::InsertBSNode(const T& elem)
{
    this->InsertBSNode_(this->root_, elem);
}

template <typename T>
bool BSTree<T>::DeleteBSNode(const T& elem)
{
    return this->DeleteBSNode_(this->root_, elem);
}

template <typename T>
bool BSTree<T>::SearchBSNode(const T& elem) const
{
    return this->SearchBSNode_(this->root_, elem);
}

template <typename T>
void BSTree<T>::PreOrderPrint() const
{
    if(this->root_ == nullptr)
    {
        std::cout << "NULL" << std::endl;
    }
    this->PreOrderPrint_(this->root_);
}