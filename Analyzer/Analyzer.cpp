#include "Analyzer.h"
#include "AnalyzerWorker.h"
#include "ui_analyzer.h"

#include <QCameraInfo>
#include <QGraphicsView>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QStandardPaths>
#include <QMessageBox>
#include <QUuid>

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

    bool result = worker->execute(this, m_reference, m_capture);
    if (result) {
        ui->statusbar->showMessage(tr("Qualified"));
    } else {
        ui->statusbar->showMessage(tr("NOT qualified"));
    }

    delete worker;
}

void Analyzer::on_select_clicked()
{
    m_reference = QFileDialog::getOpenFileName(this, tr("select file"), QDir::homePath(), tr("jpegfile(*.jpg)"));
    if(m_reference.isEmpty()) {
        qDebug("select canceled");
        ui->statusbar->showMessage(tr("select canceled"), 5000);
        return;
    }

    QPixmap *pixmap = new QPixmap();
    pixmap->load(m_reference);
    int width = ui->reference->width();
    int height = ui->reference->height();
    QPixmap fitPixmap = pixmap->scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->reference->setPixmap(fitPixmap);

    delete pixmap;
}

void Analyzer::on_imageCaptured(int id, const QImage &preview)
{
    Q_UNUSED(id);

    int width = ui->zoomLabel->width();
    int height = ui->zoomLabel->height();
    QPixmap pixmap = QPixmap::fromImage(preview);
    if (pixmap.isNull()) {
        ui->statusbar->showMessage(tr("Fail to capture."), 5000);
    }
    QPixmap fitPixmap = pixmap.scaled(width, height, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->zoomLabel->setPixmap(fitPixmap);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Save the photo", "Save?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        qDebug("Yes not clicked");
        return;
    }

    m_capture = QFileDialog::getExistingDirectory().append("/");
    if (m_capture.isEmpty()) {
        qDebug("Directory is empty");
        return;
    }

    m_capture.append(QUuid::createUuid().toString(QUuid::WithoutBraces) + ".jpeg");
//    qDebug("filename is %s", qPrintable(m_capture));
    if (preview.save(m_capture, "JPEG")) {
        qDebug("photo is saved as %s", qPrintable(m_capture));
    }
}
