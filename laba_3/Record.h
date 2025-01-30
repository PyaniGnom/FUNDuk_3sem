#ifndef LABA_3_RECORD_H
#define LABA_3_RECORD_H


#include <utility>
#include "FullNameField.h"

class Record {
public:
    std::string FirstKey;       // Первый ключ — Госномер
    FullNameField SecondKey;    // Второй ключ — ФИО
    int LineNumber;             // Номер строки входного файла

    Record();
    Record(std::string first, FullNameField second, int number);

    bool operator<(const Record& other) const;
    bool operator>(const Record& other) const;
};


#endif //LABA_3_RECORD_H
