#ifndef LABA_2_NODE_H
#define LABA_2_NODE_H


#include <utility>
#include "Key.h"

class Node {
public:
    Key key;                // ключ узла
    int value;              // значения узла
    bool color;             // цвет узла
    Node* parent;           // указатель на родителя
    Node* left;             // указатель на левого потомка
    Node* right;            // указатель на правого потомка

    // конструктор узла
    explicit Node(Key key = {}, int value = {}) {
        this->key = std::move(key);
        this->value = value;
        this->color = RED;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    };

    // проверка является ли некоторый узел красным
    bool IsRed() {
        return this->color == RED;
    }

    bool IsBlack() {
        return this->color == BLACK;
    }

    void PaintBlack() {
        this->color = BLACK;
    }

    void PaintRed() {
        this->color = RED;
    }

    static bool IsColorBlack(bool color) {
        return color == BLACK;
    }

private:
    constexpr static bool RED = false;
    constexpr static bool BLACK = true;
};


#endif //LABA_2_NODE_H
