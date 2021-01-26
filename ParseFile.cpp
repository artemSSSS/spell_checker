#include "ParseFile.h" 

enum {
    NO_SEPARATOR, FIRST_SEPARATOR, SECOND_SEPARATOR
};

int ParseFile::ParseFileInputFile(const std::string& fileContent, std::string& letterStirng,
        std::map<std::string, size_t>& dictionaryWords) {
    std::istringstream iss(fileContent);

    int state = NO_SEPARATOR;
    std::stringstream dictionaryStream, letterStream;

    std::string line;
    while (std::getline(iss, line)) {
        if (line.find("===") != std::string::npos) {
            if (state == NO_SEPARATOR) {
                state = FIRST_SEPARATOR;
            } else if (state == FIRST_SEPARATOR) {
                state = SECOND_SEPARATOR;
            }
        } else {
            if (state == NO_SEPARATOR) {
                dictionaryStream << line << std::endl;
            } else if (state == FIRST_SEPARATOR) {
                letterStream << line << std::endl;
            }
        }
    }

    if (state != SECOND_SEPARATOR)
        return -1;

    letterStirng = letterStream.str();

    std::string word;
    iss.clear();
    iss.str(dictionaryStream.str());
    while (iss >> word) {
        std::pair<std::string, int> pair(word, 0);
        dictionaryWords.insert(pair);
    }

    return 0;
}