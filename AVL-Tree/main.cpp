#include <fmt/color.h>
#include <map>
#include "AvlTree.h"

int main() {
    AvlTree<int> tree;

    for (int i = 1; i < 11; ++i) {
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

    auto container = new std::map<int, std::string>();

    container->insert({{2, "DVA"}, {3, "TRI"}});
    container->erase(2);

    delete container;

    return 0;
}
