#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#ifndef RB_TREE_LLRBTREE_H
#define RB_TREE_LLRBTREE_H


#include <fmt/color.h>
#include "Node.h"

class LlRbTree {
public:
    LlRbTree() {
        _nil = new Node();
        _nil->PaintBlack();
        _root = _nil;
    }

    ~LlRbTree() {
        _root = clear(_root);
        delete _nil;
    }

    void Insert(int key, std::string value) {
        Node* newNode = new Node(key, std::move(value));
        newNode->left = _nil;
        newNode->right = _nil;
        _root = insertNode(_root, newNode);
        _root->PaintBlack();
    }

    void Erase(const int& key) {
        _root = eraseNode(_root, key);
        _root->PaintBlack();
    }

    std::string Find(const int& key) {
        Node* node = searchNode(_root, key);
        if (node == _nil) return {};
        return node->value;
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
    static Node* rotateRight(Node* node) {
        Node* leftNode = node->left;

        node->left = leftNode->right;
        leftNode->right = node;

        leftNode->color = node->color;
        node->PaintRed();

        return leftNode;
    }

    // левый поворот вокруг некоторого узла
    static Node* rotateLeft(Node* node) {
        Node* rightNode = node->right;

        node->right = rightNode->left;
        rightNode->left = node;

        rightNode->color = node->color;
        node->PaintRed();

        return rightNode;
    }

    // реверс цветов некоторого узла и его потомков
    void flipColors(Node* node) {
        node->color = !node->color;
        if (node->left != _nil) node->left->color = !node->left->color;
        if (node->right != _nil) node->right->color = !node->right->color;
    }

    // фикс дерева с корнем node
    Node* fixUp(Node* node) {
        if (node->right->IsRed() && node->left->IsBlack()) {
            node = rotateLeft(node);
        }
        if (node->left->IsRed() && node->left->left->IsRed()) {
            node = rotateRight(node);
        }
        if (node->left->IsRed() && node->right->IsRed()) {
            flipColors(node);
        }
        return node;
    }

    // вставка нового узла newNode в дерево с корнем node
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
        if (node->right->left->IsRed()) {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
            flipColors(node);
        }
        return node;
    }

    Node* moveRedRight(Node* node) {
        flipColors(node);
        if (node->left->left->IsRed()) {
            node = rotateRight(node);
            flipColors(node);
        }
        return node;
    }

    Node* findMin(Node* node) {
        return node->left != _nil ? findMin(node->left) : node;
    }

    Node* removeMin(Node* node) {
        if (node->left == _nil) return _nil;

        if (node->left->IsBlack() && node->left->left->IsBlack()) {
            node = moveRedLeft(node);
        }
        node->left = removeMin(node->left);

        return fixUp(node);
    }

    Node* eraseNode(Node* node, const int& key) {
        if (node == _nil) return _nil;

        if (key < node->key) {
            if (node->left != _nil && node->left->IsBlack() && node->left->left->IsBlack()) {
                node = moveRedLeft(node);
            }
            node->left = eraseNode(node->left, key);
        }
        else {
            if (node->left->IsRed()) {
                node = rotateRight(node);
            }
            if (key == node->key && node->right == _nil) {
                delete node;
                return _nil;
            }
            if (node->right != _nil && node->right->IsBlack() && node->right->left->IsBlack()) {
                node = moveRedRight(node);
            }
            if (key == node->key) {
                Node* min = findMin(node->right);
                min->right = removeMin(node->right);
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

    Node* searchNode(Node* node, const int& key) {
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

    void print(Node* node, const std::string& rpref = "", const std::string& cpref = "", const std::string& lpref = "") {
        if (node == _nil) return;

        if (node->right != _nil) {
            print(node->right, rpref + "  ", rpref + CH_DOWN_HOR, rpref + CH_VER);
        }

        fmt::print(fmt::fg(fmt::color::aquamarine), "{}", cpref);
        if (node->IsRed()) {
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


#endif //RB_TREE_LLRBTREE_H
#pragma clang diagnostic pop
