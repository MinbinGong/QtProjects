#ifndef SMARTTRANSLATOR_H
#define SMARTTRANSLATOR_H

#include <QMainWindow>
#include <QString>

//#include "openwindow.h"

namespace Ui {
class SmartTranslator;
}

class SmartTranslator : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmartTranslator(QWidget *parent = nullptr);
    ~SmartTranslator();

private slots:
    void actionHelp();
    void actionAbout();
    void actionExit();

    void on_buttonSrc_clicked();

    void on_buttonTranslate_clicked();

private:
    void createActions();

    QString translate(QString keyword, QString from, QString to);
    void loadFile(const QString &fileName);

private:
    Ui::SmartTranslator *ui;

    QString fileName;
    QString fileContent;
};

#endif // SMARTTRANSLATOR_H
