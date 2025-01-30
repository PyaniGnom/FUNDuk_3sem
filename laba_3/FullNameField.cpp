#include "FullNameField.h"

FullNameField::FullNameField(std::string surname, std::string name, std::string middleName)
        : Surname(std::move(surname)), Name(std::move(name)), MiddleName(std::move(middleName)) {}

FullNameField& FullNameField::operator=(const std::initializer_list<std::string>& list) {
    auto it = list.begin();
    Surname = *it++;
    Name = *it++;
    MiddleName = *it;
    return *this;
}

bool FullNameField::operator==(const FullNameField& otherKey) const {
    return Surname == otherKey.Surname && Name == otherKey.Name && MiddleName == otherKey.MiddleName;
}

bool FullNameField::operator!=(const FullNameField& otherKey) const {
    return !(*this == otherKey);
}

bool FullNameField::operator<(const FullNameField& otherKey) const {
    if (Surname != otherKey.Surname) return Surname < otherKey.Surname;
    if (Name != otherKey.Name) return Name < otherKey.Name;
    return MiddleName < otherKey.MiddleName;
}

bool FullNameField::operator>(const FullNameField& otherKey) const {
    if (Surname != otherKey.Surname) return Surname > otherKey.Surname;
    if (Name != otherKey.Name) return Name > otherKey.Name;
    return MiddleName > otherKey.MiddleName;
}
