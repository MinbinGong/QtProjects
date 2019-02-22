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

//    void loadFile(const QString &fileName);

//private slots:
//    void newFile();
//    void open();
//    void save();
//    void saveAs();
//    void about();

//    void documentWasModified();

//private:
//    void createActions();
//    void createStatusBar();
//    void readSettings();
//    void writeSettings();
//    bool maybeSave();
//    bool saveFile(const QString &fileName);
//    void setCurrentFile(const QString &fiileName);
//    QString strippedName(const QString &fullFileName);

private:
    Ui::SmartTranslator *ui;
};

#endif // SMARTTRANSLATOR_H
