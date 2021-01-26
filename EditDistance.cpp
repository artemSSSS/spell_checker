#include "EditDistance.h"

size_t GEditDistance::InternalGetDistance(const std::string& str1, const std::string& str2, int priv) {
    if (str1.empty())
        return (str2.length());
    if (str2.empty())
        return (str1.length());

    if (priv < 0) {
        return (std::min(InternalGetDistance(str1.substr(1), str2.substr(1), 0) + ((str1[0] != str2[0]) ? REPLACE_COST : 0),
                InternalGetDistance(str1.substr(1), str2, 1) + DEL_COST));
    } else if (priv > 0) {
        return (std::min(InternalGetDistance(str1.substr(1), str2.substr(1), 0) + ((str1[0] != str2[0]) ? REPLACE_COST : 0),
                InternalGetDistance(str1, str2.substr(1), -1) + DEL_COST));
    } else {
        return (std::min(InternalGetDistance(str1.substr(1), str2.substr(1), 0) + ((str1[0] != str2[0]) ? REPLACE_COST : 0),
                std::min(InternalGetDistance(str1.substr(1), str2, 1), InternalGetDistance(str1, str2.substr(1), -1)) + DEL_COST));
    }
}

size_t GEditDistance::GetDistance(const std::string& str1, const std::string& str2) {
    return (std::min(InternalGetDistance(str1, str2, 1), InternalGetDistance(str1, str2, -1)));
}

size_t NormalEditDistance::GetDistance(const std::string& s1, const std::string& s2) {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<size_t> > d(len1 + 1, std::vector<size_t>(len2 + 1));

    d[0][0] = 0;
    for (size_t i = 1; i <= len1; ++i) d[i][0] = d[i - 1][0] + DEL_COST;
    for (size_t i = 1; i <= len2; ++i) d[0][i] = d[0][i - 1] + INSERT_COST;

    for (size_t i = 1; i <= len1; ++i)
        for (size_t j = 1; j <= len2; ++j)
            d[i][j] = std::min(std::min(d[i - 1][j] + DEL_COST, d[i][j - 1] + INSERT_COST), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : REPLACE_COST));

    return d[len1][len2];
}