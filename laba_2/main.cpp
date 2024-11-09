#include <fmt/color.h>
#include "RbTree.h"
#include "Key.h"

int main() {
    RbTree rbTree;
    Key key;

    for (int i = 1; i <= 10; ++i) {
        key.Surname = std::string(1, static_cast<char>(65 + i)) + std::string(1, static_cast<char>(70 + i));
        key.Name = std::string(1, static_cast<char>(70 + i)) + std::string(1, static_cast<char>(75 + i));
        key.MiddleName = std::string(1, static_cast<char>(75 + i)) + std::string(1, static_cast<char>(80 + i));
        key.StateNumber = std::to_string(i) + std::string(1, static_cast<char>(65 + i)) + std::string(1, static_cast<char>(80 + i)) + std::to_string(i + 1);
        rbTree.Insert(key, i);
    }

    rbTree.Print();

    return 0;
}
