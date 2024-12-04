#ifndef LABA_2_FILEHANDLER_H
#define LABA_2_FILEHANDLER_H


#include <boost/regex.hpp>
#include <codecvt>
#include <fmt/color.h>
#include <fstream>
#include <string>
#include "ConsoleColors.h"
#include "Key.h"
#include "RbTree.h"
#include "RegexUtils.h"

class FileHandler {
public:
    explicit FileHandler(const std::string& inputFile, const std::string& outputFile);
    ~FileHandler() = default;

    bool ReadFileIntoTree(RbTree* tree);
    bool WriteTreeIntoFile(RbTree* tree);

private:
    std::string _inputFileName;
    std::string _outputFileName;
};


#endif //LABA_2_FILEHANDLER_H
