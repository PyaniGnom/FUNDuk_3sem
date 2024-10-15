#include <iostream>
#include <random>
#include <fmt/color.h>
#include "List.h"

using namespace std;

const fmt::text_style AQUA_COLOR = fg(fmt::color::aqua);
const fmt::text_style INDIAN_RED_COLOR = fg(fmt::color::indian_red);
const fmt::text_style FOREST_GREEN_COLOR = fg(fmt::color::forest_green);
const int MENU_ITEMS_COUNT = 10;

int RandomGenerator() {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 100);

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
               "9. TBC\n"
               "10. Выход\n"
               "Выберите действие (для выбора просто введите цифру):\n");
    fmt::print(AQUA_COLOR, "> ");
}

int GetVariant(int count) {
    int variant {};
    wstring answer {};
    wcin >> answer;

    while (swscanf(answer.c_str(), L"%d", &variant) != 1 || variant < 1 || variant > count) {
        fmt::print(INDIAN_RED_COLOR, "Такого пункта нет!\n");
        fmt::print(AQUA_COLOR, "> ");
        wcin >> answer;
    }

    return variant;
}

List* CreateList() {
    fmt::print("\nВведите размер списка:\n");
    fmt::print(AQUA_COLOR, "> ");

    wstring answer {};
    wcin >> answer;

    int size {};
    while (swscanf(answer.c_str(), L"%d", &size) != 1 || size < 1) {
        fmt::print(INDIAN_RED_COLOR, "Недопустимый размер!\n");
        fmt::print(AQUA_COLOR, "> ");
        wcin >> answer;
    }

    List* list = new List();
    for (int i = 0; i < size; ++i) {
        list->PushFront(RandomGenerator());
    }
    /*list->PushFront(5);
    list->PushFront(5);
    list->PushFront(3);
    list->PushFront(2);
    list->PushFront(5);
    list->PushFront(1);*/

    return list;
}

void DeleteEntries(List& list) {
    fmt::print("\nВведите значение удаляемых элементов:\n");
    fmt::print(AQUA_COLOR, "> ");

    wstring answer {};
    wcin >> answer;

    int value {};
    while (swscanf(answer.c_str(), L"%d", &value) != 1) {
        fmt::print(INDIAN_RED_COLOR, "Нельзя удалить такие элементы!\n");
        fmt::print(AQUA_COLOR, "> ");
        wcin >> answer;
    }

    list.DeleteAllEntry(value);
}

void DeleteEntriesPrev(List& list) {
    fmt::print("\nВведите значение:\n");
    fmt::print(AQUA_COLOR, "> ");

    wstring answer {};
    wcin >> answer;

    int value {};
    while (swscanf(answer.c_str(), L"%d", &value) != 1) {
        fmt::print(INDIAN_RED_COLOR, "Нельзя удалить такие элементы!\n");
        fmt::print(AQUA_COLOR, "> ");
        wcin >> answer;
    }

    list.DeleteAllEntryPrev(value);
}

void AddListItem(List& list) {
    fmt::print("\nВведите значение элемента (целое число):\n");
    fmt::print(AQUA_COLOR, "> ");

    wstring answer {};
    wcin >> answer;

    int value {};
    while (swscanf(answer.c_str(), L"%d", &value) != 1) {
        fmt::print(INDIAN_RED_COLOR, "Нельзя вставить такой элемент!\n");
        fmt::print(AQUA_COLOR, "> ");
        wcin >> answer;
    }

    list.PushFront(value);
}

int FindElement(List& list) {
    fmt::print("\nВведите значение элемента (целое число):\n");
    fmt::print(AQUA_COLOR, "> ");

    wstring answer {};
    wcin >> answer;

    int value {};
    while (swscanf(answer.c_str(), L"%d", &value) != 1) {
        fmt::print(INDIAN_RED_COLOR, "Нельзя найти такой элемент!\n");
        fmt::print(AQUA_COLOR, "> ");
        wcin >> answer;
    }

    return list.Find(value);
}

int main() {
    setlocale(LC_ALL, "");

    List itemList;
    List itemList2;
    List itemList3;
    int answer;

    do {
        PrintMenu();
        answer = GetVariant(MENU_ITEMS_COUNT);

        switch (answer) {
            case 1:
                if (!itemList.isExist()) {
                    itemList = *CreateList();
                    fmt::print(FOREST_GREEN_COLOR, "\nСписок успешно создан!");

                    fmt::print("\nВ текущем списке следующие элементы:\n");
                    itemList.Print();
                }
                else {
                    fmt::print(INDIAN_RED_COLOR, "\nСписок уже существует!\n");
                }
                break;
            case 2:
                if (itemList.isExist()) {
                    itemList.~List();
                    fmt::print(FOREST_GREEN_COLOR, "\nУдаление успешно!\n");
                }
                else {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                }
                break;
            case 3:
                if (itemList.isExist()) {
                    AddListItem(itemList);

                    fmt::print(FOREST_GREEN_COLOR, "\nДобавление элемента успешно!");
                    fmt::print("\nВ текущем списке следующие элементы:\n");
                    itemList.Print();
                }
                else {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                }
                break;
            case 4:
                if (itemList.isExist()) {
                    DeleteEntries(itemList);

                    if (itemList.isExist()) {
                        fmt::print(FOREST_GREEN_COLOR, "\nУдаление элементов успешно!");
                        fmt::print("\nВ текущем списке следующие элементы:\n");
                        itemList.Print();
                    }
                    else {
                        fmt::print(FOREST_GREEN_COLOR, "\nСписок удалён!\n");
                    }
                }
                else {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                }
                break;
            case 5:
                if (itemList.isExist()) {
                    DeleteEntriesPrev(itemList);

                    if (itemList.isExist()) {
                        fmt::print(FOREST_GREEN_COLOR, "\nУдаление элементов успешно!");
                        fmt::print("\nВ текущем списке следующие элементы:\n");
                        itemList.Print();
                    }
                    else {
                        fmt::print(FOREST_GREEN_COLOR, "\nСписок удалён!\n");
                    }
                }
                else {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                }
                break;
            case 6:
                if (itemList.isExist()) {
                    int index = FindElement(itemList);
                    if (index != -1) {
                        fmt::print(FOREST_GREEN_COLOR, "\nИндекс данного элемента: {}\n", index);
                    }
                    else {
                        fmt::print(INDIAN_RED_COLOR, "\nТакого элемента не найдено!\n");
                    }
                }
                else {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                }
                break;
            case 7:
                if (itemList.isExist()) {
                    fmt::print("\nВ текущем списке следующие элементы:\n");
                    itemList.Print();
                }
                else {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                }
                break;
            case 8:
                if (itemList.isExist()) {
                    fmt::print("\nСоздание второго списка:");
                    itemList2 = *CreateList();
                    fmt::print("\nВ первом списке следующие элементы:\n");
                    itemList.Print();
                    fmt::print("Во втором списке следующие элементы:\n");
                    itemList2.Print();

                    itemList3 = *itemList.Union(itemList2);
                    fmt::print("\nОбъединение успешно!\n");
                    fmt::print("\nВ третьем списке следующие элементы:\n");
                    itemList3.Print();
                }
                else {
                    fmt::print(INDIAN_RED_COLOR, "\nНет существующего списка!\n");
                }
                break;
            case 9:
                fmt::print(INDIAN_RED_COLOR, "\nПока не реализовано!\n");
                break;
            default:
                break;
        }
    } while (answer != 10);

    fmt::print("\nВыход... Удачного дня!\n");

    return 0;
}
