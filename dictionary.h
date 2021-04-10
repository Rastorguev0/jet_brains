#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "utils.h"

#include <vector>
#include <string>

class Dictionary
{
public:
    Dictionary(const std::string& file_name);
    Words FindSubwordHaving(const std::string& sub) const;
private:
    std::vector<std::string> ReadAllWords(const std::string& file);
    Dict MakeDict(const std::vector<std::string>& words);

    Words SubwordHaving(const Words& words, const std::string& sub) const;
private:
    //all words base
    const std::vector<std::string> words_base;
    //for any letter keep words containing it
    //for '_' keep words containig non-letter symbols
    const Dict wrds_wth_lttr;
};

#endif // DICTIONARY_H
