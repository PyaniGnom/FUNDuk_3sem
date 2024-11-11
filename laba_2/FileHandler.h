#ifndef LABA_2_FILEHANDLER_H
#define LABA_2_FILEHANDLER_H

#include <fstream>
#include <string>
#include <codecvt>
#include <utility>
#include <fmt/color.h>
#include <boost/regex.hpp>
#include "RbTree.h"
#include "Key.h"
#include "RegexUtils.h"
#include "ConsoleColors.h"

class FileHandler {
public:
    explicit FileHandler(std::string fileName) {
        this->_fileName = std::move(fileName);
    }

    ~FileHandler() = default;

    bool ReadFileIntoTree(RbTree& tree) {
        std::ifstream file(_fileName);

        if (!file.is_open()) {
            fmt::print(CONSOLE_RED_COLOR, "\nНе удалось открыть входной файл!\n");
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
                fmt::print(CONSOLE_RED_COLOR, "Невозможно обработать строку №{}: \"{}\"\n",
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
                fmt::print(CONSOLE_RED_COLOR, "Входной ключ в строке №{} некорректен: \"{}\"\n",
                           lineNumber, tempStr);
                continue;
            }

            tree.Insert(tempKey, lineNumber);
        }

        file.close();
        return true;
    }

    bool WriteTreeIntoFile(RbTree& tree) {
        std::ifstream file(_fileName);

        if (!file.is_open()) {
            fmt::print(CONSOLE_RED_COLOR, "\nНе удалось открыть входной файл!\n");
            return false;
        }

        return true;
    }

private:
    std::string _fileName;
};


#endif //LABA_2_FILEHANDLER_H
