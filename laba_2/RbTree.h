#ifndef LABA_2_RBTREE_H
#define LABA_2_RBTREE_H


#include <fmt/color.h>
#include <sstream>
#include <utility>
#include "ConsoleColors.h"
#include "Node.h"

class RbTree {
public:
    RbTree();
    ~RbTree();

    bool Insert(Key key, int value);
    bool Erase(const Key& key, const int& value);
    int Find(const Key& key);
    void Clear();
    void Print();
    bool IsExist();
    std::stringstream GetPostOrderTraversal();

private:
    constexpr static std::string CH_UP_HOR = "\u2514\u2500";       // "└─"
    constexpr static std::string CH_DOWN_HOR = "\u250C\u2500";     // "┌─"
    constexpr static std::string CH_VER = "\u2502 ";               // "│ "

    Node* _root;
    Node* _nil;

    /// Правый поворот вокруг некоторого узла
    void rotateRight(Node* node);

    /// Левый поворот вокруг некоторого узла
    void rotateLeft(Node* node);

    /// Найти узел по ключу
    Node* findNode(Node* node, const Key& key);

    /// Найти родителя узла по ключу
    Node* findParent(Node* node, const Key& key);

    /// Вставить узел
    bool insertNode(Node* newNode);

    /// Балансировать вставку
    void rebalanceInsert(Node* node);

    /// Нахождение узла с максимальным ключом в поддереве
    Node* findMax(Node* node);

    void replaceSubtree(Node* oldSubtree, Node* newSubtree);

    /// Удалить узел
    void eraseNode(Node* nodeToDelete);

    /// Балансировать удаление
    void rebalanceErase(Node* node);

    /// Обработать балансировку удаления справа
    Node* handleLeftRebalanceErase(Node* node);

    /// Обработать балансировку удаления слева
    Node* handleRightRebalanceErase(Node* node);

    /// Очистить дерево
    Node* clear(Node* node);

    /// Распечатать дерево
    void print(Node* node, const std::string& rightPref = "", const std::string& cPref = "", const std::string& leftPref = "");

    /// Записать обратный обход дерева в поток строки
    void postOrder(const Node* node, std::stringstream& result);
};


#endif //LABA_2_RBTREE_H
