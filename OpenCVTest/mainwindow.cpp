#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::Mat image = cv::imread("c://Users//gongw//Downloads//1.jpg", 1);
    cv::namedWindow("My Image");
    cv::imshow("My Image", image);
}

MainWindow::~MainWindow()
{
    delete ui;
}

