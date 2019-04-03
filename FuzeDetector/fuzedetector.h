#ifndef FUZEDETECTOR_H
#define FUZEDETECTOR_H

#include <QMainWindow>

namespace Ui {
class FuzeDetector;
}

class FuzeDetector : public QMainWindow
{
    Q_OBJECT

public:
    explicit FuzeDetector(QWidget *parent = nullptr);
    ~FuzeDetector();

private:
    Ui::FuzeDetector *ui;
};

#endif // FUZEDETECTOR_H
