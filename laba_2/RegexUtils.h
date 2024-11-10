#ifndef LABA_2_REGEXUTILS_H
#define LABA_2_REGEXUTILS_H


#include <string>
#include <codecvt>
#include <unordered_map>
#include <boost/regex.hpp>

const inline static boost::wregex NAME_PATTERN = boost::wregex(L"(^[А-ЯЁ][а-яё]{1,29}$)", boost::regex::perl);
const inline static boost::wregex MIDDLE_NAME_PATTERN = boost::wregex(L"(^([А-ЯЁ][а-яё]{1,29}|-| )?$)", boost::regex::perl);
const inline static boost::wregex STATE_NUMBER_PATTERN = boost::wregex(L"(^[АВЕКМНОРСТУХ]\\d{3}(?<!000)[АВЕКМНОРСТУХ]{2}\\d{2,3}(?<!00)$)", boost::regex::perl);
const inline static boost::wregex FILE_STRING_PATTERN = boost::wregex(L"(^(.+;){2}.*;.+;$)", boost::regex::perl);

enum class Pattern {
    SURNAME,
    NAME,
    MIDDLE_NAME,
    STATE_NUMBER,
    FILE_STRING
};

const std::unordered_map<Pattern, const boost::wregex&> patternMap = {
        {Pattern::SURNAME, NAME_PATTERN},
        {Pattern::NAME, NAME_PATTERN},
        {Pattern::MIDDLE_NAME, MIDDLE_NAME_PATTERN},
        {Pattern::STATE_NUMBER, STATE_NUMBER_PATTERN},
        {Pattern::FILE_STRING, FILE_STRING_PATTERN}
};

static std::wstring StringToWString(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_str = converter.from_bytes(str);

    return wide_str;
}

static bool IsMatch(const Pattern pattern, const std::string& str) {
    auto it = patternMap.find(pattern);

    if (it != patternMap.end()) {
        std::wstring wide_str = StringToWString(str);
        return boost::regex_match(wide_str, it->second);
    }

    return false;
}

/*static bool IsMatch(const boost::wregex& pattern, const std::string& str) {
    std::wstring wide_str = StringToWString(str);

    bool match = boost::regex_match(wide_str, pattern);
    return match;
}

static bool IsMatch(const Pattern pattern, const std::string& str) {
    std::wstring wide_str = StringToWString(str);

    bool match;
    if (pattern == Pattern::SURNAME || pattern == Pattern::NAME) {
        match = boost::regex_match(wide_str, NAME_PATTERN);
    }
    else if (pattern == Pattern::MIDDLE_NAME) {
        match = boost::regex_match(wide_str, MIDDLE_NAME_PATTERN);
    }
    else if (pattern == Pattern::STATE_NUMBER) {
        match = boost::regex_match(wide_str, STATE_NUMBER_PATTERN);
    }
    else if (pattern == Pattern::FILE_STRING) {
        match = boost::regex_match(wide_str, FILE_STRING_PATTERN);
    }
    else {
        match = false;
    }

    return match;
}*/

#endif //LABA_2_REGEXUTILS_H
