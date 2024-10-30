#include <fmt/color.h>
#include "LlRbTree.h"

int main() {
    LlRbTree llRbTree;

    llRbTree.Insert(10, "AGF");
    llRbTree.Insert(18, "JGHA");
    llRbTree.Insert(7, "URY");
    llRbTree.Insert(15, "OIG");
    llRbTree.Insert(16, "ZLJD");
    llRbTree.Insert(30, "YTERQ");
    llRbTree.Insert(25, "PYKG");
    llRbTree.Insert(40, "JGHHW");
    llRbTree.Insert(60, "GPOR");
    llRbTree.Print();

    std::string preOrder = std::move(llRbTree.GetPreOrderTraversalString());
    fmt::print("\n{}\n", preOrder);
    std::string postOrder = std::move(llRbTree.GetPostOrderTraversalString());
    fmt::print("{}\n", postOrder);
    std::string inOrder = std::move(llRbTree.GetInOrderTraversalString());
    fmt::print("{}\n\n", inOrder);

    auto find1 = llRbTree.Find(30);
    auto find2 = llRbTree.Find(80);


    LlRbTree llRbTree2;

    for (int i = 1; i <= 10; ++i) {
        llRbTree2.Insert(i * i, std::string(1, static_cast<char>(65 + i)) +
                std::string(1, static_cast<char>(75 + i)));
    }

    llRbTree2.Print();
    fmt::print("\n");
    llRbTree.Clear();
    llRbTree.Print();
    fmt::print("\n");
    llRbTree2.Print();
    fmt::print("\n");

    return 0;
}
