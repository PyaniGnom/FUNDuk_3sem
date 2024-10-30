#ifndef LABA_2_NODE_H
#define LABA_2_NODE_H


#include <utility>
#include "Key.h"

constexpr static bool RED = false;
constexpr static bool BLACK = true;

struct Node {
    Key key;            // ключ узла
    int value;          // значения узла
    bool color;         // цвет узла
    Node* left;         // указатель на левого потомка
    Node* right;        // указатель на правого потомка

    // конструктор узла
    explicit Node(Key key = {}, int value = {}) {
        this->key = std::move(key);
        this->value = value;
        this->color = RED;
        this->left = nullptr;
        this->right = nullptr;
    };
};


#endif //LABA_2_NODE_H
