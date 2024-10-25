#include "AvlTree.h"

AvlTree::AvlTree() {
    _root = nullptr;
}

AvlTree::~AvlTree() {
    m_clear(_root);
}

void AvlTree::insert(int key) {
    _root = m_insert(_root, key);
}

void AvlTree::erase(int key) {
    _root = m_erase(_root, key);
}

void AvlTree::print() {
    m_print(_root);
}

void AvlTree::clear() {
    _root = m_clear(_root);
}

std::string AvlTree::getPreOrderString() {
    std::string result {};
    m_preOrder(_root, result);
    return result;
}

std::string AvlTree::getPostOrderString() {
    std::string result {};
    m_postOrder(_root, result);
    return result;
}

std::string AvlTree::getInOrderString() {
    std::string result {};
    m_inOrder(_root, result);
    return result;
}

int AvlTree::m_getHeight(AvlTree::Node *node) {
    return node ? node->height : -1;
}

int AvlTree::m_getBalanceFactor(AvlTree::Node *node) {
    return m_getHeight(node->left) - m_getHeight(node->right);
}

void AvlTree::m_fixHeight(AvlTree::Node *node) {
    int leftHeight = m_getHeight(node->left);
    int rightHeight = m_getHeight(node->right);

    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

AvlTree::Node *AvlTree::m_rotateRight(AvlTree::Node *node) {
    Node* leftNode = node->left;

    node->left = leftNode->right;
    leftNode->right = node;

    m_fixHeight(node);
    m_fixHeight(leftNode);

    return leftNode;   // возвращаем новый корень поддерева
}

AvlTree::Node *AvlTree::m_rotateLeft(AvlTree::Node *node) {
    Node* rightNode = node->right;

    node->right = rightNode->left;
    rightNode->left = node;

    m_fixHeight(node);
    m_fixHeight(rightNode);

    return rightNode;   // возвращаем новый корень поддерева
}

AvlTree::Node *AvlTree::m_balance(AvlTree::Node *node) {
    m_fixHeight(node);

    if (m_getBalanceFactor(node) == 2) {
        if (m_getBalanceFactor(node->left) < 0) {     // лево-правый поворот
            node->left = m_rotateLeft(node->left);
        }
        return m_rotateRight(node);
    }

    if (m_getBalanceFactor(node) == -2) {
        if (m_getBalanceFactor(node->right) > 0) {    // право-левый поворот
            node->right = m_rotateRight(node->right);
        }
        return m_rotateLeft(node);
    }

    return node;    // балансировка не требуется
}

AvlTree::Node *AvlTree::m_insert(AvlTree::Node *node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }
    if (key < node->key) {
        node->left = m_insert(node->left, key);
    }
    else {
        node->right = m_insert(node->right, key);
    }
    return m_balance(node);
}

AvlTree::Node *AvlTree::m_findMax(AvlTree::Node *node) {
    return node->right ? m_findMax(node->right) : node;
}

AvlTree::Node *AvlTree::m_eraseMax(AvlTree::Node *node) {
    if (node->right == nullptr) {
        return node->left;
    }
    node->right = m_eraseMax(node->right);

    return m_balance(node);   // возвращаем сбалансированное дерево
}

AvlTree::Node *AvlTree::m_erase(AvlTree::Node *node, int key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key < node->key) {
        node->left = m_erase(node->left, key);
    }
    else if (key > node->key) {
        node->right = m_erase(node->right, key);
    }
    else {  // key == node->key
        Node* left = node->left;
        Node* right = node->right;
        delete node;

        if (left == nullptr) {
            return right;
        }
        Node* max = m_findMax(left);
        max->left = m_eraseMax(left);
        max->right = right;

        return m_balance(max);
    }
    return m_balance(node);
}

AvlTree::Node *AvlTree::m_clear(AvlTree::Node *node) {
    if (!node) {
        return nullptr;
    }

    node->left = m_clear(node->left);
    node->right = m_clear(node->right);
    delete node;
    return nullptr;
}

/*Node* m_clear2(Node* node) {
    if (node->left) {
        node->left = m_clear(node->left);
    }
    if (node->right) {
        node->right = clear(node->right);
    }
    delete node;
    return nullptr;
}*/

void AvlTree::m_print(AvlTree::Node *node, const std::string &rpref,
                      const std::string &cpref, const std::string &lpref) {
    if (!node) {
        return;
    }

    if (node->right) {
        m_print(node->right, rpref + "  ", rpref + _ch_dhor,
                rpref + _ch_ver);
    }

    fmt::print("{}{}\n", cpref, node->key);

    if (node->left) {
        m_print(node->left, lpref + _ch_ver, lpref + _ch_uhor,
                lpref + "  ");
    }
}

void AvlTree::m_preOrder(const AvlTree::Node *node, std::string &result) {
    if (!node) {
        return;
    }

    result += std::to_string(node->key) + " ";
    m_preOrder(node->left, result);
    m_preOrder(node->right, result);
}

void AvlTree::m_postOrder(const AvlTree::Node *node, std::string &result) {
    if (!node) {
        return;
    }

    m_postOrder(node->left, result);
    m_postOrder(node->right, result);
    result += std::to_string(node->key) + " ";
}

void AvlTree::m_inOrder(const AvlTree::Node *node, std::string &result) {
    if (!node) {
        return;
    }

    m_inOrder(node->left, result);
    result += std::to_string(node->key) + " ";
    m_inOrder(node->right, result);
}

AvlTree::Node *AvlTree::m_findMin(AvlTree::Node *node) {
    return node->left ? m_findMin(node->left) : node;
}

AvlTree::Node *AvlTree::m_eraseMin(AvlTree::Node *node) {
    if (node->left == nullptr) {
        return node->right;
    }
    node->left = m_eraseMin(node->left);

    return m_balance(node);   // возвращаем сбалансированное дерево
}

AvlTree::Node *AvlTree::m_eraseWithMin(AvlTree::Node *node, int key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key < node->key) {
        node->left = m_eraseWithMin(node->left, key);
    }
    else if (key > node->key) {
        node->right = m_erase(node->right, key);
    }
    else {  // key == node->key
        Node* left = node->left;
        Node* right = node->right;
        delete node;

        if (right == nullptr) {
            return left;
        }
        Node* min = m_findMin(right);
        min->right = m_eraseMin(right);
        min->left = left;

        return m_balance(min);
    }
    return m_balance(node);
}
