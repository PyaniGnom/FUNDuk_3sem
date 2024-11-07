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
        _nil->PaintBlack();
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

    void Erase(int key) {
        Node* nodeToDelete = searchHelper(_root, key);
        if (nodeToDelete->key == key) {
            eraseNodeWithReplacementPredecessor(nodeToDelete);
        }
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

        leftNode->parent = node->parent;
        if (node->parent == _nil) {
            _root = leftNode;
        }
        else if (node->parent->right == node) {
            node->parent->right = leftNode;
        }
        else {
            node->parent->left = leftNode;
        }

        node->left = leftNode->right;
        if (leftNode->right != _nil) {
            leftNode->right->parent = node;
        }

        leftNode->right = node;
        node->parent = leftNode;
    }

    // левый поворот вокруг некоторого узла
    void rotateLeft(Node* node) {
        Node* rightNode = node->right;

        rightNode->parent = node->parent;
        if (node->parent == _nil) {
            _root = rightNode;
        }
        else if (node->parent->left == node) {
            node->parent->left = rightNode;
        }
        else {
            node->parent->right = rightNode;
        }

        node->right = rightNode->left;
        if (rightNode->left != _nil) {
            rightNode->left->parent = node;
        }

        rightNode->left = node;
        node->parent = rightNode;
    }

    Node* searchHelper(Node* node, int key) {
        if (node == _nil || key == node->key) {
            return node;
        }
        else if (key < node->key) {
            if (node->left == _nil) {
                return node;
            }

            return searchHelper(node->left, key);
        }
        else {
            if (node->right == _nil) {
                return node;
            }

            return searchHelper(node->right, key);
        }
    }

    void insertNode(Node* newNode) {
        Node* newNodeParent = searchHelper(_root, newNode->key);

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
        while (node->parent->IsRed()) {
            Node* grandpa = node->parent->parent;
            Node* uncle = grandpa->left == node->parent ? grandpa->right : grandpa->left;

            if (uncle->IsRed()) {
                node->parent->PaintBlack();
                uncle->PaintBlack();
                grandpa->PaintRed();
            }
            else {
                if (node->parent == grandpa->left) {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->PaintBlack();
                    grandpa->PaintRed();

                    rotateRight(grandpa);
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->PaintBlack();
                    grandpa->PaintRed();
                    rotateLeft(grandpa);
                }
            }
            node = grandpa;
        }
        _root->PaintBlack();
    }

    Node* findMin(Node* node) {
        return node->left != _nil ? findMin(node->left) : node;
    }

    Node* findMax(Node* node) {
        return node->right != _nil ? findMax(node->right) : node;
    }

    void transplant(Node* toNode, Node* fromNode) {
        if (toNode->parent == _nil)
            _root = fromNode;
        else if (toNode == toNode->parent->left)
            toNode->parent->left = fromNode;
        else
            toNode->parent->right = fromNode;
        fromNode->parent = toNode->parent;
    }

    void eraseNodeWithReplacementSuccessor(Node* nodeToDelete) {
        Node* child;
        bool removedNodeColor = nodeToDelete->color;

        if (nodeToDelete->left == _nil) {
            child = nodeToDelete->right;
            transplant(nodeToDelete, nodeToDelete->right);
        }
        else if (nodeToDelete->right == _nil) {
            child = nodeToDelete->left;
            transplant(nodeToDelete, nodeToDelete->left);
        }
        else {
            Node* minNode = findMin(nodeToDelete->right);
            removedNodeColor = minNode->color;
            child = minNode->right;

            if (minNode->parent == nodeToDelete) {
                child->parent = minNode;
            }
            else {
                transplant(minNode, minNode->right);
                minNode->right = nodeToDelete->right;
                minNode->right->parent = minNode;
            }

            transplant(nodeToDelete, minNode);
            minNode->left = nodeToDelete->left;
            minNode->left->parent = minNode;
            minNode->color = nodeToDelete->color;
        }

        delete nodeToDelete;

        if (removedNodeColor == true) {
            rebalanceErase(child);
        }
    }

    void eraseNodeWithReplacementPredecessor(Node* nodeToDelete) {
        Node* child;
        bool removedNodeColor = nodeToDelete->color;

        if (nodeToDelete->left == _nil) {
            child = nodeToDelete->right;
            transplant(nodeToDelete, nodeToDelete->right);
        }
        else if (nodeToDelete->right == _nil) {
            child = nodeToDelete->left;
            transplant(nodeToDelete, nodeToDelete->left);
        }
        else {
            Node* maxNode = findMax(nodeToDelete->left);
            removedNodeColor = maxNode->color;
            child = maxNode->left;

            if (maxNode->parent == nodeToDelete) {
                child->parent = maxNode;
            }
            else {
                transplant(maxNode, maxNode->left);
                maxNode->left = nodeToDelete->left;
                maxNode->left->parent = maxNode;
            }

            transplant(nodeToDelete, maxNode);
            maxNode->right = nodeToDelete->right;
            maxNode->right->parent = maxNode;
            maxNode->color = nodeToDelete->color;
        }

        delete nodeToDelete;

        if (removedNodeColor == true) {
            rebalanceErase(child);
        }
    }

    void rebalanceErase(Node* node) {
        while (node != _root && node->IsBlack()) {
            Node* brother;
            if (node == node->parent->left) {
                brother = node->parent->right;
                if (brother->IsRed()) {
                    brother->PaintBlack();
                    node->parent->PaintRed();
                    rotateLeft(node->parent);
                    brother = node->parent->right;
                }
                if (brother->left->IsBlack() && brother->right->IsBlack()) {
                    brother->PaintRed();
                    node = node->parent;
                }
                else {
                    if (brother->right->IsBlack()) {
                        brother->left->PaintBlack();
                        brother->PaintRed();
                        rotateRight(brother);
                        brother = node->parent->right;
                    }
                    brother->color = node->parent->color;
                    node->parent->PaintBlack();
                    brother->right->PaintBlack();
                    rotateLeft(node->parent);
                    node = _root;
                }
            }
            else {
                brother = node->parent->left;
                if (brother->IsRed()) {
                    brother->PaintBlack();
                    node->parent->PaintRed();
                    rotateRight(node->parent);
                    brother = node->parent->left;
                }
                if (brother->left->IsBlack() && brother->right->IsBlack()) {
                    brother->PaintRed();
                    node = node->parent;
                }
                else {
                    if (brother->left->IsBlack()) {
                        brother->right->PaintBlack();
                        brother->PaintRed();
                        rotateLeft(brother);
                        brother = node->parent->left;
                    }
                    brother->color = node->parent->color;
                    node->parent->PaintBlack();
                    brother->left->PaintBlack();
                    rotateRight(node->parent);
                    node = _root;
                }
            }
        }
        node->PaintBlack();
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


#endif //RB_TREE_RBTREE_H
#pragma clang diagnostic pop
