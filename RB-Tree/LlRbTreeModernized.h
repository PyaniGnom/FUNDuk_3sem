/**
 * ***********************************
 * *********** UNFINISHED ************
 * ***********************************
 */

#ifndef RB_TREE_LLRBTREEMODERNIZED_H
#define RB_TREE_LLRBTREEMODERNIZED_H


#include <fmt/color.h>

class LlRbTreeModernized {
public:
    LlRbTreeModernized() {
        _nil = new Node(int(), int());
        _nil->color = BLACK;
        _root = _nil;
    }

    ~LlRbTreeModernized() {
        clear(_root);
        delete _nil;
    }

    void Insert(int key, int value) {
        Node* newNode = new Node(key, value);
        newNode->left = _nil;
        newNode->right = _nil;
        _root = insertNode(_root, newNode);
        _root->color = BLACK;
    }

    void Erase(int key) {
        _root = erase(_root, key);
        _root->color = BLACK;
    }

    void Print() {
        print(_root);
    }

private:
    const std::string _ch_uhor = "\u2514\u2500";    // "└─"
    const std::string _ch_dhor = "\u250C\u2500";    // "┌─"
    const std::string _ch_ver = "\u2502 ";          // "│ "
    const fmt::text_style CONSOLE_RED_COLOR = fmt::fg(fmt::color::red);
    const fmt::text_style CONSOLE_BLACK_COLOR = fmt::fg(fmt::color::dark_gray);

    const static bool RED = false;
    const static bool BLACK = true;

    struct Node {
        int key;        // ключ узла
        int value;
        bool color;     // цвет узла
        Node* left;     // указатель на левого потомка
        Node* right;    // указатель на правого потомка

        // конструктор узла
        Node(int k, int val) {
            key = k;
            value = val;
            color = RED;
            left = nullptr;
            right = nullptr;
        };
    };

    Node* _root;
    Node* _nil;

    Node* rotateRight(Node* node) {
        Node* leftNode = node->left;

        node->left = leftNode->right;
        leftNode->right = node;

        leftNode->color = node->color;
        node->color = RED;

        return leftNode;   // возвращаем новый корень поддерева
    }

    Node* rotateLeft(Node* node) {
        Node* rightNode = node->right;

        node->right = rightNode->left;
        rightNode->left = node;

        rightNode->color = node->color;
        node->color = RED;

        return rightNode;   // возвращаем новый корень поддерева
    }

    bool isRed(Node* node) {
        return node->color == RED;
    }

    void flipColors(Node* node) {
        node->color = !node->color;
        if (node->left != _nil) node->left->color = !node->left->color;
        if (node->right != _nil) node->right->color = !node->right->color;
    }

    Node* insertNode(Node* node, Node* newNode) {
        if (node == _nil) {
            return newNode;
        }

        if (isRed(node->left) && isRed(node->right)) {
            flipColors(node);
        }

        if (newNode->key < node->key) {
            node->left = insertNode(node->left, newNode);
        }
        else if (newNode->key > node->key) {
            node->right = insertNode(node->right, newNode);
        }
        else {
            return node;
        }

        if (isRed(node->right) && !isRed(node->left)) {
            node = rotateLeft(node);
        }
        if (isRed(node->left) && isRed(node->left->left)) {
            node = rotateRight(node);
        }

        return node;
    }

    Node* moveRedLeft(Node* node) {
        flipColors(node);
        if (node->right != _nil && isRed(node->right->left)) {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
            flipColors(node);
        }
        return node;
    }

    Node* moveRedRight(Node* node) {
        flipColors(node);
        if (node->left != _nil && isRed(node->left->left)) {
            node = rotateRight(node);
            flipColors(node);
        }
        return node;
    }

    Node* findMin(Node* node) {
        return node->left != _nil ? findMin(node->left) : node;
    }

    Node* eraseMin(Node* node) {
        if (node->left == _nil) {
            return _nil;
        }

        if (!isRed(node->left) && !isRed(node->left->left)) {
            node = moveRedLeft(node);
        }
        node->left = eraseMin(node->left);

        return fixUp(node);
    }

    Node* fixUp(Node* node) {
        if (isRed(node->right)) {
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

    Node* erase(Node* node, int key) {
        if (node == _nil) {
            return _nil;
        }
        if (key < node->key) {
            if (node->left != _nil && !isRed(node->left) && !isRed(node->left->left)) {
                node = moveRedLeft(node);
            }
            node->left = erase(node->left, key);
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
                node->right = erase(node->right, key);
            }
        }

        return fixUp(node);
    }

    Node* clear(Node* node) {
        if (node == _nil) {
            return _nil;
        }

        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
        return _nil;
    }

    void print(Node* node, const std::string& rpref = "", const std::string& cpref = "", const std::string& lpref = "") {
        if (node == _nil) {
            return;
        }

        if (node->right != _nil) {
            print(node->right, rpref + "  ", rpref + _ch_dhor, rpref + _ch_ver);
        }

        fmt::print(fmt::fg(fmt::color::aquamarine), "{}", cpref);
        if (node->color == BLACK) {
            fmt::print(CONSOLE_BLACK_COLOR, "B:{}\n", node->key);
        }
        else {
            fmt::print(CONSOLE_RED_COLOR, "R:{}\n", node->key);
        }

        if (node->left != _nil) {
            print(node->left, lpref + _ch_ver, lpref + _ch_uhor, lpref + "  ");
        }
    }
};


#endif //RB_TREE_LLRBTREEMODERNIZED_H
