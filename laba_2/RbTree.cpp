#include "RbTree.h"

RbTree::RbTree() {
    _nil = new Node({ }, { });
    _nil->PaintBlack();
    _root = _nil;
}

RbTree::~RbTree() {
    _root = clear(_root);
    delete _nil;
}

bool RbTree::Insert(Key key, int value) {
    Node* newNode = new Node(std::move(key), value);
    newNode->left = _nil;
    newNode->right = _nil;
    return insertNode(newNode);
}

bool RbTree::Erase(const Key& key, const int& value) {
    Node* nodeToDelete = findNode(_root, key);
    if (nodeToDelete != _nil && nodeToDelete->value == value) {
        eraseNode(nodeToDelete);
        return true;
    }
    return false;
}

int RbTree::Find(const Key& key) {
    Node* node = findNode(_root, key);
    if (node == _nil) return -1;
    return node->value;
}

void RbTree::Clear() {
    _root = clear(_root);
    _nil->parent = nullptr;
}

void RbTree::Print() {
    print(_root);
}

bool RbTree::IsExist() {
    return _root != _nil;
}

std::stringstream RbTree::GetPostOrderTraversal() {
    std::stringstream result { };
    postOrder(_root, result);
    return result;
}

void RbTree::rotateRight(Node* node) {
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

void RbTree::rotateLeft(Node* node) {
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

Node* RbTree::findNode(Node* node, const Key& key) {
    while (node != _nil && node->key != key) {
        node = (key < node->key) ? node->left : node->right;
    }
    return node;
}

Node* RbTree::findParent(Node* node, const Key& key) {
    Node* parent = _nil;

    while (node != _nil && node->key != key) {
        parent = node;
        node = (key < node->key) ? node->left : node->right;
    }
    return parent;
}

bool RbTree::insertNode(Node* newNode) {
    Node* newNodeParent = findParent(_root, newNode->key);

    if (newNodeParent == _nil && _root == _nil) {
        _root = newNode;
    }
    else if (newNode->key < newNodeParent->key && newNodeParent->left == _nil) {
        newNodeParent->left = newNode;
    }
    else if (newNode->key > newNodeParent->key && newNodeParent->right == _nil) {
        newNodeParent->right = newNode;
    }
    else {
        return false;
    }

    newNode->parent = newNodeParent;
    rebalanceInsert(newNode);

    return true;
}

void RbTree::rebalanceInsert(Node* node) {
    Node* grandpa;
    Node* uncle;

    while (node->parent->IsRed()) {
        grandpa = node->parent->parent;
        uncle = (grandpa->left == node->parent) ? grandpa->right : grandpa->left;

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

Node* RbTree::findMax(Node* node) {
    while (node->right != _nil) {
        node = node->right;
    }
    return node;
}

void RbTree::replaceSubtree(Node* oldSubtree, Node* newSubtree) {
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

void RbTree::eraseNode(Node* nodeToDelete) {
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

void RbTree::rebalanceErase(Node* node) {
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

Node* RbTree::handleLeftRebalanceErase(Node* node) {
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

Node* RbTree::handleRightRebalanceErase(Node* node) {
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

Node* RbTree::clear(Node* node) {
    if (node == _nil) return _nil;

    if (node->left != _nil) {
        node->left = clear(node->left);
    }
    if (node->right != _nil) {
        node->right = clear(node->right);
    }
    delete node;
    return _nil;
}

void RbTree::print(Node* node, const std::string& rightPref, const std::string& cPref, const std::string& leftPref) {
    if (node == _nil) return;

    if (node->right != _nil) {
        print(node->right, rightPref + "  ", rightPref + CH_DOWN_HOR, rightPref + CH_VER);
    }

    fmt::print(fmt::fg(fmt::color::aquamarine), "{}", cPref);
    if (node->IsRed()) {
        fmt::print(CONSOLE_RED_COLOR, "R: {0} {1} {2} - {3}\n", node->key.Surname, node->key.Name, node->key.MiddleName,
                   node->key.StateNumber);
    }
    else {
        fmt::print(CONSOLE_BLACK_COLOR, "B: {0} {1} {2} - {3}\n", node->key.Surname, node->key.Name,
                   node->key.MiddleName, node->key.StateNumber);
    }

    if (node->left != _nil) {
        print(node->left, leftPref + CH_VER, leftPref + CH_UP_HOR, leftPref + "  ");
    }
}

void RbTree::postOrder(const Node* node, std::stringstream& result) {
    if (node == _nil) return;

    postOrder(node->left, result);
    postOrder(node->right, result);
    result << node->key << "\n";
}
