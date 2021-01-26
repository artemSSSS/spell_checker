#ifndef PARSEFILE_H
#define PARSEFILE_H

#include <map>
#include <string>
#include <streambuf>
#include <sstream>

class ParseFile {
public:
    static int ParseFileInputFile(const std::string& fileContent, std::string& letterStirng,
            std::map<std::string, size_t>& dictionaryWords);
};

#endif