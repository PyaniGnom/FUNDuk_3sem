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
        int lineNumber = 1;

        while (getline(file, tempStr)) {
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

            tree.Insert(tempKey, lineNumber);
            ++lineNumber;
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
//    constexpr static fmt::text_style CONSOLE_RED_COLOR = fmt::fg(fmt::color::red);
//    const inline static boost::wregex PATTERN = boost::wregex(L"(^([А-ЯЁ][а-яё]{1,29};){2}([А-ЯЁ][а-яё]{1,29}|-| )?;[АВЕКМНОРСТУХ]\\d{3}(?<!000)[АВЕКМНОРСТУХ]{2}\\d{2,3}(?<!00);$)", boost::regex::perl);

    /*static bool IsLineParsed(const std::string& str) {
        std::wstring wide_str = StringToWString(str);

        bool match = boost::regex_match(wide_str, PATTERN);
        return match;
    }

    static std::wstring StringToWString(const std::string& str) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wide_str = converter.from_bytes(str);

        return wide_str;
    }*/
};


#endif //LABA_2_FILEHANDLER_H
