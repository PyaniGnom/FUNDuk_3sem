#include <fmt/color.h>
#include <iostream>
#include <random>
#include <utility>
#include "ConsoleColors.h"
#include "FileHandler.h"
#include "Key.h"
#include "RbTree.h"

constexpr int MENU_ITEMS_COUNT = 9;

void PrintMenu();
int GetNumberInput(int min, int max, const std::string& failPrompt);
Key GetKey();
Key GetKeyInput();

int main() {
    setlocale(LC_ALL, "");

    auto* rbTree = new RbTree();
    int menuNumber;
    std::string failPrompt {};
    FileHandler fileHandler("../input_file.txt", "../output_file.txt");

    fmt::print(CONSOLE_PROCESS_COLOR, "Считывание информации из файла в дерево...\n");
    if (!fileHandler.ReadFileIntoTree(rbTree)) {
        return -1;
    }
    fmt::print(CONSOLE_DONE_COLOR, "Готово!\n");

    do {
        PrintMenu();
        failPrompt = "Такого пункта нет!\n";
        menuNumber = GetNumberInput(1, MENU_ITEMS_COUNT, failPrompt);

        switch (menuNumber) {
            case 1: {   // Инициализация
                if (rbTree != nullptr) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nДерево уже существует!\n");
                    break;
                }

                rbTree = new RbTree();
                fmt::print(CONSOLE_DONE_COLOR, "\nДерево успешно инициализировано!\n");

                break;
            }
            case 2: {   // Добавление эл-та
                if (rbTree == nullptr) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nНет существующего дерева!\n");
                    break;
                }

                fmt::print("\nДля добавления элемента, заполните поля ключа:\n");
                Key key = GetKey();

                fmt::print("\nДля добавления элемента, введите значение:\n");
                fmt::print(CONSOLE_PROCESS_COLOR, "> ");
                failPrompt = "Некорректное значение!\n";
                int value = GetNumberInput(1, 1000, failPrompt);

                if (!rbTree->Insert(std::move(key), value)) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nЭлемент с таким ключом уже существует в дереве!\n");
                    break;
                }
                fmt::print(CONSOLE_DONE_COLOR, "\nДобавление элемента успешно!\n");

                break;
            }
            case 3: {   // Удаление эл-та
                if (rbTree == nullptr) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nНет существующего дерева!\n");
                    break;
                }
                else if (!rbTree->IsExist()) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nВ дереве нет элементов!\n");
                    break;
                }

                fmt::print("\nДля удаления элемента, заполните поля ключа:\n");
                Key key = GetKey();

                fmt::print("\nДля удаления элемента, введите значение:\n");
                failPrompt = "Некорректное значение!\n";
                int value = GetNumberInput(1, 1000, failPrompt);

                if (!rbTree->Erase(key, value)) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nЭлемент не найден. Удаление не произведено!\n");
                    break;
                }
                fmt::print(CONSOLE_DONE_COLOR, "\nУдаление элемента успешно!\n");

                break;
            }
            case 4: {   // Поиск эл-та
                if (rbTree == nullptr) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nНет существующего дерева!\n");
                    break;
                }
                else if (!rbTree->IsExist()) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nВ дереве нет элементов!\n");
                    break;
                }

                fmt::print("\nДля поиска элемента, заполните поля ключа:\n");
                Key key = GetKey();
                int result = rbTree->Find(key);
                if (result == -1) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nТакого элемента не существует!\n");
                    break;
                }

                fmt::print(CONSOLE_DONE_COLOR, "\nЭлемент найден со значением: ");
                fmt::print("{}\n", result);

                break;
            }
            case 5: {   // Печать
                if (rbTree == nullptr) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nНет существующего дерева!\n");
                    break;
                }
                else if (!rbTree->IsExist()) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nВ дереве нет элементов!\n");
                    break;
                }

                fmt::print("\nВ текущем дереве следующие элементы:\n");
                rbTree->Print();

                break;
            }
            case 6: {   // Обход
                if (rbTree == nullptr) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nНет существующего дерева!\n");
                    break;
                }
                else if (!rbTree->IsExist()) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nВ дереве нет элементов!\n");
                    break;
                }

                auto stream = rbTree->GetPostOrderTraversal();
                fmt::print("\nОбратный обход дерева:\n"
                           "{}", stream.str());

                break;
            }
            case 7: {   // Удаление дерева
                if (rbTree == nullptr) {
                    fmt::print(CONSOLE_FAIL_COLOR, "\nНет существующего дерева!\n");
                    break;
                }

                delete rbTree;
                rbTree = nullptr;
                fmt::print(CONSOLE_DONE_COLOR, "\nУдаление успешно!\n");

                break;
            }
            case 8: {
                fmt::print(CONSOLE_FAIL_COLOR, "\nНе реализовано!\n");

                break;
            }
            default: {
                break;
            }
        }
    } while (menuNumber != MENU_ITEMS_COUNT);

    fmt::print(CONSOLE_PROCESS_COLOR, "\nЗапись информации из дерева в файл...\n");
    if (!fileHandler.WriteTreeIntoFile(rbTree)) {
        return -1;
    }
    fmt::print(CONSOLE_DONE_COLOR, "Готово!\n");

    fmt::print("\nВыход... Удачного дня!\n");
    delete rbTree;

    return 0;
}

void PrintMenu() {
    fmt::print("\nМеню:\n"
               "1. Инициализация дерева\n"
               "2. Добавление элемента\n"
               "3. Удаление элемента\n"
               "4. Поиск элемента\n"
               "5. Печать дерева\n"
               "6. Обратный обход дерева\n"
               "7. Удаление дерева\n"
               "8. TBC\n"
               "9. Выход\n"
               "Выберите действие (для выбора просто введите цифру):\n");
    fmt::print(CONSOLE_PROCESS_COLOR, "> ");
}

int GetNumberInput(int min, int max, const std::string& failPrompt) {
    int variant {};
    std::wstring answer {};
    std::wcin >> answer;

    while (swscanf(answer.c_str(), L"%d", &variant) != 1 || variant < min || variant > max) {
        fmt::print(CONSOLE_FAIL_COLOR, "{}", failPrompt);
        fmt::print(CONSOLE_PROCESS_COLOR, "> ");
        std::wcin >> answer;
    }

    return variant;
}

Key GetKey() {
    Key key = GetKeyInput();

    while (!key.IsValid()) {
        fmt::print(CONSOLE_FAIL_COLOR, "\nВведённый ключ некорректен! Повторите ещё раз!\n\n");
        key = GetKeyInput();
    }

    return key;
}

Key GetKeyInput() {
    Key key;
    std::wstring tempStr;

    fmt::print("Введите Фамилию: ");
    std::wcin >> tempStr;
    key.Surname = WStringToString(tempStr);
    fmt::print("Введите Имя: ");
    std::wcin >> tempStr;
    key.Name = WStringToString(tempStr);
    fmt::print("Введите Отчество: ");
    std::wcin >> tempStr;
    key.MiddleName = WStringToString(tempStr);
    fmt::print("Введите Госномер: ");
    std::wcin >> tempStr;
    key.StateNumber = WStringToString(tempStr);

    return key;
}
