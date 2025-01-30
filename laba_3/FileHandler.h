#ifndef LABA_3_FILEHANDLER_H
#define LABA_3_FILEHANDLER_H


#include <fmt/color.h>
#include <fstream>
#include <string>
#include "ConsoleColors.h"
#include "Record.h"

class FileHandler {
public:
    FileHandler(const std::string& input, const std::string& shakerOutput, const std::string& heapOutput);

    bool ReadFileIntoArray(Record arr[], int fileSize);

    bool WriteArrayIntoFile(Record arr[], int size, double time, bool isShakerSort);

private:
    std::string inputFileName;
    std::string shakerOutputFileName;
    std::string heapOutputFileName;
};


#endif //LABA_3_FILEHANDLER_H
