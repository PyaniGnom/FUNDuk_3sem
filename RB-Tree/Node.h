#ifndef RB_TREE_NODE_H
#define RB_TREE_NODE_H


#include <string>

class Node {
public:
    int key;                // ключ узла
    std::string value;      // значения узла
    bool color;             // цвет узла
    Node* parent;           // указатель на родителя
    Node* left;             // указатель на левого потомка
    Node* right;            // указатель на правого потомка

    // конструктор узла
    explicit Node(int key = {}, std::string value = {}) {
        this->key = key;
        this->value = std::move(value);
        this->color = RED;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    };

    // проверка является ли некоторый узел красным
    bool isRed() {
        return this->color == RED;
    }

    void paintBlack() {
        this->color = BLACK;
    }

    void paintRed() {
        this->color = RED;
    }

private:
    constexpr static bool RED = false;
    constexpr static bool BLACK = true;
};


#endif //RB_TREE_NODE_H
