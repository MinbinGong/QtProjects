#include "smarttranslator.h"
#include "ui_smarttranslator.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>

SmartTranslator::SmartTranslator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmartTranslator)
{
    ui->setupUi(this);

    createActions();
}

SmartTranslator::~SmartTranslator()
{
    delete ui;
}

void SmartTranslator::loadFile(const QString &fileName)
{
    QFile file(fileName);
       if (!file.open(QFile::ReadOnly | QFile::Text)) {
           QMessageBox::warning(this, tr("Application"),
                                tr("Cannot read file %1:\n%2.")
                                .arg(QDir::toNativeSeparators(fileName), file.errorString()));
           return;
       }

       QTextStream in(&file);
   #ifndef QT_NO_CURSOR
       QApplication::setOverrideCursor(Qt::WaitCursor);
   #endif

       ui->textBrowser->setPlainText(in.readAll());
   #ifndef QT_NO_CURSOR
       QApplication::restoreOverrideCursor();
   #endif
}

void SmartTranslator::actionAbout()
{
    QMessageBox::about(this, tr("SmartTranslator"),
                tr("The <b>SmartTranslator</b> shows a smart translator based on Google translate"));
}

void SmartTranslator::actionExit()
{
    QApplication::quit();
}

void SmartTranslator::actionHelp()
{
    QMessageBox::about(this, tr("Help"),
                tr("Please try to contact <b>Wayne Gong</b>"
                   "\ngongwayne@hotmail.com"));
}

void SmartTranslator::createActions()
{
    connect(ui->actionExit, &QAction::triggered, this, &SmartTranslator::actionExit);
    ui->menuFile->addAction(ui->actionExit);

    connect(ui->actionHelp, &QAction::triggered, this, &SmartTranslator::actionHelp);
    ui->menuAbout->addAction(ui->actionHelp);

    connect(ui->actionAbout, &QAction::triggered, this, &SmartTranslator::actionAbout);
    ui->menuAbout->addAction(ui->actionAbout);
}

void SmartTranslator::on_buttonSrc_clicked()
{
}
