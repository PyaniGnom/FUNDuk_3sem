#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#ifndef RB_TREE_RBTREE_H
#define RB_TREE_RBTREE_H


#include <fmt/color.h>
#include "Node.h"

class RbTree {
public:
    RbTree() {
        _nil = new Node();
        _nil->paintBlack();
        _root = _nil;
    }

    ~RbTree() {
        _root = clear(_root);
        delete _nil;
    }

    void Insert(int key, std::string value) {
        Node* newNode = new Node(key, std::move(value));
        newNode->left = _nil;
        newNode->right = _nil;
        insertNode(newNode);
    }

    void Clear() {
        _root = clear(_root);
    }

    void Print() {
        fmt::print("\n");
        print(_root);
    }

    /// Прямой обход дерева
    std::string GetPreOrderTraversalString() {
        std::string result {};
        preOrder(_root, result);
        return result;
    }

    /// Обратный обход дерева
    std::string GetPostOrderTraversalString() {
        std::string result {};
        postOrder(_root, result);
        return result;
    }

    /// Симметричный обход дерева
    std::string GetInOrderTraversalString() {
        std::string result {};
        inOrder(_root, result);
        return result;
    }

private:
    constexpr static std::string CH_UP_HOR = "\u2514\u2500";       // "└─"
    constexpr static std::string CH_DOWN_HOR = "\u250C\u2500";     // "┌─"
    constexpr static std::string CH_VER = "\u2502 ";               // "│ "
    constexpr static fmt::text_style CONSOLE_RED_COLOR = fmt::fg(fmt::color::red);
    constexpr static fmt::text_style CONSOLE_BLACK_COLOR = fmt::fg(fmt::color::dark_gray);

    Node* _root;
    Node* _nil;

    // правый поворот вокруг некоторого узла
    void rotateRight(Node* node) {
        Node* leftNode = node->left;
        Node* nodeParent = node->parent;

        node->left = leftNode->right;
        if (leftNode->right != _nil) {
            leftNode->right->parent = node;
        }

        leftNode->parent = node->parent;
        if (nodeParent == _nil) {
            _root = leftNode;
        }
        else if (nodeParent->right == node) {
            nodeParent->right = leftNode;
        }
        else {
            nodeParent->left = leftNode;
        }

        leftNode->right = node;
        node->parent = leftNode;
    }

    // левый поворот вокруг некоторого узла
    void rotateLeft(Node* node) {
        Node* rightNode = node->right;
        Node* nodeParent = node->parent;

        node->right = rightNode->left;
        if (rightNode->left != _nil) {
            rightNode->left->parent = node;
        }

        rightNode->parent = node->parent;
        if (nodeParent == _nil) {
            _root = rightNode;
        }
        else if (nodeParent->left == node) {
            nodeParent->left = rightNode;
        }
        else {
            nodeParent->right = rightNode;
        }

        rightNode->left = node;
        node->parent = rightNode;
    }

    Node* searchHelper(Node* node, Node* searchedNode) {
        if (node == _nil || searchedNode->key == node->key) {
            return node;
        }
        else if (searchedNode->key < node->key) {
            if (node->left == _nil) {
                return node;
            }

            return searchHelper(node->left, searchedNode);
        }
        else {
            if (node->right == _nil) {
                return node;
            }

            return searchHelper(node->right, searchedNode);
        }
    }

    void insertNode(Node* newNode) {
        Node* newNodeParent = searchHelper(_root, newNode);

        if (newNode->key == newNodeParent->key) {
            return;
        }

        if (newNodeParent == _nil) {
            _root = newNode;
        }
        else if (newNode->key < newNodeParent->key) {
            newNodeParent->left = newNode;
        }
        else {
            newNodeParent->right = newNode;
        }

        newNode->parent = newNodeParent;
        rebalanceInsert(newNode);
    }

    void rebalanceInsert(Node* node) {
        while (node != _root && node->parent->isRed()) {
            Node* grandpa = node->parent->parent;
            Node* uncle = grandpa->left == node->parent ? grandpa->right : grandpa->left;

            if (uncle->isRed()) {
                node->parent->paintBlack();
                uncle->paintBlack();
                grandpa->paintRed();
                node = grandpa;
            }
            else {
                if (node->parent == grandpa->left) {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->paintBlack();
                    grandpa->paintRed();

                    rotateRight(grandpa);
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->paintBlack();
                    grandpa->paintRed();
                    rotateLeft(grandpa);
                }
            }
        }
        _root->paintBlack();
    }

    Node* clear(Node* node) {
        if (node == _nil) return _nil;

        if (node->left) {
            node->left = clear(node->left);
        }
        if (node->right) {
            node->right = clear(node->right);
        }
        delete node;
        return _nil;
    }

    void print(Node* node, const std::string& rpref = "", const std::string& cpref = "", const std::string& lpref = "") {
        if (node == _nil) return;

        if (node->right != _nil) {
            print(node->right, rpref + "  ", rpref + CH_DOWN_HOR, rpref + CH_VER);
        }

        fmt::print(fmt::fg(fmt::color::aquamarine), "{}", cpref);
        if (node->isRed()) {
            fmt::print(CONSOLE_RED_COLOR, "R:{}\n", node->key);
        }
        else {
            fmt::print(CONSOLE_BLACK_COLOR, "B:{}\n", node->key);
        }

        if (node->left != _nil) {
            print(node->left, lpref + CH_VER, lpref + CH_UP_HOR, lpref + "  ");
        }
    }

    void preOrder(const Node* node, std::string& result) {
        if (node == _nil) return;

        result += std::to_string(node->key) + " ";
        preOrder(node->left, result);
        preOrder(node->right, result);
    }

    void postOrder(const Node* node, std::string& result) {
        if (node == _nil) return;

        postOrder(node->left, result);
        postOrder(node->right, result);
        result += std::to_string(node->key) + " ";
    }

    void inOrder(const Node* node, std::string& result) {
        if (node == _nil) return;

        inOrder(node->left, result);
        result += std::to_string(node->key) + " ";
        inOrder(node->right, result);
    }
};


#endif //RB_TREE_RBTREE_H
#pragma clang diagnostic pop
