#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#ifndef LABA_2_RBTREE_H
#define LABA_2_RBTREE_H


#include <fmt/color.h>
#include <utility>
#include "Node.h"

class RbTree {
public:
    RbTree() {
        _nil = new Node({}, {});
        _nil->color = BLACK;
        _root = _nil;
    }

    ~RbTree() {
        _root = clear(_root);
        delete _nil;
    }

    void Insert(Key key, int value) {
        Node* newNode = new Node(std::move(key), value);
        newNode->left = _nil;
        newNode->right = _nil;
        _root = insertNode(_root, newNode);
        _root->color = BLACK;
    }

    void Erase(const Key& key) {
        _root = eraseNode(_root, key);
        _root->color = BLACK;
    }

    int Find(const Key& key) {
        Node* node = searchNode(_root, key);
        if (node == _nil) return {};
        return node->value;
    }

    void Clear() {
        _root = clear(_root);
    }



private:
    constexpr static std::string CH_UP_HOR = "\u2514\u2500";       // "└─"
    constexpr static std::string CH_DOWN_HOR = "\u250C\u2500";     // "┌─"
    constexpr static std::string CH_VER = "\u2502 ";               // "│ "
    constexpr static fmt::text_style CONSOLE_RED_COLOR = fmt::fg(fmt::color::red);
    constexpr static fmt::text_style CONSOLE_BLACK_COLOR = fmt::fg(fmt::color::dark_gray);

    Node* _root;
    Node* _nil;

    static Node* rotateRight(Node* node) {
        Node* leftNode = node->left;

        node->left = leftNode->right;
        leftNode->right = node;

        leftNode->color = node->color;
        node->color = RED;

        return leftNode;
    }

    static Node* rotateLeft(Node* node) {
        Node* rightNode = node->right;

        node->right = rightNode->left;
        rightNode->left = node;

        rightNode->color = node->color;
        node->color = RED;

        return rightNode;
    }

    static bool isRed(Node* node) {
        return node->color == RED;
    }

    void flipColors(Node* node) {
        node->color = !node->color;
        if (node->left != _nil) node->left->color = !node->left->color;
        if (node->right != _nil) node->right->color = !node->right->color;
    }

    Node* fixUp(Node* node) {
        if (isRed(node->right) && !isRed(node->left)) {
            node = rotateLeft(node);
        }
        if (isRed(node->left) && isRed(node->left->left)) {
            node = rotateRight(node);
        }
        if (isRed(node->left) && isRed(node->right)) {
            flipColors(node);
        }
        return node;
    }

    Node* insertNode(Node* node, Node* newNode) {
        if (node == _nil) return newNode;

        if (newNode->key < node->key) {
            node->left = insertNode(node->left, newNode);
        }
        else if (newNode->key > node->key) {
            node->right = insertNode(node->right, newNode);
        }
        else {
            return node;
        }

        return fixUp(node);
    }

    Node* moveRedLeft(Node* node) {
        flipColors(node);
        if (isRed(node->right->left)) {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
            flipColors(node);
        }
        return node;
    }

    Node* moveRedRight(Node* node) {
        flipColors(node);
        if (isRed(node->left->left)) {
            node = rotateRight(node);
            flipColors(node);
        }
        return node;
    }

    Node* findMin(Node* node) {
        return node->left != _nil ? findMin(node->left) : node;
    }

    Node* eraseMin(Node* node) {
        if (node->left == _nil) return _nil;

        if (!isRed(node->left) && !isRed(node->left->left)) {
            node = moveRedLeft(node);
        }
        node->left = eraseMin(node->left);

        return fixUp(node);
    }

    Node* eraseNode(Node* node, const Key& key) {
        if (node == _nil) return _nil;

        if (key < node->key) {
            if (node->left != _nil && !isRed(node->left) && !isRed(node->left->left)) {
                node = moveRedLeft(node);
            }
            node->left = eraseNode(node->left, key);
        }
        else {
            if (isRed(node->left)) {
                node = rotateRight(node);
            }
            if (key == node->key && node->right == _nil) {
                delete node;
                return _nil;
            }
            if (node->right != _nil && !isRed(node->right) && !isRed(node->right->left)) {
                node = moveRedRight(node);
            }
            if (key == node->key) {
                Node* min = findMin(node->right);
                min->right = eraseMin(node->right);
                min->left = node->left;
                min->color = node->color;

                delete node;

                return fixUp(min);
            }
            else {
                node->right = eraseNode(node->right, key);
            }
        }

        return fixUp(node);
    }

    Node* searchNode(Node* node, const Key& key) {
        if (node == _nil || node->key == key) return node;

        if (key < node->key) {
            return searchNode(node->left, key);
        }
        else {
            return searchNode(node->right, key);
        }
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
};


#endif //LABA_2_RBTREE_H
#pragma clang diagnostic pop
