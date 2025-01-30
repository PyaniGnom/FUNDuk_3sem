#include "FileHandler.h"

FileHandler::FileHandler(const std::string& input, const std::string& shakerOutput, const std::string& heapOutput) {
    this->inputFileName = input;
    this->shakerOutputFileName = shakerOutput;
    this->heapOutputFileName = heapOutput;
}

bool FileHandler::ReadFileIntoArray(Record* arr, int fileSize) {
    std::ifstream file(inputFileName);

    if (!file.is_open()) {
        fmt::print(CONSOLE_FAIL_COLOR, "\nНе удалось открыть входной файл!\n");
        return false;
    }

    Record tempRecord;
    std::string line { };

    for (int i = 0; i < fileSize; ++i) {
        getline(file, line);
        erase(line, '\r');
        erase(line, ' ');

        const size_t pipePos = line.find('|');
        const size_t semi1Pos = line.find(';', pipePos + 1);
        const size_t semi2Pos = line.find(';', semi1Pos + 1);

        arr[i] = Record(
                line.substr(0, pipePos),
                FullNameField(
                        line.substr(pipePos + 1, semi1Pos - pipePos - 1),
                        line.substr(semi1Pos + 1, semi2Pos - semi1Pos - 1),
                        line.substr(semi2Pos + 1)
                ),
                i + 1
        );
    }

    file.close();
    return true;
}

bool FileHandler::WriteArrayIntoFile(Record* arr, int size, double time, bool isShakerSort) {
    std::ofstream file(isShakerSort ? shakerOutputFileName : heapOutputFileName);

    if (!file.is_open()) {
        fmt::print(CONSOLE_FAIL_COLOR, "\nНе удалось открыть выходной файл!\n");
        return false;
    }

    for (int i = 0; i < size; ++i) {
        file << arr[i].FirstKey << " | "
             << arr[i].SecondKey.Surname << " "
             << arr[i].SecondKey.Name << " "
             << arr[i].SecondKey.MiddleName << " | "
             << arr[i].LineNumber << "\n";
    }

    file << "\nВремя, затраченное на сортировку: " << time;

    file.close();
    return true;
}
