#include "FileHandler.h"

FileHandler::FileHandler(const std::string &inputFile, const std::string &outputFile) {
    this->_inputFileName = inputFile;
    this->_outputFileName = outputFile;
}

bool FileHandler::ReadFileIntoTree(RbTree *tree) {
    std::ifstream file(_inputFileName);

    if (!file.is_open()) {
        fmt::print(CONSOLE_FAIL_COLOR, "\nНе удалось открыть входной файл!\n");
        return false;
    }

    Key tempKey;
    std::string tempStr {};
    int lineNumber {};

    while (getline(file, tempStr)) {
        ++lineNumber;
        if (tempStr.empty() || tempStr[0] == '#') continue;
        erase(tempStr, '\r');
        erase(tempStr, ' ');

        if (!IsMatch(Pattern::FILE_STRING, tempStr)) {
            fmt::print(CONSOLE_FAIL_COLOR, "Невозможно обработать строку №{}: \"{}\"\n",
                       lineNumber, tempStr);
            continue;
        }

        tempKey.Surname = tempStr.substr(0, tempStr.find(';'));
        tempStr.erase(0, tempStr.find(';') + 1);
        tempKey.Name = tempStr.substr(0, tempStr.find(';'));
        tempStr.erase(0, tempStr.find(';') + 1);
        tempKey.MiddleName = tempStr.substr(0, tempStr.find(';'));
        tempStr.erase(0, tempStr.find(';') + 1);
        tempKey.StateNumber = tempStr.substr(0, tempStr.find(';'));

        if (!tempKey.IsValid()) {
            fmt::print(CONSOLE_FAIL_COLOR, "Входной ключ в строке №{} некорректен: \"{}\"\n",
                       lineNumber, tempStr);
            continue;
        }

        tree->Insert(tempKey, lineNumber);
    }

    file.close();
    return true;
}

bool FileHandler::WriteTreeIntoFile(RbTree *tree) {
    std::ofstream file(_outputFileName);

    if (!file.is_open()) {
        fmt::print(CONSOLE_FAIL_COLOR, "\nНе удалось открыть входной файл!\n");
        return false;
    }

    auto traversal = tree->GetPostOrderTraversal();
    file << traversal.str();

    file.close();
    return true;
}
