#include <iostream>
#include <random>
#include <fmt/color.h>
#include "List.h"

constexpr fmt::text_style AQUA_COLOR = fg(fmt::color::aqua);
constexpr fmt::text_style INDIAN_RED_COLOR = fg(fmt::color::indian_red);
constexpr fmt::text_style FOREST_GREEN_COLOR = fg(fmt::color::forest_green);
constexpr int MENU_ITEMS_COUNT = 10;

int GenerateRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}

void PrintMenu() {
    fmt::print("\nМеню:\n"
               "1. Создать список\n"
               "2. Удалить список\n"
               "3. Добавление элемента (в начало)\n"
               "4. Удаление всех вхождений заданного по значению элемента\n"
               "5. Удаление (перед каждым вхождением заданного)\n"
               "6. Поиск заданного элемента по значению\n"
               "7. Распечатать список\n"
               "8. Операция работы с двумя списками (объединение)\n"
               "9. Доп. Операция\n"
               "10. Выход\n"
               "Выберите действие (для выбора просто введите цифру):\n");
    fmt::print(AQUA_COLOR, "> ");
}

int GetMenuNumber(int count) {
    int variant {};
    std::wstring answer {};
    std::wcin >> answer;

    while (swscanf(answer.c_str(), L"%d", &variant) != 1 || variant < 1 || variant > count) {
        fmt::print(INDIAN_RED_COLOR, "Такого пункта нет!\n");
        fmt::print(AQUA_COLOR, "> ");
        std::wcin >> answer;
    }

    return variant;
}

List* CreateList() {
    fmt::print("\nВведите размер списка:\n");
    fmt::print(AQUA_COLOR, "> ");

    std::wstring answer {};
    std::wcin >> answer;

    int size {};
    while (swscanf(answer.c_str(), L"%d", &size) != 1 || size < 1) {
        fmt::print(INDIAN_RED_COLOR, "Недопустимый размер!\n");
        fmt::print(AQUA_COLOR, "> ");
        std::wcin >> answer;
    }

    List* list = new List();
    for (int i = 0; i < size; ++i) {
        list->PushFront(GenerateRandomInt(0, 100));
    }

    return list;
}

int GetNumber(const std::string& failPrompt) {
    fmt::print("\nВведите значение (целое число):\n");
    fmt::print(AQUA_COLOR, "> ");

    std::wstring answer {};
    std::wcin >> answer;

    int value {};
    while (swscanf(answer.c_str(), L"%d", &value) != 1) {
        fmt::print(INDIAN_RED_COLOR, "{}", failPrompt);
        fmt::print(AQUA_COLOR, "> ");
        std::wcin >> answer;
    }

    return value;
}

int main() {
    setlocale(LC_ALL, "");

    List initialList;
    List listForUnion;
    List unionResultList;
    List divisorsList;
    std::string failPrompt {};
    int menuNumber;

    do {
        PrintMenu();
        menuNumber = GetMenuNumber(MENU_ITEMS_COUNT);

        switch (menuNumber) {
            case 1: {
                if (initialList.isExist()) {
                    fmt::print(INDIAN_RED_COLOR, "\nСписок уже существует!\n");
                    break;
                }

                initialList = *CreateList();
                fmt::print(FOREST_GREEN_COLOR, "\nСписок успешно создан!");

                fmt::print("\nВ текущем списке следующие элементы:\n");
                initialList.Print();

                break;
            }
            case 2: {
                if (!initialList.isExist()) {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                    break;
                }

                initialList.~List();
                fmt::print(FOREST_GREEN_COLOR, "\nУдаление успешно!\n");

                break;
            }
            case 3: {
                if (!initialList.isExist()) {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                    break;
                }

                failPrompt = "Нельзя добавить такой элемент!\n";

                initialList.PushFront(GetNumber(failPrompt));
                fmt::print(FOREST_GREEN_COLOR, "\nДобавление элемента успешно!");
                fmt::print("\nВ текущем списке следующие элементы:\n");
                initialList.Print();

                break;
            }
            case 4: {
                if (!initialList.isExist()) {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                    break;
                }

                failPrompt = "Нельзя удалить такие элементы!\n";
                initialList.DeleteAllEntry(GetNumber(failPrompt));

                if (!initialList.isExist()) {
                    fmt::print(FOREST_GREEN_COLOR, "\nСписок удалён!\n");
                    break;
                }

                fmt::print(FOREST_GREEN_COLOR, "\nУдаление элементов успешно!");
                fmt::print("\nВ текущем списке следующие элементы:\n");
                initialList.Print();

                break;
            }
            case 5: {
                if (!initialList.isExist()) {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                    break;
                }

                failPrompt = "Нельзя удалить такие элементы!\n";
                initialList.DeleteAllEntryPrev(GetNumber(failPrompt));

                if (!initialList.isExist()) {
                    fmt::print(FOREST_GREEN_COLOR, "\nСписок удалён!\n");
                    break;
                }

                fmt::print(FOREST_GREEN_COLOR, "\nУдаление элементов успешно!");
                fmt::print("\nВ текущем списке следующие элементы:\n");
                initialList.Print();

                break;
            }
            case 6: {
                if (!initialList.isExist()) {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                    break;
                }

                failPrompt = "Нельзя найти такой элемент!\n";
                int index = initialList.Find(GetNumber(failPrompt));

                if (index < 0) {
                    fmt::print(INDIAN_RED_COLOR, "\nТакого элемента не найдено!\n");
                    break;
                }

                fmt::print(FOREST_GREEN_COLOR, "\nИндекс данного элемента: {}\n", index);

                break;
            }
            case 7: {
                if (!initialList.isExist()) {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                    break;
                }

                fmt::print("\nВ текущем списке следующие элементы:\n");
                initialList.Print();

                break;
            }
            case 8: {
                if (!initialList.isExist()) {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                    break;
                }

                fmt::print("\nСоздание второго списка:");
                listForUnion = *CreateList();
                fmt::print("\nВ первом списке следующие элементы:\n");
                initialList.Print();
                fmt::print("Во втором списке следующие элементы:\n");
                listForUnion.Print();

                unionResultList = *initialList.Union(listForUnion);
                fmt::print("\nОбъединение успешно!\n");
                fmt::print("\nВ третьем списке следующие элементы:\n");
                unionResultList.Print();

                break;
            }
            case 9: {
                initialList.~List();

                fmt::print("Введите количество элементов, которое хотите добавить в новый список:\n");
                fmt::print(AQUA_COLOR, "> ");

                std::wstring answer{};
                std::wcin >> answer;

                int size{};
                while (swscanf(answer.c_str(), L"%d", &size) != 1 || size < 1) {
                    fmt::print(INDIAN_RED_COLOR, "Недопустимый размер!\n");
                    fmt::print(AQUA_COLOR, "> ");
                    std::wcin >> answer;
                }

                failPrompt = "Нельзя добавить такой элемент!\n";
                for (int i = 0; i < size; ++i) {
                    initialList.PushFront(GetNumber(failPrompt));
                }

                fmt::print("\nВ текущем списке следующие элементы:\n");
                initialList.Print();

                divisorsList = *initialList.GetDivisorsList();

                fmt::print("\nВ новом списке следующие элементы:\n");
                divisorsList.Print();

                break;
            }
            default:
                break;
        }
    } while (menuNumber != 10);

    fmt::print("\nВыход... Удачного дня!\n");

    return 0;
}
