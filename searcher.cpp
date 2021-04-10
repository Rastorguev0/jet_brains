#include "searcher.h"
#include "ui_searcher.h"
#include "profile.h"
#include "match.h"

Searcher::Searcher(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Searcher)
{
    LOG_DURATION("Starting the app");
    ui->setupUi(this);
    //dict = new Dictionary("words.txt");
    model = new QStringListModel(this);
    ui->search_result->setModel(model);
    ui->layout->setAlignment(Qt::AlignCenter);
    ui->search_bar->setFocus();
}

Searcher::~Searcher()
{
    delete ui;
    //delete dict;
}


void Searcher::on_search_bar_textChanged(const QString& s)
{
    LOG_DURATION("Output");
    Match m;
    if (ui->advanced->isChecked())
        m = Match::ADVANCED;
    else m = Match::BASE;
    model->setStringList(GetMatches(s, m));
}

void Searcher::on_advanced_stateChanged(int)
{
    on_search_bar_textChanged(ui->search_bar->text());
}
