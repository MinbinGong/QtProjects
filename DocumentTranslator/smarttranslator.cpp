#include "smarttranslator.h"
#include "ui_smarttranslator.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

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
                             tr("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    fileContent = in.readAll();
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
    fileName = QFileDialog::getOpenFileName(this,
             tr("Open File"), "/home", tr("TXT Files (*.txt)"));
    ui->lineEdit->setText(fileName);
}

void SmartTranslator::on_buttonTranslate_clicked()
{
    loadFile(fileName);
    QString translated = translate(fileContent, QString("en"), QString("zh-CN"));
    QMessageBox::about(this, tr("Translated"),
                       tr(translated.toUtf8().constData()));
}

QString SmartTranslator::translate(QString keyword, QString from, QString to)
{
    //Translate URL
//    QString url = QString("http://translate.google.com/translate_a/t?client=t&text=%0&hl=%1&sl=%2&tl=%1&multires=1&prev=enter&oc=2&ssel=0&tsel=0&uptl=%1&sc=1").arg(keyword).arg(to).arg(from);
    QString url = QString("https://translate.google.com/?tr=f&hl=en#view=home&op=docs&sl=%1&tl=%2").arg(from).arg(to);

    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

    //Get reply from Google
    do {
        QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    } while(!reply->isFinished());

    //Convert to string
    QString translation(reply->readAll());
    reply->close();

    //Free memory
    delete reply;

    //Remove [[[" from the beginning
    translation = translation.replace("[[[\"", "");

    //Extract final translated string
    translation = translation.mid(0, translation.indexOf(",\"") - 1);

    return translation;
}
