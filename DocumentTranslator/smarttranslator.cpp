#include "smarttranslator.h"
#include "ui_smarttranslator.h"

SmartTranslator::SmartTranslator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmartTranslator)
{
    ui->setupUi(this);
}

SmartTranslator::~SmartTranslator()
{
    delete ui;
}
