#include <chrono>
#include <fmt/color.h>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

int GenerateRandomInt(int min, int max);

int ReadValidNumber(std::string errorMessage, int min, int max);

char ReadSeparatorFromUser(std::string message, std::string errorMessage);

std::vector<std::string> GetVectorFromFile(const std::string& filePath);

std::vector<int> GetRegionVectorFromFile(const std::string& filePath);

std::string GetRandomSurname(bool isMale);

std::string GetRandomName(bool isMale);

std::string GetRandomMiddleName(bool isMale);

std::string GetRandomStateNumber();

std::string GetRandomTime();

enum class GenerationPattern {
    FullNamePlusStateNumber = 1,
    FullNamePlusTime = 2,
    StateNumberPlusFullName = 3,
    TimePlusFullName = 4
};

void GenerateFile(const std::string& filePath, int recordsNumber, GenerationPattern pattern,
                  char columnSep, char fullNameSep, bool isNeedEndOfLineSep);

static std::vector<std::string> LetterVec;
static std::vector<int> RegionVec;
static std::vector<std::string> SurnamesVec;
static std::vector<std::string> MaleNamesVec;
static std::vector<std::string> FemaleNamesVec;
static std::vector<std::string> MiddleNamesVec;

static std::map<int, char> SEPARATOR_MAP = {
        { 1, ';' },
        { 2, '|' },
        { 3, ' ' },
};

constexpr static fmt::text_style CONSOLE_RED_COLOR = fmt::fg(fmt::color::red);
constexpr static fmt::text_style CONSOLE_GREEN_COLOR = fmt::fg(fmt::color::forest_green);
constexpr static fmt::text_style CONSOLE_AQUA_COLOR = fmt::fg(fmt::color::aqua);

int main() {
    setlocale(LC_ALL, "");

    fmt::print(CONSOLE_AQUA_COLOR, "\nПодождите, идёт считывание информации...\n");

    std::string plateLettersDictionaryPath = "../dictionaries/vehicle_registration_plate_letters.txt";
    std::string regionCodesDictionaryPath = "../dictionaries/region_codes.txt";
    std::string surnamesDictionaryPath = "../dictionaries/surnames/surnames.txt";
    std::string maleNamesDictionaryPath = "../dictionaries/names/male.txt";
    std::string femaleNamesDictionaryPath = "../dictionaries/names/female.txt";
    std::string middleNamesDictionaryPath = "../dictionaries/middle_names/middle_names.txt";
    std::string outputFilePath = "../output_file.txt";

    auto letterVec = GetVectorFromFile(plateLettersDictionaryPath);
    LetterVec = std::move(letterVec);
    auto regionVec = GetRegionVectorFromFile(regionCodesDictionaryPath);
    RegionVec = std::move(regionVec);
    auto surnamesVec = GetVectorFromFile(surnamesDictionaryPath);
    SurnamesVec = std::move(surnamesVec);
    auto maleNamesVec = GetVectorFromFile(maleNamesDictionaryPath);
    MaleNamesVec = std::move(maleNamesVec);
    auto femaleNamesVec = GetVectorFromFile(femaleNamesDictionaryPath);
    FemaleNamesVec = std::move(femaleNamesVec);
    auto middleNamesVec = GetVectorFromFile(middleNamesDictionaryPath);
    MiddleNamesVec = std::move(middleNamesVec);

    fmt::print(CONSOLE_GREEN_COLOR, "Готово!\n");

    fmt::print(
            "\nВыберите вариант генерации:\n"
            "1. ФИО + Автомобильный номер (Госномер)\n"
            "2. ФИО + Время (Часы:Минуты)\n"
            "3. Автомобильный номер (Госномер) + ФИО\n"
            "4. Время (Часы:Минуты) + ФИО\n"
    );
    fmt::print(CONSOLE_AQUA_COLOR, "> ");
    auto pattern = (GenerationPattern) ReadValidNumber("Нет такого варианта!\n", 1, 4);

    char columnSeparator = ReadSeparatorFromUser(
            "\nВыберите разделитель для колонок:\n",
            "Нет такого варианта!\n"
    );
    char fullNameSeparator = ReadSeparatorFromUser(
            "\nВыберите разделитель для ФИО:\n",
            "Нет такого варианта!\n"
    );

    fmt::print(
            "\nВставлять в конце строк разделитель для колонок?\n"
            "1. Да\n"
            "2. Нет\n"
    );
    fmt::print(CONSOLE_AQUA_COLOR, "> ");
    bool isNeedEndOfLineSeparator = ReadValidNumber("Нет такого варианта!\n", 1, 2) == 1 ? true : false;

    fmt::print("\nВведите желаемое количество записей в файле:\n");
    fmt::print(CONSOLE_AQUA_COLOR, "> ");
    int recordsNumber = ReadValidNumber("Недопустимое количество!\n", 1, 10000);

    fmt::print(CONSOLE_AQUA_COLOR, "\nЗапись...\n");

    auto start = std::chrono::steady_clock::now();
    GenerateFile(outputFilePath, recordsNumber, pattern,
                 columnSeparator, fullNameSeparator, isNeedEndOfLineSeparator);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = end - start;

    fmt::print(CONSOLE_GREEN_COLOR, "Готово!\n");
    fmt::print("Время генерации файла: {:0.7f} сек\n", elapsedTime.count());

    return 0;
}

