#include "fuzedetector.h"
#include "ui_fuzedetector.h"

FuzeDetector::FuzeDetector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FuzeDetector)
{
    ui->setupUi(this);
}

FuzeDetector::~FuzeDetector()
{
    delete ui;
}
