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

    void loadFile(const QString &fileName);

private slots:
    void actionHelp();
    void actionAbout();
    void actionExit();

    void on_buttonSrc_clicked();

private:
    void createActions();

private:
    Ui::SmartTranslator *ui;
};

#endif // SMARTTRANSLATOR_H
