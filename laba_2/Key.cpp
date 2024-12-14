#include "Key.h"

Key::Key() : Surname { }, Name { }, MiddleName { }, StateNumber { } {}

bool Key::operator==(const Key& otherKey) const {
    return Surname == otherKey.Surname && Name == otherKey.Name &&
           MiddleName == otherKey.MiddleName && StateNumber == otherKey.StateNumber;
}

bool Key::operator!=(const Key& otherKey) const {
    return !(*this == otherKey);
}

bool Key::operator<(const Key& otherKey) const {
    if (Surname != otherKey.Surname) return Surname < otherKey.Surname;
    if (Name != otherKey.Name) return Name < otherKey.Name;
    if (MiddleName != otherKey.MiddleName) return MiddleName < otherKey.MiddleName;
    return StateNumber < otherKey.StateNumber;
}

bool Key::operator>(const Key& otherKey) const {
    if (Surname != otherKey.Surname) return Surname > otherKey.Surname;
    if (Name != otherKey.Name) return Name > otherKey.Name;
    if (MiddleName != otherKey.MiddleName) return MiddleName > otherKey.MiddleName;
    return StateNumber > otherKey.StateNumber;
}

std::ostream& operator<<(std::ostream& os, const Key& key) {
    os << key.Surname << ";" << key.Name << ";" << key.MiddleName << ";" << key.StateNumber << ";";
    return os;
}

bool Key::IsValid() {
    if (IsMatch(Pattern::SURNAME, Surname) && IsMatch(Pattern::NAME, Name) &&
        IsMatch(Pattern::MIDDLE_NAME, MiddleName) && IsMatch(Pattern::STATE_NUMBER, StateNumber)) {
        return true;
    }

    return false;
}
