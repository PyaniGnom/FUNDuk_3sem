#ifndef AVL_TREE_AVLTREE_H
#define AVL_TREE_AVLTREE_H


#include <string>
#include <fmt/color.h>

template <typename Key>
class AvlTree {
public:
    AvlTree() {
        _root = nullptr;
    }

    ~AvlTree() {
        _root = clear(_root);
    }

    void Insert(Key key) {
        Node* newNode = new Node(key);
        _root = insertNode(_root, newNode);
    }

    void Erase(Key key) {
        _root = eraseNode(_root, key);
    }

    void Print() {
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

    struct Node {
        Key key;        // ключ узла
        int height;     // высота узла
        Node* left;     // указатель на левого потомка
        Node* right;    // указатель на правого потомка

        // конструктор узла
        Node(Key k) {
            key = k;
            height = 0;
            left = nullptr;
            right = nullptr;
        };
    };

    Node* _root;

    // определение высоты некоторого узла
    int getHeight(Node* node) {
        return node ? node->height : -1;
    }

    // определение фактора балансировки некоторого узла
    int getBalanceFactor(Node* node) {
        return getHeight(node->left) - getHeight(node->right);
    }

    // корректировка высоты некоторого узла
    void fixHeight(Node* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    // правый поворот вокруг некоторого узла
    Node* rotateRight(Node* node) {
        Node* leftNode = node->left;

        node->left = leftNode->right;
        leftNode->right = node;

        fixHeight(node);
        fixHeight(leftNode);

        return leftNode;    // возвращаем новый корень поддерева
    }

    // левый поворот вокруг некоторого узла
    Node* rotateLeft(Node* node) {
        Node* rightNode = node->right;

        node->right = rightNode->left;
        rightNode->left = node;

        fixHeight(node);
        fixHeight(rightNode);

        return rightNode;   // возвращаем новый корень поддерева
    }

    // балансировка некоторого узла
    Node* balance(Node* node) {
        fixHeight(node);

        if (getBalanceFactor(node) == 2) {
            if (getBalanceFactor(node->left) < 0) {     // лево-правый поворот
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (getBalanceFactor(node) == -2) {
            if (getBalanceFactor(node->right) > 0) {    // право-левый поворот
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;    // балансировка не требуется
    }

    // вставка узла с ключом key в дерево с корнем node
    Node* insertNode(Node* node, Node* newNode) {
        if (node == nullptr) {
            return newNode;
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
        return balance(node);
    }

    // поиск узла с максимальным ключом в дереве node
    Node* findMax(Node* node) {
        return node->right ? findMax(node->right) : node;
    }

    // удаление узла с максимальным ключом в дереве node
    Node* eraseMax(Node* node) {
        if (node->right == nullptr) {
            return node->left;
        }
        node->right = eraseMax(node->right);

        return balance(node);   // возвращаем сбалансированное дерево
    }

    // удаление узла с ключом key из дерева node с заменой на предшественника
    Node* eraseNode(Node* node, Key key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->left = eraseNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = eraseNode(node->right, key);
        }
        else {  // key == node->key
            Node* left = node->left;
            Node* right = node->right;
            delete node;

            if (left == nullptr) {
                return right;
            }
            Node* max = findMax(left);
            max->left = eraseMax(left);
            max->right = right;

            return balance(max);
        }
        return balance(node);
    }

    Node* clear(Node* node) {
        if (!node) {
            return nullptr;
        }

        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
        return nullptr;
    }

    Node* coolestClear(Node* node) {
        if (!node) {
            return nullptr;
        }
        if (node->left) {
            node->left = coolestClear(node->left);
        }
        if (node->right) {
            node->right = coolestClear(node->right);
        }
        delete node;
        return nullptr;
    }

    void print(Node* node, const std::string& rpref = "", const std::string& cpref = "", const std::string& lpref = "") {
        if (!node) {
            return;
        }

        if (node->right) {
            print(node->right, rpref + "  ", rpref + CH_DOWN_HOR, rpref + CH_VER);
        }

        fmt::print("{}{}\n", cpref, node->key);

        if (node->left) {
            print(node->left, lpref + CH_VER, lpref + CH_UP_HOR, lpref + "  ");
        }
    }

    void preOrder(const Node* node, std::string& result) {
        if (!node) {
            return;
        }

        result += std::to_string(node->key) + " ";
        preOrder(node->left, result);
        preOrder(node->right, result);
    }

    void postOrder(const Node* node, std::string& result) {
        if (!node) {
            return;
        }

        postOrder(node->left, result);
        postOrder(node->right, result);
        result += std::to_string(node->key) + " ";
    }

    void inOrder(const Node* node, std::string& result) {
        if (!node) {
            return;
        }

        inOrder(node->left, result);
        result += std::to_string(node->key) + " ";
        inOrder(node->right, result);
    }

    // поиск узла с минимальным ключом в дереве node
    Node* findMin(Node* node)  {
        return node->left ? findMin(node->left) : node;
    }

    // удаление узла с минимальным ключом в дереве node
    Node* eraseMin(Node* node)  {
        if (node->left == nullptr) {
            return node->right;
        }
        node->left = eraseMin(node->left);

        return balance(node);   // возвращаем сбалансированное дерево
    }

    // удаление узла с ключом key из дерева node с заменой на преемника
    Node* eraseMinWithReplacementSuccessor(Node* node, Key key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->left = eraseMinWithReplacementSuccessor(node->left, key);
        }
        else if (key > node->key) {
            node->right = eraseNode(node->right, key);
        }
        else {  // key == node->key
            Node* left = node->left;
            Node* right = node->right;
            delete node;

            if (right == nullptr) {
                return left;
            }
            Node* min = findMin(right);
            min->right = eraseMin(right);
            min->left = left;

            return balance(min);
        }
        return balance(node);
    }
};


#endif //AVL_TREE_AVLTREE_H
