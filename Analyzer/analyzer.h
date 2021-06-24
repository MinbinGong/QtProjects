#ifndef ANALYZER_H
#define ANALYZER_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Analyzer; }
QT_END_NAMESPACE

class Analyzer : public QMainWindow
{
    Q_OBJECT

public:
    Analyzer(QWidget *parent = nullptr);
    ~Analyzer();

private slots:
    void on_imageCaptured(int id, const QImage &preview);

    void on_capture_clicked();

    void on_analyze_clicked();

    void on_save_clicked();

private:
    Ui::Analyzer *ui;
    QString file;

    QList<QCameraInfo> m_cameras;
    QCamera *m_camera;
    QCameraViewfinder *m_viewfinder;
    QCameraImageCapture *m_imageCapture;
};
#endif // ANALYZER_H
