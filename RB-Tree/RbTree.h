#ifndef RB_TREE_RBTREE_H
#define RB_TREE_RBTREE_H


#include <fmt/color.h>
#include <optional>
#include <sstream>
#include "Node.h"

class RbTree {
public:
    RbTree() {
        nil = new Node();
        nil->PaintBlack();
        root = nil;
    }

    ~RbTree() {
        root = clear(root);
        delete nil;
    }

    void Insert(int key, std::string value) {
        Node* newNode = new Node(key, std::move(value));
        newNode->left = nil;
        newNode->right = nil;
        insertNode(newNode);
    }

    void Erase(const int& key) {
        Node* nodeToDelete = findNode(root, key);
        if (nodeToDelete != nil) {
            eraseNodeWithReplacementPredecessor(nodeToDelete);
        }
    }

    std::string Find(const int& key) {
        Node* node = findNode(root, key);
        if (node == nil) return {};
        return node->value;
    }

    void Clear() {
        root = clear(root);
        nil->parent = nullptr;
    }

    void Print() {
        print(root);
    }

    /// Прямой обход дерева
    std::string GetPreOrderTraversalString() {
        std::stringstream result {};
        preOrder(root, result);
        return result.str();
    }

    /// Обратный обход дерева
    std::string GetPostOrderTraversalString() {
        std::stringstream result {};
        postOrder(root, result);
        return result.str();
    }

    /// Симметричный обход дерева
    std::string GetInOrderTraversalString() {
        std::stringstream result {};
        inOrder(root, result);
        return result.str();
    }

private:
    constexpr static std::string CH_UP_HOR = "\u2514\u2500";       // "└─"
    constexpr static std::string CH_DOWN_HOR = "\u250C\u2500";     // "┌─"
    constexpr static std::string CH_VER = "\u2502 ";               // "│ "
    constexpr static fmt::text_style CONSOLE_RED_COLOR = fmt::fg(fmt::color::red);
    constexpr static fmt::text_style CONSOLE_BLACK_COLOR = fmt::fg(fmt::color::dark_gray);

    Node* root;
    Node* nil;

    /// Правый поворот вокруг некоторого узла
    void rotateRight(Node* node) {
        Node* leftNode = node->left;

        leftNode->parent = node->parent;
        if (node->parent == nil) {
            root = leftNode;
        }
        else if (node->parent->right == node) {
            node->parent->right = leftNode;
        }
        else {
            node->parent->left = leftNode;
        }

        node->left = leftNode->right;
        if (leftNode->right != nil) {
            leftNode->right->parent = node;
        }

        leftNode->right = node;
        node->parent = leftNode;
    }

    /// Левый поворот вокруг некоторого узла
    void rotateLeft(Node* node) {
        Node* rightNode = node->right;

        rightNode->parent = node->parent;
        if (node->parent == nil) {
            root = rightNode;
        }
        else if (node->parent->left == node) {
            node->parent->left = rightNode;
        }
        else {
            node->parent->right = rightNode;
        }

        node->right = rightNode->left;
        if (rightNode->left != nil) {
            rightNode->left->parent = node;
        }

        rightNode->left = node;
        node->parent = rightNode;
    }

    Node* findNode(Node* node, const int& key) {
        while (node != nil && node->key != key) {
            node = (key < node->key) ? node->left : node->right;
        }
        return node;
    }

    Node* findParent(Node* node, const int& key) {
        Node* parent = nil;

        while (node != nil && node->key != key) {
            parent = node;
            node = (key < node->key) ? node->left : node->right;
        }
        return parent;
    }

