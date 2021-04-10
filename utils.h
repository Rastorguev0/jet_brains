#ifndef UTILS_H
#define UTILS_H

#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

#include <QStringList>


template<class Iterator>
class IteratorRange {
private:
    Iterator begin_it, end_it;
public:
    IteratorRange(Iterator b, Iterator e) {
        begin_it = b;
        end_it = e;
    }
    Iterator begin() const {
        return begin_it;
    }
    Iterator end() const {
        return end_it;
    }
    size_t size() const {
        return end_it - begin_it;
    }
};


template<class It>
auto MakeRange(It begin, It end) {
    return IteratorRange(begin, end);
}


template <typename RandomIt>
class Paginator
{
private:
    std::vector<IteratorRange<RandomIt>> pages;

public:
    Paginator(RandomIt begin, RandomIt end, int parts) {
        if (parts > 0 && begin < end) {
            const int step = (end - begin) / parts;
            for (int i = 0; i + 1 < parts; ++i) {
                pages.push_back(MakeRange(begin, begin + step));
                begin += step;
            }
            pages.push_back(MakeRange(begin, end));
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }
};


template <typename C>
auto Paginate(C& c, size_t parts) {
    return Paginator(c.begin(), c.end(), parts);
}

template<typename C>
auto Head(C& c, int count) {
    if (count > 0) {
        if (c.end() - c.begin() > count) {
            return MakeRange(c.begin(), c.begin() + count);
        }
        else return MakeRange(c.begin(), c.end());
    }
}

template<typename C>
auto Vicinity(C& c, int pos_idx, size_t radius) {
    auto lbound = std::max(c.begin(), std::min(c.begin()  + pos_idx - radius, c.end()));
    auto rbound = std::min(c.begin() + pos_idx + radius, c.end());
    return MakeRange(lbound, rbound);
}

template<typename C>
auto MostlyNextItems(C& c, int pos_idx, size_t count) {
    auto item = std::max(c.begin(), std::min(c.end(), c.begin() + pos_idx));
    auto rbound = std::min(c.end(), item + count);
    auto lbound = std::max(c.begin(), rbound - count);
    return MakeRange(lbound, rbound);
}



using Words = std::vector<const std::string*>;
using Dict = std::unordered_map<char, Words>;

void FillWithKeys(Dict& dict);

Dict MergeDicts(std::vector<Dict>&& dicts);

QStringList ToStringList(const Words& words);

QString ToString(const Words& words);

#endif // UTILS_H
