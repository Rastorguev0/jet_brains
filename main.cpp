#include "searcher.h"

#include <QApplication>
#include <QFile>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile style("Combinear.qss");
    style.open(QFile::ReadOnly);
    QString styleSheet{ style.readAll() };
    a.setStyleSheet(styleSheet);

    Searcher w;
    w.show();
    return a.exec();
}
