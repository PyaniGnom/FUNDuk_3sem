#ifndef LABA_2_RBTREE_H
#define LABA_2_RBTREE_H


#include <sstream>
#include <utility>
#include <fmt/color.h>
#include "Node.h"
#include "ConsoleColors.h"

class RbTree {
public:
    RbTree() {
        _nil = new Node({}, {});
        _nil->PaintBlack();
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
        insertNode(newNode);
    }

    void Erase(const Key& key) {
        Node* nodeToDelete = findNode(_root, key);
        if (nodeToDelete != _nil) {
            eraseNode(nodeToDelete);
        }
    }

    int Find(const Key& key) {
        Node* node = findNode(_root, key);
        if (node == _nil) return {};
        return node->value;
    }

    void Clear() {
        _root = clear(_root);
        _nil->parent = nullptr;
    }

    void Print() {
        fmt::print("\n");
        print(_root);
    }

    std::stringstream GetPostOrderTraversal() {
        std::stringstream result {};
        postOrder(_root, result);
        return result;
    }

private:
    constexpr static std::string CH_UP_HOR = "\u2514\u2500";       // "└─"
    constexpr static std::string CH_DOWN_HOR = "\u250C\u2500";     // "┌─"
    constexpr static std::string CH_VER = "\u2502 ";               // "│ "

    Node* _root;
    Node* _nil;

    /// Правый поворот вокруг некоторого узла
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

    /// Левый поворот вокруг некоторого узла
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

    Node* findNode(Node* node, const Key& key) {
        while (node != _nil && node->key != key) {
            node = (key < node->key) ? node->left : node->right;
        }
        return node;
    }

    Node* findParent(Node* node, const Key& key) {
        Node* parent = _nil;

        while (node != _nil && node->key != key) {
            parent = node;
            node = (key < node->key) ? node->left : node->right;
        }
        return parent;
    }

    void insertNode(Node* newNode) {
        Node* newNodeParent = findParent(_root, newNode->key);

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
            Node* uncle = (grandpa->left == node->parent) ? grandpa->right : grandpa->left;

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

    /// Нахождение узла с максимальным ключом в поддереве
    Node* findMax(Node* node) {
        while (node->right != _nil) {
            node = node->right;
        }
        return node;
    }

    void replaceSubtree(Node* oldSubtree, Node* newSubtree) {
        if (oldSubtree->parent == _nil) {
            _root = newSubtree;
        }
        else if (oldSubtree == oldSubtree->parent->left) {
            oldSubtree->parent->left = newSubtree;
        }
        else {
            oldSubtree->parent->right = newSubtree;
        }
        newSubtree->parent = oldSubtree->parent;
    }

    void eraseNode(Node* nodeToDelete) {
        Node* child;
        bool removedNodeColor = nodeToDelete->color;

        if (nodeToDelete->left == _nil) {
            child = nodeToDelete->right;
            replaceSubtree(nodeToDelete, nodeToDelete->right);
        }
        else if (nodeToDelete->right == _nil) {
            child = nodeToDelete->left;
            replaceSubtree(nodeToDelete, nodeToDelete->left);
        }
        else {
            Node* maxNode = findMax(nodeToDelete->left);
            removedNodeColor = maxNode->color;
            child = maxNode->left;

            if (maxNode->parent == nodeToDelete) {
                child->parent = maxNode;
            }
            else {
                replaceSubtree(maxNode, maxNode->left);
                maxNode->left = nodeToDelete->left;
                maxNode->left->parent = maxNode;
            }

            replaceSubtree(nodeToDelete, maxNode);
            maxNode->right = nodeToDelete->right;
            maxNode->right->parent = maxNode;
            maxNode->color = nodeToDelete->color;
        }

        delete nodeToDelete;

        if (Node::IsColorBlack(removedNodeColor)) {
            rebalanceErase(child);
        }
    }

    void rebalanceErase(Node* node) {
        while (node != _root && node->IsBlack()) {
            if (node == node->parent->left) {
                node = handleLeftRebalanceErase(node);
            }
            else {
                node = handleRightRebalanceErase(node);
            }
        }
        node->PaintBlack();
    }

    Node* handleLeftRebalanceErase(Node* node) {
        Node* brother = node->parent->right;
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
        return node;
    }

    Node* handleRightRebalanceErase(Node* node) {
        Node* brother = node->parent->left;
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
        return node;
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
            fmt::print(CONSOLE_RED_COLOR, "R: {0} {1} {2} - {3}\n", node->key.Surname, node->key.Name, node->key.MiddleName, node->key.StateNumber);
        }
        else {
            fmt::print(CONSOLE_BLACK_COLOR, "B: {0} {1} {2} - {3}\n", node->key.Surname, node->key.Name, node->key.MiddleName, node->key.StateNumber);
        }

        if (node->left != _nil) {
            print(node->left, lpref + CH_VER, lpref + CH_UP_HOR, lpref + "  ");
        }
    }

    void postOrder(const Node* node, std::stringstream& result) {
        if (node == _nil) return;

        postOrder(node->left, result);
        postOrder(node->right, result);
        result << node->key << "\n";
    }
};


#endif //LABA_2_RBTREE_H
