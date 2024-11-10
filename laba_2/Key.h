#ifndef LABA_2_KEY_H
#define LABA_2_KEY_H


#include <string>
#include <boost/regex.hpp>
#include "RegexUtils.h"

class Key {
public:
    std::string Surname;
    std::string Name;
    std::string MiddleName;
    std::string StateNumber;

    Key(std::string surname, std::string name, std::string middleName, std::string stateNumber) {
        Surname = std::move(surname);
        Name = std::move(name);
        MiddleName = std::move(middleName);
        StateNumber = std::move(stateNumber);
    }

    Key() : Surname {}, Name {}, MiddleName {}, StateNumber {} {}

    bool operator==(const Key& otherKey) const {
        return Surname == otherKey.Surname && Name == otherKey.Name &&
               MiddleName == otherKey.MiddleName && StateNumber == otherKey.StateNumber;
    }

    bool operator!=(const Key& otherKey) const {
        return !(*this == otherKey);
    }

    bool operator<(const Key& otherKey) const {
        if (Surname != otherKey.Surname) return Surname < otherKey.Surname;
        if (Name != otherKey.Name) return Name < otherKey.Name;
        if (MiddleName != otherKey.MiddleName) return MiddleName < otherKey.MiddleName;
        return StateNumber < otherKey.StateNumber;
    }

    bool operator>(const Key& otherKey) const {
        if (Surname != otherKey.Surname) return Surname > otherKey.Surname;
        if (Name != otherKey.Name) return Name > otherKey.Name;
        if (MiddleName != otherKey.MiddleName) return MiddleName > otherKey.MiddleName;
        return StateNumber > otherKey.StateNumber;
    }

    friend std::ostream& operator<<(std::ostream& os, const Key& key) {
        os << key.Surname << ";" << key.Name << ";" << key.MiddleName << ";" << key.StateNumber << ";";
        return os;
    }

    bool IsValid() {
        if (IsMatch(Pattern::SURNAME, Surname) && IsMatch(Pattern::NAME, Name) &&
            IsMatch(Pattern::MIDDLE_NAME, MiddleName) && IsMatch(Pattern::STATE_NUMBER, StateNumber)) {
            return true;
        }

        return false;
    }

    /*bool IsValid() {
        if (!IsMatch(NAME_PATTERN, Surname)) {
            return false;
        }
        if (!IsMatch(NAME_PATTERN, Name)) {
            return false;
        }
        if (!IsMatch(MIDDLENAME_PATTERN, MiddleName)) {
            return false;
        }
        if (!IsMatch(STATENUMBER_PATTERN, StateNumber)) {
            return false;
        }

        return true;
    }*/
};


#endif //LABA_2_KEY_H
