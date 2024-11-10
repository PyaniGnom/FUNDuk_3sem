#include <random>
#include <fmt/color.h>
#include "RbTree.h"
#include "Key.h"
#include "FileHandler.h"
#include "ConsoleColors.h"

int RandomGenerator(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}

int main() {
    RbTree rbTree;

    FileHandler fileHandler("../input_file.txt");
    fileHandler.ReadFileIntoTree(rbTree);
    rbTree.Print();


//    auto stream = rbTree.GetPostOrderTraversal();
//    fmt::print("\nОбратный обход дерева:\n{}", stream.str());

    return 0;
}
