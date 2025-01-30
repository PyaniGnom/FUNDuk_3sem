#include <algorithm>
#include <chrono>
#include <fmt/color.h>
#include <iostream>
#include "ConsoleColors.h"
#include "FileHandler.h"
#include "Sorts.h"

int GetLineCount(int min, int max) {
    int number { };
    std::wstring answer { };
    std::wcin >> answer;

    while (swscanf(answer.c_str(), L"%d", &number) != 1 || number < min || number > max) {
        fmt::print(CONSOLE_RED_COLOR, "Недопустимое количество! ({} <= n <= {})\n", min, max);
        fmt::print(CONSOLE_PROCESS_COLOR, "> ");
        std::wcin >> answer;
    }

    return number;
}

int main() {
    setlocale(LC_ALL, "");

    fmt::print("\nВведите количество строк входного файла:\n");
    fmt::print(CONSOLE_PROCESS_COLOR, "> ");
    int lineCount = GetLineCount(10, 1000000);

    fmt::print(CONSOLE_PROCESS_COLOR, "\nПодождите, идёт считывание информации...\n");

    FileHandler fileHandler("../input.txt", "../output_shaker.txt", "../output_heap.txt");
    Record arrayForShakerSort[lineCount];
    if (!fileHandler.ReadFileIntoArray(arrayForShakerSort, lineCount)) {
        return -1;
    }
    Record arrayForHeapSort[lineCount];
    for (size_t i = 0; i < lineCount; ++i) {
        arrayForHeapSort[i] = arrayForShakerSort[i];
    }

    fmt::print(CONSOLE_DONE_COLOR, "Готово!\n");

//----------------------- Shaker Sort ----------------------------------------------------------------------------------

    fmt::print(CONSOLE_PROCESS_COLOR, "\nПроизводится Шейкерная сортировка...\n");

    auto start = std::chrono::steady_clock::now();
    Sorts::ShakerSort(arrayForShakerSort, lineCount);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> shakerSortTime = end - start;

    fmt::print(CONSOLE_DONE_COLOR, "Готово!\n");
    fmt::print("Итоговое время: {:0.8f} сек\n", shakerSortTime.count());

    fmt::print(CONSOLE_PROCESS_COLOR, "\nЗапись результатов в файл \"output_shaker.txt\"...\n");

    fileHandler.WriteArrayIntoFile(arrayForShakerSort, lineCount, shakerSortTime.count(), true);

    fmt::print(CONSOLE_DONE_COLOR, "Готово!\n");

//----------------------- Heap Sort ------------------------------------------------------------------------------------

    fmt::print(CONSOLE_PROCESS_COLOR, "\nПроизводится Пирамидальная сортировка...\n");

    start = std::chrono::steady_clock::now();
    Sorts::HeapSort(arrayForHeapSort, lineCount);
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> heapSortTime = end - start;

    fmt::print(CONSOLE_DONE_COLOR, "Готово!\n");
    fmt::print("Итоговое время: {:0.8f} сек\n", heapSortTime.count());

    fmt::print(CONSOLE_PROCESS_COLOR, "\nЗапись результатов в файл \"output_heap.txt\"...\n");

    fileHandler.WriteArrayIntoFile(arrayForHeapSort, lineCount, heapSortTime.count(), false);

    fmt::print(CONSOLE_DONE_COLOR, "Готово!\n");

//----------------------- Result block ---------------------------------------------------------------------------------

    fmt::print("\nКак показали себя сортировки на устойчивость:\n");
    fmt::print("Шейкерная — {}\n", Sorts::isStable(arrayForShakerSort, lineCount) ? "устойчивая" : "неустойчивая");
    fmt::print("Пирамидальная — {}\n", Sorts::isStable(arrayForHeapSort, lineCount) ? "устойчивая" : "неустойчивая");

    if (shakerSortTime.count() < heapSortTime.count()) {
        auto time = heapSortTime.count() - shakerSortTime.count();
        fmt::print("\nШейкерная сортировка была быстрее на {:0.8f} сек\n", time);
    }
    else {
        auto time = shakerSortTime.count() - heapSortTime.count();
        fmt::print("\nПирамидальная сортировка была быстрее на {:0.8f} сек\n", time);
    }
}
