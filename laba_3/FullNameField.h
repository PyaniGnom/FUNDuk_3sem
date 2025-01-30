#ifndef LABA_3_FULLNAMEFIELD_H
#define LABA_3_FULLNAMEFIELD_H


#include <string>
#include <utility>

class FullNameField {
public:
    std::string Surname;
    std::string Name;
    std::string MiddleName;

    FullNameField() = default;
    FullNameField(std::string surname, std::string name, std::string middleName);

    FullNameField& operator=(const std::initializer_list<std::string>& list);

    bool operator==(const FullNameField& otherKey) const;
    bool operator!=(const FullNameField& otherKey) const;
    bool operator<(const FullNameField& otherKey) const;
    bool operator>(const FullNameField& otherKey) const;
};


#endif //LABA_3_FULLNAMEFIELD_H
