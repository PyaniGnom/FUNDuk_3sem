#include <fmt/color.h>
#include "AvlTree.h"
#include <map>

int main() {
    AvlTree tree;

    for (int i = 1; i < 11; ++i) {
        tree.insert(i);
        tree.print();
    }

    tree.erase(4);
    tree.print();
    tree.erase(6);
    tree.print();
    tree.erase(7);
    tree.print();

    /*std::map<int, std::string> container;

    container.insert({{2, "DVA"}, {3, "TRI"}});
    container.erase(2);*/

    return 0;
}
