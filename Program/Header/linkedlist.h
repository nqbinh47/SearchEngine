#pragma once
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include <iostream>
using namespace std;
template <typename T>
struct Node
{
    T data;
    Node *next;
    Node<T>(T data = T{"null", 0.0}, Node<T> *next = nullptr) : data(data), next(next) {}
    ~Node()
    {
        if (next)
            delete[] next;
    }
};
template <typename T>
struct List
{
    Node<T> *head, *tail;
    int size;
    List() : head(new Node<T>), tail(new Node<T>), size(0) {}
    bool CheckEmpty();
    int Size();
    Node<T> *FindI(int pos);
    Node<T> *FindData(T value);
    Node<T> *FindHead();
    Node<T> *FindTail();
    Node<T> *AddHead(T value);
    Node<T> *AddTail(T value);
    Node<T> *AddAfrer(int pos, T value);
    void RemoveHead();
    void RemoveTail();
    void Remove(int pos);
    void Clear();
};
template <typename T>
bool List<T>::CheckEmpty()
{
    return (head->next == nullptr);
}
template <typename T>
int List<T>::Size()
{
    return size;
}
template <typename T>
Node<T> *List<T>::FindI(int pos)
{
    int id = 0;
    Node<T> *cursor = head->next;
    while (cursor != nullptr && id < pos)
    {
        id++;
        cursor = cursor->next;
    }
    return cursor;
}
template <typename T>
Node<T> *List<T>::FindData(T value)
{
    Node<T> *cursor = head->next;
    while (cursor != nullptr && cursor->data != value)
    {
        cursor = cursor->next;
    }
    return cursor;
}
template <typename T>
Node<T> *List<T>::FindHead()
{
    return head->next;
}
template <typename T>
Node<T> *List<T>::FindTail()
{
    Node<T> *cursor = head;
    while (cursor->next != nullptr)
    {
        cursor = cursor->next;
    }
    return cursor;
}
template <typename T>
Node<T> *List<T>::AddHead(T value)
{
    size++;
    Node<T> *new_node = new Node<T>(value);
    if (CheckEmpty())
    {
        tail = new_node;
    }
    new_node->next = head->next;
    head->next = new_node;
    return new_node;
}
template <typename T>
Node<T> *List<T>::AddTail(T value)
{
    size++;
    if (CheckEmpty())
    {
        return AddHead(value);
    }
    Node<T> *new_node = new Node<T>(value);
    Node<T> *cursor = FindTail();
    cursor->next = new_node;
    tail = new_node;
    return new_node;
}
template <typename T>
Node<T> *List<T>::AddAfrer(int pos, T value)
{
    if (pos < 0)
    {
        return AddHead(value);
    }
    Node<T> *cursor = FindI(pos);
    if (cursor && cursor->next == nullptr)
    {
        return AddTail(value);
    }
    if (cursor)
    {
        Node<T> *new_node = new Node<T>(value);
        new_node->next = cursor->next;
        cursor->next = new_node;
        return new_node;
    }
    return 0;
}
template <typename T>
void List<T>::RemoveHead()
{
    if (CheckEmpty())
        return;
    size--;
    head->next = (head->next)->next;
    if (CheckEmpty())
        tail = nullptr;
    return;
}
template <typename T>
void List<T>::RemoveTail()
{
    if (CheckEmpty())
        return;
    size--;
    Node<T> *prev = head;
    for (Node<T> *cursor = head; cursor->next != nullptr; cursor = cursor->next)
        prev = cursor;
    prev->next = nullptr;
    tail = prev;
    if (CheckEmpty())
        tail = nullptr;
    return;
}
template <typename T>
void List<T>::Remove(int pos)
{
    if (CheckEmpty())
        return;
    if (pos <= 0)
    {
        RemoveHead();
        return;
    }
    Node<T> *cursor = FindI(pos - 1);
    if (cursor && cursor->next)
    {
        if ((cursor->next)->next == nullptr)
        {
            RemoveTail();
            return;
        }
        cursor->next = (cursor->next)->next;
        return;
    }
    return;
}
template <typename T>
List<T> MergeTwoList(List<T> &li_1, List<T> &li_2)
{
    //COPY_LIST_1
    List<T> li_3;
    for (Node<T> *cursor = li_1.head->next; cursor != nullptr; cursor = cursor->next)
        li_3.AddTail(cursor->data);
    //LINK_LIST_2
    li_3.tail->next = li_2.head->next;
    return li_3;
}
template <typename T>
void List<T>::Clear()
{
    while (!CheckEmpty())
        RemoveHead();
    return;
}
template <typename T>
void Print(List<T> &li)
{
    for (Node<T> *cursor = li.head->next; cursor != nullptr; cursor = cursor->next)
        std::cout << cursor->data << ' ';
    std::cout << '\n';
}
#endif // LINKEDLIST_H_INCLUDED
