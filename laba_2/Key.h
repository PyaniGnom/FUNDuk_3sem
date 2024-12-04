#ifndef LABA_2_KEY_H
#define LABA_2_KEY_H


#include <string>
#include <utility>
#include "RegexUtils.h"

class Key {
public:
    std::string Surname;
    std::string Name;
    std::string MiddleName;
    std::string StateNumber;

    Key();

    bool operator==(const Key& otherKey) const;
    bool operator!=(const Key& otherKey) const;
    bool operator<(const Key& otherKey) const;
    bool operator>(const Key& otherKey) const;
    friend std::ostream& operator<<(std::ostream& os, const Key& key);

    bool IsValid();
};


#endif //LABA_2_KEY_H
