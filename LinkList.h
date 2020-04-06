
// 2020/3/26 //

#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
#include <cstdlib>
#include <vector>

template <typename T>
struct Node
{
    T data;
    Node<T>* next;

    Node();
    Node(T data);
    ~Node();
};

template <typename T>
Node<T>::Node():
    next(nullptr) {}

template <typename T>
Node<T>::Node(T data):
    data(data), next(nullptr) {}

template <typename T>
Node<T>::~Node() {}

template <typename T>
class LinkList
{
    private:
        Node<T>* head;
        int len;

    public:
        LinkList();
        ~LinkList();

        void CreateList(const std::vector<T>& vec);
        void CreateList();
        bool LocateElem(T elem) const;
        bool ListInsert(int pos, T elem);
        bool ListDelete(int pos);
        void PrintLinkList() const;

        void Merge(LinkList& L);
        void Reverse();
        T MiddleElem() const;
};

template <typename T>
LinkList<T>::LinkList():
    len(0)
{
    this->head = new Node<T>();
    this->head->data = -1;
    this->head->next = nullptr;
}

template <typename T>
LinkList<T>::~LinkList()
{
    Node<T>* curr = this->head;
    while(curr != nullptr)
    {
        Node<T>* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

template <typename T>
void LinkList<T>::CreateList(const std::vector<T>& vec)
{
    int size = vec.size();
    this->len = size;
    Node<T>* curr = this->head;
    for(int i = 0; i < size; i++) // tail insert
    {
        Node<T>* node = new Node<T>(vec[i]);
        curr->next = node;
        curr = curr->next;
    }
}

template <typename T>
void LinkList<T>::CreateList()
{
    int size = 0, ind = 0;
    std::cout << "Please enter the size of linked list: ";
    std::cin >> size;
    this->len = size;
    while(size--) // head insert
    {
        Node<T>* node = new Node<T>;
        std::cin >> node->data;
        node->next = this->head->next;
        this->head->next = node;
    }
}

template <typename T>
bool LinkList<T>::LocateElem(T elem) const
{
    Node<T>* curr = this->head->next;
    while(curr != nullptr)
    {
        if(curr->data == elem)
        {
            return true;
        }
        curr = curr->next;
    }
    
    return false;
}

template <typename T>
bool LinkList<T>::ListInsert(int pos, T elem)
{
    int ind = 1;
    Node<T>* curr = this->head;
    while(curr != nullptr && ind < pos)
    {
        ind++;
        curr = curr->next;
    }
    if(curr == nullptr)
    {
        std::cout << "Position error" << std::endl;
        return false;
    }
    else
    {
        Node<T>* node = new Node<T>;
        node->data = elem;
        node->next = curr->next;
        curr->next = node;
        this->len++;   
        return true;
    }
}

template <typename T>
bool LinkList<T>::ListDelete(int pos)
{
    int ind = 1;
    Node<T>* curr = this->head;
    while(curr != nullptr && ind < pos)
    {
        ind++;
        curr = curr->next;
    }
    if(curr == nullptr || curr->next == nullptr)
    {
        return false;
    }
    else
    {
        Node<T>* temp = curr->next;
        curr->next = curr->next->next;
        this->len--;
        delete temp;
        return true;
    }
}

template <typename T>
void LinkList<T>::PrintLinkList() const
{
    Node<T>* curr = this->head->next;
    while(curr != nullptr)
    {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

template <typename T>
void LinkList<T>::Merge(LinkList& L)
{
    Node<T>* dummy = new Node<T>;
    dummy->data = -1;
    dummy->next = nullptr;

    // default sorted linked list
    Node<T>* curr1 = L.head->next;
    Node<T>* curr2 = this->head->next;
    Node<T>* track = dummy;
    while(curr1 != nullptr && curr2 != nullptr)
    {
        if(curr1->data <= curr2->data)
        {
            track->next = curr1;
            curr1 = curr1->next;
            track = track->next;
        }
        else if(curr1->data > curr2->data)
        {
            track->next = curr2;
            curr2 = curr2->next;
            track = track->next;
        }
    }
    if(curr1 == nullptr)
    {
        track->next = curr2;
    }
    else if(curr2 == nullptr)
    {
        track->next = curr1;
    }
    
    L.head->next = nullptr;
    this->head = dummy;
    this->len += L.len;
}

template <typename T>
void LinkList<T>::Reverse()
{
    Node<T>* curr = this->head->next;
    this->head->next = nullptr;
    while(curr != nullptr)
    {
        Node<T>* temp = curr->next;
        curr->next = this->head->next;
        this->head->next = curr;
        curr = temp;
    }
}

template <typename T>
T LinkList<T>::MiddleElem() const
{
    Node<T>* fast = this->head;
    Node<T>* slow = this->head;
    while(fast != nullptr && fast->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    
    return slow->data;
}

#endif