void GenerateFile(const std::string& filePath, int recordsNumber, GenerationPattern pattern,
                  char columnSep, char fullNameSep, bool isNeedEndOfLineSep) {
    std::stringstream record;
    bool isMale;

    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("\nНе удалось открыть выходной файл!\n");
    }

    std::string endOfLineSep;
    if (isNeedEndOfLineSep) {
        endOfLineSep = columnSep;
    }
    else {
        endOfLineSep = "";
    }
    switch (pattern) {
        case GenerationPattern::FullNamePlusStateNumber: {
            for (int i = 0; i < recordsNumber; ++i) {
                isMale = GenerateRandomInt(0, 1);
                record << GetRandomSurname(isMale) << fullNameSep;
                record << GetRandomName(isMale) << fullNameSep;
                record << GetRandomMiddleName(isMale) << columnSep;
                record << GetRandomStateNumber() << endOfLineSep << "\n";
                file << record.str();
                record.str("");
                record.clear();
            }
            break;
        }
        case GenerationPattern::FullNamePlusTime: {
            for (int i = 0; i < recordsNumber; ++i) {
                isMale = GenerateRandomInt(0, 1);
                record << GetRandomSurname(isMale) << fullNameSep;
                record << GetRandomName(isMale) << fullNameSep;
                record << GetRandomMiddleName(isMale) << columnSep;
                record << GetRandomTime() << endOfLineSep << "\n";
                file << record.str();
                record.str("");
                record.clear();
            }
            break;
        }
        case GenerationPattern::StateNumberPlusFullName: {
            for (int i = 0; i < recordsNumber; ++i) {
                isMale = GenerateRandomInt(0, 1);
                record << GetRandomStateNumber() << columnSep;
                record << GetRandomSurname(isMale) << fullNameSep;
                record << GetRandomName(isMale) << fullNameSep;
                record << GetRandomMiddleName(isMale) << endOfLineSep << "\n";
                file << record.str();
                record.str("");
                record.clear();
            }
            break;
        }
        case GenerationPattern::TimePlusFullName: {
            for (int i = 0; i < recordsNumber; ++i) {
                isMale = GenerateRandomInt(0, 1);
                record << GetRandomTime() << columnSep;
                record << GetRandomSurname(isMale) << fullNameSep;
                record << GetRandomName(isMale) << fullNameSep;
                record << GetRandomMiddleName(isMale) << endOfLineSep << "\n";
                file << record.str();
                record.str("");
                record.clear();
            }
            break;
        }
    }

    file.close();
}

std::vector<std::string> GetVectorFromFile(const std::string& filePath) {
    std::vector<std::string> vec;
    std::string str;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("\nНе удалось открыть входной файл!\n");
    }

    while (getline(file, str)) {
        std::erase(str, '\r');
        std::erase(str, ' ');
        if (str.empty() || str[0] == '#') continue;

        vec.emplace_back(str);
    }

    file.close();

    std::sort(vec.begin(), vec.end());

    return vec;
}

