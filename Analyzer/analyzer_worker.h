#ifndef ANALYZER_WORKER_H
#define ANALYZER_WORKER_H

#include <QString>
#include <QWidget>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class analyzer_worker
{
public:
    analyzer_worker();
    virtual ~analyzer_worker() {}

    void execute(QWidget *parent, const QString &reference, const QImage &target);

private:
    cv::Mat convert_opencv_mat( const QImage &inImage, bool inCloneImageData = true);
};

#endif // ANALYZER_WORKER_H
