#include "TransformInputString.h"

enum {
    SPACE, WORD, END_WORD
};

void TransformInputString::TransformInputLetterString(std::string& inputLetter,
        std::map<std::string, size_t>& dictionaryWords) {
    size_t state = SPACE;
    size_t wBegin = 0, wEnd = 0;
    for (size_t i = 0; i < inputLetter.size();) {
        if (!(ASCII_NOT_WORD_CHARS_BEGIN <= inputLetter[i] && inputLetter[i] <= ASCII_NOT_WORD_CHARS_End)) {
            if (state == SPACE) {
                state = WORD;
                wBegin = i;
            }
        } else {
            if (state == WORD) {
                state = END_WORD;
                wEnd = i;
            }
        }

        if (state == END_WORD) {
            state = SPACE;
            size_t len = wEnd - wBegin;
            std::string newWord = CorrectWord(inputLetter.substr(wBegin, len), dictionaryWords);
            inputLetter.replace(wBegin, len, newWord);
            if (newWord.size() < len)
                i = wEnd;
            else
                i = wEnd + newWord.size() - len;
        } else {
            i++;
        }
    }
}

std::string TransformInputString::CorrectWord(const std::string& word,
        std::map<std::string, size_t>& dictionaryWords) {
    std::string newWord;

    if (dictionaryWords.size() == 0) {
        return word;
    }

    std::map<std::string, size_t>::iterator iter = dictionaryWords.find(word);
    if (iter != dictionaryWords.end()) {
        return word;
    }

    for (std::map<std::string, size_t>::iterator dicIter = dictionaryWords.begin();
            dicIter != dictionaryWords.end(); dicIter++) {
        std::string lowerWord = word;
        std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

        std::string lowerDictionaryWord = dicIter->first;
        std::transform(lowerDictionaryWord.begin(), lowerDictionaryWord.end(), lowerDictionaryWord.begin(), ::tolower);

        dicIter->second = GetDistance(lowerWord, lowerDictionaryWord);
    }

    FindMin min;
    std::map<std::string, size_t>::const_iterator minIter = std::min_element(dictionaryWords.begin(), dictionaryWords.end(), min);

    if (minIter->second > MIN_DIST) {
        newWord = "{" + word + "?}";
        return newWord;
    }

    std::vector<std::string> anotherMins;
    for (std::map<std::string, size_t>::const_iterator dicIter = dictionaryWords.begin();
            dicIter != dictionaryWords.end(); dicIter++) {
        if (dicIter == minIter)
            continue;

        if (dicIter->second == minIter->second)
            anotherMins.push_back(dicIter->first);
    }

    if (anotherMins.size() == 0) {
        newWord = minIter->first;
    } else {
        newWord = "{" + minIter->first;
        for (size_t j = 0; j < anotherMins.size(); j++) {
            newWord += " " + anotherMins[j];
        }
        newWord += "}";
    }

    return newWord;
}