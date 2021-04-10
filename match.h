#ifndef MATCHE_H
#define MATCHE_H

#include <QString>
#include <QStringList>

enum class Match {
    BASE, ADVANCED,
};

std::string MakeFileName(char ch);

bool IsMatch(const std::string& main, const std::string& sub, Match m);

QStringList GetMatches(const QString& str, Match m);

#endif // MATCHE_H
