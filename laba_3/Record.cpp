#include "Record.h"

Record::Record() : FirstKey { }, SecondKey { }, LineNumber { } {}

Record::Record(std::string first, FullNameField second, int number)
        : FirstKey(std::move(first)), SecondKey(std::move(second)), LineNumber(number) {}

bool Record::operator<(const Record& other) const {
    // Сначала сравниваем по первому ключу (убывание)
    if (FirstKey != other.FirstKey) return FirstKey > other.FirstKey;
    // При равенстве — по второму ключу (возрастание)
    return SecondKey < other.SecondKey;
}

bool Record::operator>(const Record& other) const {
    // Сначала сравниваем по первому ключу (убывание)
    if (FirstKey != other.FirstKey) return FirstKey < other.FirstKey;
    // При равенстве — по второму ключу (возрастание)
    return SecondKey > other.SecondKey;
}
