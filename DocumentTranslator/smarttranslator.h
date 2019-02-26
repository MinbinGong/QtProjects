#ifndef SMARTTRANSLATOR_H
#define SMARTTRANSLATOR_H

#include <QMainWindow>
#include <QString>

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

private:
//    void createMenus();
    void createActions();

//private:
//    QMenu *fileMenu;
//    QMenu *aboutMenu;

private:
    Ui::SmartTranslator *ui;
};

#endif // SMARTTRANSLATOR_H