    void insertNode(Node* newNode) {
        Node* newNodeParent = findParent(root, newNode->key);

        if (newNodeParent == nil && root == nil) {
            root = newNode;
        }
        else if (newNode->key < newNodeParent->key && newNodeParent->left == nil) {
            newNodeParent->left = newNode;
        }
        else if (newNode->key > newNodeParent->key && newNodeParent->right == nil) {
            newNodeParent->right = newNode;
        }
        else {
            return;
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
        root->PaintBlack();
    }

    /// Нахождение узла с минимальным ключом в поддереве
    Node* findMin(Node* node) {
        while (node->left != nil) {
            node = node->left;
        }
        return node;
    }

    /// Нахождение узла с максимальным ключом в поддереве
    Node* findMax(Node* node) {
        while (node->right != nil) {
            node = node->right;
        }
        return node;
    }

    void replaceSubtree(Node* oldSubtree, Node* newSubtree) {
        if (oldSubtree->parent == nil) {
            root = newSubtree;
        }
        else if (oldSubtree == oldSubtree->parent->left) {
            oldSubtree->parent->left = newSubtree;
        }
        else {
            oldSubtree->parent->right = newSubtree;
        }
        newSubtree->parent = oldSubtree->parent;
    }

    void eraseNodeWithReplacementPredecessor(Node* nodeToDelete) {
        Node* child;
        bool removedNodeColor = nodeToDelete->color;

        if (nodeToDelete->left == nil) {
            child = nodeToDelete->right;
            replaceSubtree(nodeToDelete, nodeToDelete->right);
        }
        else if (nodeToDelete->right == nil) {
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

    void eraseNodeWithReplacementSuccessor(Node* nodeToDelete) {
        Node* child;
        bool removedNodeColor = nodeToDelete->color;

        if (nodeToDelete->left == nil) {
            child = nodeToDelete->right;
            replaceSubtree(nodeToDelete, nodeToDelete->right);
        }
        else if (nodeToDelete->right == nil) {
            child = nodeToDelete->left;
            replaceSubtree(nodeToDelete, nodeToDelete->left);
        }
        else {
            Node* minNode = findMin(nodeToDelete->right);
            removedNodeColor = minNode->color;
            child = minNode->right;

            if (minNode->parent == nodeToDelete) {
                child->parent = minNode;
            }
            else {
                replaceSubtree(minNode, minNode->right);
                minNode->right = nodeToDelete->right;
                minNode->right->parent = minNode;
            }

            replaceSubtree(nodeToDelete, minNode);
            minNode->left = nodeToDelete->left;
            minNode->left->parent = minNode;
            minNode->color = nodeToDelete->color;
        }

        delete nodeToDelete;

        if (Node::IsColorBlack(removedNodeColor)) {
            rebalanceErase(child);
        }
    }

    void rebalanceErase(Node* node) {
        while (node != root && node->IsBlack()) {
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
            node = root;
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
            node = root;
        }
        return node;
    }

    Node* clear(Node* node) {
        if (node == nil) return nil;

        if (node->left) {
            node->left = clear(node->left);
        }
        if (node->right) {
            node->right = clear(node->right);
        }
        delete node;
        return nil;
    }

    void print(Node* node, const std::string& rpref = "", const std::string& cpref = "", const std::string& lpref = "") {
        if (node == nil) return;

        if (node->right != nil) {
            print(node->right, rpref + "  ", rpref + CH_DOWN_HOR, rpref + CH_VER);
        }

        fmt::print(fmt::fg(fmt::color::aquamarine), "{}", cpref);
        if (node->IsRed()) {
            fmt::print(CONSOLE_RED_COLOR, "R:{}\n", node->key);
        }
        else {
            fmt::print(CONSOLE_BLACK_COLOR, "B:{}\n", node->key);
        }

        if (node->left != nil) {
            print(node->left, lpref + CH_VER, lpref + CH_UP_HOR, lpref + "  ");
        }
    }

    void preOrder(const Node* node, std::stringstream& result) {
        if (node == nil) return;

        result << node->key << " ";
        preOrder(node->left, result);
        preOrder(node->right, result);
    }

    void postOrder(const Node* node, std::stringstream& result) {
        if (node == nil) return;

        postOrder(node->left, result);
        postOrder(node->right, result);
        result << node->key << " ";
    }

    void inOrder(const Node* node, std::stringstream& result) {
        if (node == nil) return;

        inOrder(node->left, result);
        result << node->key << " ";
        inOrder(node->right, result);
    }
};


#endif //RB_TREE_RBTREE_H
