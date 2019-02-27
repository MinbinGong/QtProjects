#ifndef OPENWINDOW_H
#define OPENWINDOW_H

#include <QDialog>

namespace Ui {
class OpenWindow;
}

class OpenWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OpenWindow(QWidget *parent = nullptr);
    ~OpenWindow();

private:
    Ui::OpenWindow *ui;
};

#endif // OPENWINDOW_H
