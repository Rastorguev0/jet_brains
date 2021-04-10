#include "dictionary.h"
#include "profile.h"
#include "utils.h"

#include <QThread>
#include <fstream>
#include <future>
#include <set>

using namespace std;

const int THREADS_COUNT = QThread::idealThreadCount();


vector<string> Dictionary::ReadAllWords(const std::string& file) {
    LOG_DURATION("Read words");
    vector<string> result;
    std::ifstream input(file);

    std::string word;
    getline(input, word);
    result.reserve(stoi(word));

    while (std::getline(input, word)) {
        result.push_back(word);
    }
    return result;
}

template<typename Range>
Dict MakeDictPart(Range r) {
    Dict result;
    FillWithKeys(result);
    for (const auto& word : r) {
        set<char> chars;
        bool pushed_to_other = false;
        for (auto ch : word) {
            if (!chars.count(ch)) {
                if (isalpha(ch)) {
                    result[ch].push_back(&word);
                }
                else if (!pushed_to_other) {
                    result['_'].push_back(&word);
                    pushed_to_other = true;
                }
            }
            chars.insert(ch);
        }
    }
    return result;
}

Dict Dictionary::MakeDict(const vector<string>& owner) {
    LOG_DURATION("Dict creating");
    vector<Dict> parts(THREADS_COUNT);
    vector<future<void>> futures;

    int i = 0;
    for (auto words : Paginate(owner, THREADS_COUNT)) {
        auto& part = parts[i++];
        futures.push_back(async(std::launch::async, [words, &part] {
            part = MakeDictPart(words);
        }));
    }
    futures.clear();
    return MergeDicts(std::move(parts));
}

Words Dictionary::SubwordHaving(const Words& words, const string& sub) const {
    if (sub.size() == 1 && isalpha(sub[0])) {
        return words;
    }
    Words result;
    for (const auto& word : words) {
        if (word->find(sub) != string::npos) {
            result.push_back(word);
        }
    }
    return result;
}

Words Dictionary::FindSubwordHaving(const std::string& sub) const {
    if (sub.empty()) return {};

    char symb = sub[0];
    if (!isalpha(symb)) symb = '_';
    const auto& words = wrds_wth_lttr.at(symb);
    return SubwordHaving(words, sub);
}


Dictionary::Dictionary(const string& file_name)
    : words_base(ReadAllWords(file_name)),
      wrds_wth_lttr(MakeDict(words_base)) {}
