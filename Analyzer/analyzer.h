#ifndef ANALYZER_H
#define ANALYZER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Analyzer; }
QT_END_NAMESPACE

class Analyzer : public QMainWindow
{
    Q_OBJECT

public:
    Analyzer(QWidget *parent = nullptr);
    ~Analyzer();

private:
    Ui::Analyzer *ui;
};
#endif // ANALYZER_H
