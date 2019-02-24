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

void SmartTranslator::loadFile(const QString &fileName)
{

}

void SmartTranslator::actionNew()
{

}

void SmartTranslator::actionOpen()
{

}

void SmartTranslator::actionSave()
{

}

void SmartTranslator::actionSaveAs()
{

}

void SmartTranslator::actionRecent()
{

}

void SmartTranslator::actionAbout()
{

}
