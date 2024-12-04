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
    explicit Node(Key key = {}, int value = {});;

    // проверка является ли некоторый узел красным
    bool IsRed();
    // проверка является ли некоторый узел чёрным
    bool IsBlack();
    // покрасить узел в чёрный
    void PaintBlack();
    // покрасить узел в красный
    void PaintRed();
    // проверить является ли булева переменная чёрным цветом
    static bool IsColorBlack(bool color);

private:
    constexpr static bool RED = false;
    constexpr static bool BLACK = true;
};


#endif //LABA_2_NODE_H
