#ifndef MATCHE_CPP
#define MATCHE_CPP
#include "match.h"

#include <string>
#include <fstream>
using namespace std;

string MakeFileName(char ch) {
    string file_name;
    if ('A' <= ch && ch <= 'Z') file_name += "cap_";
    file_name += tolower(ch);
    file_name += ".txt";
    return file_name;
}

bool IsMatch(const string& main, const string& sub, Match m) {
    switch (m) {
    case Match::BASE:
        return main.find(sub) != string::npos;
        break;
    case Match::ADVANCED:
        int pos = -1;
        for (char ch : sub) {
            pos = main.find(ch, pos + 1);
            if (static_cast<size_t>(pos) == string::npos) return false;
        }
        return true;
        break;
    }
}

QStringList GetMatches(const QString& str, Match m) {
    QStringList result;
    if (str.isEmpty()) return result;

    char symb = str[0].toLatin1();
    if (!isalpha(symb)) symb = '_';
    ifstream input(MakeFileName(symb));
    string stdstr = str.toStdString();

    string word;
    while (getline(input, word)) {
        if (IsMatch(word, stdstr, m)) {
            result << QString::fromStdString(word);
        }
    }
    return result;
}

#endif // MATCHE_CPP
