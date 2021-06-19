#include "analyzer.h"
#include "ui_analyzer.h"

Analyzer::Analyzer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Analyzer)
{
    ui->setupUi(this);

    init();
}

Analyzer::~Analyzer()
{
    delete ui;
}

void Analyzer::init()
{
    camera = new QCamera();
    viewfinder = new QCameraViewfinder(this);
    imageCapture = new QCameraImageCapture(camera);

    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(viewfinder);
//    camera->start();
}
