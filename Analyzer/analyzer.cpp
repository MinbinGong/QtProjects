#include "analyzer.h"
#include "ui_analyzer.h"

Analyzer::Analyzer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Analyzer)
{
    ui->setupUi(this);
}

Analyzer::~Analyzer()
{
    delete ui;
}
