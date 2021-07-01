#include "analyzer.h"
#include "analyzer_worker.h"
#include "ui_analyzer.h"

#include <QCameraInfo>
#include <QGraphicsView>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QStandardPaths>
#include <QMessageBox>

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

    worker->execute(this, m_reference, m_capture);

    delete worker;
}

void Analyzer::on_select_clicked()
{
    m_reference = QFileDialog::getOpenFileName(this, tr("select file"), QDir::homePath(), tr("jpegfile(*.jpg)"));
    if(m_reference.isEmpty())
    {
        ui->statusbar->showMessage(tr("select canceled"), 5000);
    }

    QPixmap *pixmap = new QPixmap();
    pixmap->load(m_reference);
    int width = ui->reference->width();
    int height = ui->reference->height();
    QPixmap fitPixmap = pixmap->scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->reference->setPixmap(fitPixmap);
}

void Analyzer::on_imageCaptured(int id, const QImage &preview)
{
    Q_UNUSED(id);
    m_capture = preview;

    int width = ui->zoomLabel->width();
    int height = ui->zoomLabel->height();
    QPixmap pixmap = QPixmap::fromImage(preview);
    QPixmap fitPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->zoomLabel->setPixmap(pixmap);
}
