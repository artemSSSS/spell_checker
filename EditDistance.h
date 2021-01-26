#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include <string>
#include <algorithm>
#include <vector>

#define MIN_DIST 2

#define DEL_COST 1
#define INSERT_COST 1
#define REPLACE_COST 2 

class EditDistance {
public:
    virtual size_t GetDistance(const std::string& str1, const std::string& str2) = 0;
};

class GEditDistance : public EditDistance {
private:
    size_t InternalGetDistance(const std::string& str1, const std::string& str2, int priv);

public:
    virtual size_t GetDistance(const std::string& str1, const std::string& str2);
};

class NormalEditDistance : public EditDistance {
public:
    virtual size_t GetDistance(const std::string& str1, const std::string& str2);
};

#endif