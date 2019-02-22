#ifndef SMARTTRANSLATOR_H
#define SMARTTRANSLATOR_H

#include <QMainWindow>

namespace Ui {
class SmartTranslator;
}

class SmartTranslator : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmartTranslator(QWidget *parent = nullptr);
    ~SmartTranslator();

private:
    Ui::SmartTranslator *ui;
};

#endif // SMARTTRANSLATOR_H
