#include <fmt/color.h>
#include "LlRbTree.h"

int main() {
    LlRbTree<int, std::string> llRbTree;

    llRbTree.Insert(10, "A");
    llRbTree.Insert(18, "A");
    llRbTree.Insert(7, "A");
    llRbTree.Insert(15, "A");
    llRbTree.Insert(16, "A");
    llRbTree.Insert(30, "A");
    llRbTree.Insert(25, "A");
    llRbTree.Insert(40, "A");
    llRbTree.Insert(60, "A");
    llRbTree.Print();

    std::string preOrder = std::move(llRbTree.GetPreOrderTraversalString());
    fmt::print("\n\n{}\n", preOrder);
    std::string postOrder = std::move(llRbTree.GetPostOrderTraversalString());
    fmt::print("{}\n", postOrder);
    std::string inOrder = std::move(llRbTree.GetInOrderTraversalString());
    fmt::print("{}\n", inOrder);

    return 0;
}
