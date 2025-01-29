#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <fmt/color.h>

int GenerateRandomInt(int min, int max);
int GetRecordsNumber(int maxNumber);
std::vector<std::string> GetVectorFromFile(const std::string& fileName);
std::vector<int> GetRegionVector(const std::string& fileName);

std::string GetRandomSurname(bool isMale);
std::string GetRandomName(bool isMale);
std::string GetRandomMiddleName(bool isMale);
std::string GetRandomStateNumber();
void GenerateFile(const std::string& fileName, int recordsNumber);

static std::vector<std::string> LetterVec;
static std::vector<int> RegionVec;
static std::vector<std::string> SurnamesVec;
static std::vector<std::string> MaleNamesVec;
static std::vector<std::string> FemaleNamesVec;
static std::vector<std::string> MiddleNamesVec;

constexpr static fmt::text_style CONSOLE_RED_COLOR = fmt::fg(fmt::color::red);
constexpr static fmt::text_style CONSOLE_GREEN_COLOR = fmt::fg(fmt::color::forest_green);
constexpr static fmt::text_style CONSOLE_AQUA_COLOR = fmt::fg(fmt::color::aqua);

int main() {
    setlocale(LC_ALL, "");

    fmt::print(CONSOLE_AQUA_COLOR, "Подождите, идёт считывание информации...\n");

    auto letterVec = GetVectorFromFile("../license_plate_letters.txt");
    LetterVec = std::move(letterVec);
    auto regionVec = GetRegionVector("../region_codes.txt");
    RegionVec = std::move(regionVec);
    auto surnamesVec = GetVectorFromFile("../surnames.txt");
    SurnamesVec = std::move(surnamesVec);
    auto maleNamesVec = GetVectorFromFile("../male_names.txt");
    MaleNamesVec = std::move(maleNamesVec);
    auto femaleNamesVec = GetVectorFromFile("../female_names.txt");
    FemaleNamesVec = std::move(femaleNamesVec);
    auto middleNamesVec = GetVectorFromFile("../middle_names.txt");
    MiddleNamesVec = std::move(middleNamesVec);

    fmt::print(CONSOLE_GREEN_COLOR, "Готово!\n");

    fmt::print("\nВведите желаемое количество записей в файле:\n");
    fmt::print(CONSOLE_AQUA_COLOR, "> ");
    int recordsNumber = GetRecordsNumber(10000);

    fmt::print(CONSOLE_AQUA_COLOR, "\nЗапись...\n");

    GenerateFile("../output_file.txt", recordsNumber);

    fmt::print(CONSOLE_GREEN_COLOR, "Готово!\n");

    return 0;
}

void GenerateFile(const std::string& fileName, int recordsNumber) {
    std::stringstream record;
    bool isMale;

    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("\nНе удалось открыть выходной файл!\n");
    }

    for (int i = 0; i < recordsNumber; ++i) {
        isMale = GenerateRandomInt(0, 1);
        record << GetRandomSurname(isMale) << ";";
        record << GetRandomName(isMale) << ";";
        record << GetRandomMiddleName(isMale) << ";";
        record << GetRandomStateNumber() << ";\n";
        file << record.str();
        record.str("");
        record.clear();
    }

    file.close();
}

std::vector<std::string> GetVectorFromFile(const std::string& fileName) {
    std::vector<std::string> vec;
    std::string str;

    std::ifstream file(fileName);
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

std::vector<int> GetRegionVector(const std::string& fileName) {
    std::vector<int> vec;
    std::string code;

    std::ifstream file(fileName);
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

int GetRecordsNumber(int maxNumber) {
    int number {};
    std::wstring answer {};
    std::wcin >> answer;

    while (swscanf(answer.c_str(), L"%d", &number) != 1 || number < 1 || number > maxNumber) {
        fmt::print(CONSOLE_RED_COLOR, "Недопустимое количество!\n");
        fmt::print(CONSOLE_AQUA_COLOR, "> ");
        std::wcin >> answer;
    }

    return number;
}

int GenerateRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}
