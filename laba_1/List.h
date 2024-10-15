#include <fmt/color.h>
#ifndef LINKED_LIST_LIST_H
#define LINKED_LIST_LIST_H


class List {
public:
    List();
    ~List();

    ///\n Добавление элемента в начало списка
    void PushFront(int data);
    ///\n Удаление элемента из начала списка
    void PopFront();
    ///\n Очистка списка
    void Clear();
    void Print();
    bool isExist();
    ///\n Удаление всех вхождений заданного элемента
    void DeleteAllEntry(int value);
    void DeleteAllEntryPrev(int value);
    int Find(int value);
    List* Union(List& secondList);

private:
    struct Node {
    public:
        Node* pNext;
        int data;

        Node(int data = {}, Node* pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };

    Node* head;
};


#endif //LINKED_LIST_LIST_H