std::vector<int> GetRegionVectorFromFile(const std::string& filePath) {
    std::vector<int> vec;
    std::string code;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("\nНе удалось открыть входной файл!\n");
    }

    while (getline(file, code)) {
        std::erase(code, '\r');
        std::erase(code, ' ');
        if (code.empty() || code[0] == '#') continue;

        vec.emplace_back(std::stoi(code));
    }

    file.close();

    std::sort(vec.begin(), vec.end());
    auto last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());

    return vec;
}

std::string GetRandomSurname(bool isMale) {
    std::string surname;

    surname = SurnamesVec[GenerateRandomInt(0, static_cast<int>(SurnamesVec.size()) - 1)];
    if (!isMale) {
        surname.append("а");
    }

    return surname;
}

std::string GetRandomName(bool isMale) {
    std::string name;

    if (isMale) {
        name = MaleNamesVec[GenerateRandomInt(0, static_cast<int>(MaleNamesVec.size()) - 1)];
    }
    else {
        name = FemaleNamesVec[GenerateRandomInt(0, static_cast<int>(FemaleNamesVec.size()) - 1)];
    }

    return name;
}

std::string GetRandomMiddleName(bool isMale) {
    std::string middleName;

    middleName = MiddleNamesVec[GenerateRandomInt(0, static_cast<int>(MiddleNamesVec.size()) - 1)];
    if (isMale) {
        middleName.erase(middleName.find('/'), middleName.length());
    }
    else {
        middleName.erase(0, middleName.find('/') + 1);
    }

    return middleName;
}

std::string GetRandomStateNumber() {
    std::string stateNumber;

    stateNumber = LetterVec[GenerateRandomInt(0, static_cast<int>(LetterVec.size()) - 1)];

    std::string tempStr = std::to_string(GenerateRandomInt(1, 999));
    while (tempStr.length() < 3) {
        tempStr.insert(0, "0");
    }
    stateNumber.append(tempStr);

    for (int i = 0; i < 2; ++i) {
        stateNumber.append(LetterVec[GenerateRandomInt(0, static_cast<int>(LetterVec.size()) - 1)]);
    }

    tempStr = std::to_string(RegionVec[GenerateRandomInt(0, static_cast<int>(RegionVec.size()) - 1)]);
    while (tempStr.length() < 2) {
        tempStr.insert(0, "0");
    }
    stateNumber.append(tempStr);

    return stateNumber;
}

std::string GetRandomTime() {
    std::string time;

    std::string tempStr = std::to_string(GenerateRandomInt(0, 23));
    if (tempStr.length() == 1) {
        tempStr.insert(0, "0");
    }
    time.append(tempStr);
    time.append(":");

    tempStr = std::to_string(GenerateRandomInt(0, 59));
    if (tempStr.length() == 1) {
        tempStr.insert(0, "0");
    }
    time.append(tempStr);

    return time;
}

int ReadValidNumber(std::string errorMessage, int min, int max) {
    int number { };
    std::wstring answer { };
    std::wcin >> answer;

    while (swscanf(answer.c_str(), L"%d", &number) != 1 || number < min || number > max) {
        fmt::print(CONSOLE_RED_COLOR, "{}", errorMessage);
        fmt::print(CONSOLE_AQUA_COLOR, "> ");
        std::wcin >> answer;
    }

    return number;
}

char ReadSeparatorFromUser(std::string message, std::string errorMessage) {
    fmt::print("{}", message);
    for (auto it: SEPARATOR_MAP) {
        fmt::print("{0}. \"{1}\"\n", it.first, it.second);
    }
    fmt::print(CONSOLE_AQUA_COLOR, "> ");

    int number { };
    std::wstring answer { };
    std::wcin >> answer;

    while (swscanf(answer.c_str(), L"%d", &number) != 1 || number < 1 || number > SEPARATOR_MAP.size()) {
        fmt::print(CONSOLE_RED_COLOR, "{}", errorMessage);
        fmt::print(CONSOLE_AQUA_COLOR, "> ");
        std::wcin >> answer;
    }

    return SEPARATOR_MAP[number];
}

int GenerateRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}
