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

private slots:
    void on_action_New_triggered();

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_action_Save_As_triggered();

    void on_action_Quit_triggered();

    void on_action_Cut_triggered();

    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_action_Preference_triggered();

    void on_actionAbout_FuzeDetector_triggered();

private:
    Ui::FuzeDetector *ui;
};

#endif // FUZEDETECTOR_H
