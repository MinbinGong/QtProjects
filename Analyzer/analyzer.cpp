#include "analyzer.h"
#include "analyzer_worker.h"
#include "ui_analyzer.h"

#include <QCameraInfo>
#include <QGraphicsView>
#include <QString>
#include <QPixmap>
#include <QFileDialog>

Analyzer::Analyzer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Analyzer)
{
    ui->setupUi(this);

    m_cameras = QCameraInfo::availableCameras();
    foreach(const auto &cameraInfo, m_cameras) {
        ui->cameraType->addItem(cameraInfo.description());
    }

    m_viewfinder = new QCameraViewfinder();
    ui->imageView->addWidget(m_viewfinder);

    m_camera = new QCamera(this);
    m_imageCapture = new QCameraImageCapture(m_camera);
    ui->zoomLabel->setScaledContents(true);

    m_camera->setViewfinder(m_viewfinder);
    m_camera->start();

    connect(m_imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(on_imageCaptured(int,QImage)));
}

Analyzer::~Analyzer()
{
    delete ui;
}

void Analyzer::on_capture_clicked()
{
    ui->statusbar->showMessage(tr("Capturing..."), 1000);
    m_imageCapture->capture();
}

void Analyzer::on_analyze_clicked()
{
    analyzer_worker *worker = new analyzer_worker();

    worker->execute(this, file);

    delete worker;
}

void Analyzer::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("save file"), QDir::homePath(), tr("jpegfile(*.jpg)"));
    if(fileName.isEmpty())
    {
        ui->statusbar->showMessage(tr("save canceled"), 5000);
    }

    const QPixmap *pixmap = ui->zoomLabel->pixmap();
    if (nullptr != pixmap)
    {
        file = fileName;
        pixmap->save(fileName);
    }
}

void Analyzer::on_imageCaptured(int id, const QImage &preview)
{
    Q_UNUSED(id);
    int width = ui->zoomLabel->width();
    int height = ui->zoomLabel->height();
    QPixmap pixmap = QPixmap::fromImage(preview);
    QPixmap fitPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->zoomLabel->setPixmap(pixmap);
}
