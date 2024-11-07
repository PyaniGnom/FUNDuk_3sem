#include <fmt/color.h>
#include "LlRbTree.h"
#include "RbTree.h"

int main() {
    RbTree rbTree;

    rbTree.Insert(10, "AGF");
    rbTree.Insert(18, "JGHA");
    rbTree.Insert(7, "URY");
    rbTree.Insert(15, "OIG");
    rbTree.Insert(16, "ZLJD");
    rbTree.Insert(30, "YTERQ");
    rbTree.Insert(25, "PYKG");
    rbTree.Insert(40, "JGHHW");
    rbTree.Insert(60, "GPOR");

    /*for (int i = 1; i <= 20; ++i) {
        rbTree.Insert(i * i, std::string(1, static_cast<char>(65 + i)) +
                                           std::string(1, static_cast<char>(75 + i)));
    }*/

    rbTree.Print();
    rbTree.Erase(16);
    rbTree.Print();
    rbTree.Erase(15);
    rbTree.Print();

    /*LlRbTree llRbTree;

    for (int i = 1; i <= 20; ++i) {
        llRbTree.Insert(i * i, std::string(1, static_cast<char>(65 + i)) +
                                std::string(1, static_cast<char>(75 + i)));
    }
    llRbTree.Print();

    llRbTree.Erase(64);
    llRbTree.Print();

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

    llRbTree.Erase(10);
    llRbTree.Print();

    std::string preOrder = std::move(llRbTree.GetPreOrderTraversalString());
    fmt::print("\n{}\n", preOrder);
    std::string postOrder = std::move(llRbTree.GetPostOrderTraversalString());
    fmt::print("{}\n", postOrder);
    std::string inOrder = std::move(llRbTree.GetInOrderTraversalString());
    fmt::print("{}\n\n", inOrder);

    auto find1 = llRbTree.Find(30);
    auto find2 = llRbTree.Find(80);*/

    return 0;
}
