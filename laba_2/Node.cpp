#include "Node.h"

Node::Node(Key key, int value) {
    this->key = std::move(key);
    this->value = value;
    this->color = RED;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

bool Node::IsRed() {
    return this->color == RED;
}

bool Node::IsBlack() {
    return this->color == BLACK;
}

void Node::PaintBlack() {
    this->color = BLACK;
}

void Node::PaintRed() {
    this->color = RED;
}

bool Node::IsColorBlack(bool color) {
    return color == BLACK;
}
