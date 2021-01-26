#ifndef TRANSFORMINPUTSTRING_H
#define TRANSFORMINPUTSTRING_H

#include "EditDistance.h"

#include <map>
#include <string>

#define ASCII_NOT_WORD_CHARS_BEGIN 0
#define ASCII_NOT_WORD_CHARS_End 32

struct FindMin {

    bool operator()(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) const {
        return a.second < b.second;
    }
};

class TransformInputString {
private:
    EditDistance* editDistance;

    TransformInputString();
    TransformInputString(const TransformInputString&);
    void TransformInputString::operator=(const TransformInputString&);

    size_t GetDistance(const std::string& str1, const std::string& str2) {
        return editDistance->GetDistance(str1, str2);
    };
public:

    TransformInputString(EditDistance* editDistance) {
        this->editDistance = editDistance;
    };

    virtual ~TransformInputString() {
        if (editDistance) {
            delete editDistance;
            editDistance = NULL;
        }
    };

    void TransformInputLetterString(std::string& inputLetter,
            std::map<std::string, size_t>& dictionaryWords);
    std::string CorrectWord(const std::string& word,
            std::map<std::string, size_t>& dictionaryWords);
};

#endif