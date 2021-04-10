#ifndef SEARCHER_H
#define SEARCHER_H

//#include "dictionary.h"

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Searcher; }
QT_END_NAMESPACE

class Searcher : public QMainWindow
{
    Q_OBJECT

public:
    Searcher(QWidget *parent = nullptr);
    ~Searcher();

private slots:
    void on_search_bar_textChanged(const QString &arg1);

    void on_advanced_stateChanged(int arg1);

private:
    Ui::Searcher *ui;
    //const Dictionary* dict;
    QStringListModel* model;
};

#endif // SEARCHER_H
