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

void FuzeDetector::on_action_New_triggered()
{

}

void FuzeDetector::on_action_Open_triggered()
{

}

void FuzeDetector::on_action_Save_triggered()
{

}
