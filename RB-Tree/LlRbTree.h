#ifndef RB_TREE_LLRBTREE_H
#define RB_TREE_LLRBTREE_H


#include <fmt/color.h>

template <typename Key, typename Value>
class LlRbTree {
public:
    LlRbTree() {
        _nil = new Node(Key(), Value());
        _nil->color = BLACK;
        _root = _nil;
    }

    ~LlRbTree() {
        _root = clear(_root);
        delete _nil;
    }

    void Insert(Key key, Value value) {
        Node* newNode = new Node(key, value);
        newNode->left = _nil;
        newNode->right = _nil;
        _root = insertNode(_root, newNode);
        _root->color = BLACK;
    }

    void Erase(Key key) {
        _root = eraseNode(_root, key);
        _root->color = BLACK;
    }

    void Print() {
        fmt::print("\n");
        print(_root);
    }

    void Clear() {
        _root = clear(_root);
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
    const std::string CH_UP_HOR = "\u2514\u2500";       // "└─"
    const std::string CH_DOWN_HOR = "\u250C\u2500";     // "┌─"
    const std::string CH_VER = "\u2502 ";               // "│ "
    const fmt::text_style CONSOLE_RED_COLOR = fmt::fg(fmt::color::red);
    const fmt::text_style CONSOLE_BLACK_COLOR = fmt::fg(fmt::color::dark_gray);

    const static bool RED = false;
    const static bool BLACK = true;

    struct Node {
        Key key;        // ключ узла
        Value value;    // значения узла
        bool color;     // цвет узла
        Node* left;     // указатель на левого потомка
        Node* right;    // указатель на правого потомка

        // конструктор узла
        Node(Key k, Value val) {
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

        return leftNode;
    }

    Node* rotateLeft(Node* node) {
        Node* rightNode = node->right;

        node->right = rightNode->left;
        rightNode->left = node;

        rightNode->color = node->color;
        node->color = RED;

        return rightNode;
    }

    bool isRed(Node* node) {
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

    Node* eraseNode(Node* node, Key key) {
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
        if (node->color == BLACK) {
            fmt::print(CONSOLE_BLACK_COLOR, "B:{}\n", node->key);
        }
        else {
            fmt::print(CONSOLE_RED_COLOR, "R:{}\n", node->key);
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
