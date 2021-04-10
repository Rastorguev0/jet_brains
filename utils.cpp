#include "utils.h"
#include "profile.h"

#include <future>
#include <sstream>

void FillWithKeys(Dict& dict) {
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        dict[ch];
    }
    for (char ch = 'a'; ch <= 'z'; ch++) {
        dict[ch];
    }
    dict['_'];
}

Dict MergeDicts(std::vector<Dict>&& dicts) {
    Dict result;
    FillWithKeys(result);
    for (auto& [lett, words]: result) {
        Words merged;

        size_t size = 0;
        for (const auto& dict : dicts) {
            size += dict.at(lett).size();
        }
        merged.reserve(size);

        for (const auto& dict : dicts) {
            merged.insert(merged.end(), dict.at(lett).begin(), dict.at(lett).end());
        }
        words = move(merged);
    }
    return result;
}

QStringList ToStringList(const Words& words) {
    QStringList result;
    for (const auto& word : words) {
        result << QString::fromStdString(*word);
    }
    return result;
}
