#ifndef AVL_TREE_AVLTREE_H
#define AVL_TREE_AVLTREE_H


#include <string>
#include <fmt/color.h>

class AvlTree {
public:
    AvlTree();
    ~AvlTree();

    /**
       *  @brief Inserts the key of int into the AvlTree.
       *  @param  key  Int value to be inserted.
       */
    void insert(int key);

    void erase(int key);

    void print();

    void clear();

    /// Прямой обход дерева
    std::string getPreOrderString();

    /// Обратный обход дерева
    std::string getPostOrderString();

    /// Симметричный обход дерева
    std::string getInOrderString();

private:
    std::string _ch_uhor = "\u2514\u2500";    // "└─"
    std::string _ch_dhor = "\u250C\u2500";    // "┌─"
    std::string _ch_ver = "\u2502 ";          // "│ "

    struct Node {
        int key;        // ключ узла
        int height;     // высота узла
        Node* left;     // указатель на левого потомка
        Node* right;    // указатель на правого потомка

        // конструктор узла
        Node(int k) {
            key = k;
            left = nullptr;
            right = nullptr;
            height = 0;
        };
    };

    Node* _root;

    // определение высоты некоторого узла
    int m_getHeight(Node* node);

    // определение фактора балансировки некоторого узла
    int m_getBalanceFactor(Node* node);

    // корректировка высоты некоторого узла
    void m_fixHeight(Node* node);

    // правый поворот вокруг некоторого узла
    Node* m_rotateRight(Node* node);

    // левый поворот вокруг некоторого узла
    Node* m_rotateLeft(Node* node);

    // балансировка некоторого узла
    Node* m_balance(Node* node);

    // вставка ключа key в дерево с корнем node
    Node* m_insert(Node* node, int key);

    // поиск узла с максимальным ключом в дереве node
    Node* m_findMax(Node* node);

    // удаление узла с максимальным ключом в дереве node
    Node* m_eraseMax(Node* node);

    // удаление ключа key из дерева node
    Node* m_erase(Node* node, int key);

    Node* m_clear(Node* node);

    void m_print(Node* node, const std::string& rpref = "",
                 const std::string& cpref = "", const std::string& lpref = "");

    void m_preOrder(const Node* node, std::string& result);

    void m_postOrder(const Node* node, std::string& result);

    void m_inOrder(const Node* node, std::string& result);

    // поиск узла с минимальным ключом в дереве node
    Node* m_findMin(Node* node);

    // удаление узла с минимальным ключом в дереве node
    Node* m_eraseMin(Node* node);

    // удаление ключа key из дерева node с заменой на минимальный справа
    Node* m_eraseWithMin(Node* node, int key);
};


#endif //AVL_TREE_AVLTREE_H
