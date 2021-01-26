#include "ParseFile.h"
#include "TransformInputString.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << std::endl << argv[0] << " input_file output_file" << std::endl;
        return -1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cout << "Wrong input file name" << std::endl;
        return -2;
    }
    std::string fileContent((std::istreambuf_iterator<char>(inputFile)),
            std::istreambuf_iterator<char>());
    inputFile.close();

    std::ofstream out(argv[2]);
    if (!out.is_open()) {
        std::cout << "Wrong output file name" << std::endl;
        return -3;
    }

    std::map<std::string, size_t> dictionaryWords;
    std::string letterString;

    if (ParseFile::ParseFileInputFile(fileContent, letterString, dictionaryWords)) {
        std::cout << "Wrong input file format" << std::endl;
        return -4;
    }

    TransformInputString transformInputString(new GEditDistance());

    transformInputString.TransformInputLetterString(letterString, dictionaryWords);

    out << letterString;
    out.close();

    return 0;
}