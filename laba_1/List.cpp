#include "List.h"

List::List() {
    head = nullptr;
}

List::~List() {
    Clear();
    fmt::print("\nВызван деструктор!!!\n");
}

void List::PushFront(int data) {
    head = new Node(data, head);
}

void List::PopFront() {
    if (head == nullptr) return;

    Node* toDelete = head;

    head = head->pNext;

    delete toDelete;
}

void List::Clear() {
    while (head) {
        PopFront();
    }
}

void List::Print() {
    Node* current = head;

    while (current != nullptr) {
        fmt::print("{} -> ", current->data);
        current = current->pNext;
    }
    fmt::print("NULL\n");
}

bool List::isExist() {
    return head;
}

void List::DeleteAllEntry(int value) {
    Node* current = head->pNext;
    Node* prev = head;
    Node* toDelete;

    while (current != nullptr) {
        if (current->data == value) {
            toDelete = current;
            prev->pNext = current->pNext;
            current = current->pNext;

            delete toDelete;
        }
        else {
            prev = current;
            current = current->pNext;
        }
    }

    if (head->data == value) PopFront();
}

void List::DeleteAllEntryPrev(int value) {
    Node* current = head->pNext;
    Node* prev = head;
    Node* toDelete;

    while (current->pNext != nullptr) {
        if (current->pNext->data == value) {
            toDelete = current;
            prev->pNext = current->pNext;
            current = current->pNext;

            delete toDelete;
        }
        else {
            prev = current;
            current = current->pNext;
        }
    }

    if (head->pNext->data == value) {
        toDelete = head;
        head = head->pNext;

        delete toDelete;
    }
}

int List::Find(int value) {
    Node* current = head;
    int index {};

    while (current != nullptr) {
        if (current->data == value) {
            return index;
        }

        current = current->pNext;
        ++index;
    }

    return -1;
}

List* List::Union(List& secondList) {
    bool found[100] {false};

    List* newList = new List();
    newList->head = new Node(head->data);

    Node* current = head->pNext;
    Node* newListCurrent = newList->head;

    while (current != nullptr) {
        if (!found[current->data]) {
            found[current->data] = true;
            newListCurrent->pNext = new Node(current->data);
            newListCurrent = newListCurrent->pNext;
        }
        current = current->pNext;
    }

    current = secondList.head;

    while (current != nullptr) {
        if (!found[current->data]) {
            found[current->data] = true;
            newListCurrent->pNext = new Node(current->data);
            newListCurrent = newListCurrent->pNext;
        }
        current = current->pNext;
    }

    return newList;
}
