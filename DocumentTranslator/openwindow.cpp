#include "openwindow.h"
#include "ui_openwindow.h"

OpenWindow::OpenWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenWindow)
{
    ui->setupUi(this);
}

OpenWindow::~OpenWindow()
{
    delete ui;
}
