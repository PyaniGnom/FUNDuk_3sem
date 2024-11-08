#include "AvlTree.h"

int main() {
    AvlTree tree;

    for (int i = 1; i <= 10; ++i) {
        tree.Insert(i);
    }

    tree.Print();
    tree.Erase(4);
    tree.Print();
    tree.Erase(6);
    tree.Print();
    tree.Erase(7);
    tree.Print();

    tree.Clear();

    return 0;
}
