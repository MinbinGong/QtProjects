#include "analyzer_worker.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

analyzer_worker::analyzer_worker()
{

}

void analyzer_worker::execute(QWidget *parent, const QString &reference, const QString &target)
{
    Q_UNUSED(parent);
    cv::Mat imageRef = cv::imread(reference.toStdString(), 1);
    cv::namedWindow("Reference Image");
    cv::imshow("Reference Image", imageRef);

    cv::Mat imageTarget = cv::imread(target.toStdString(), 1);
    cv::namedWindow("Reference Image");
    cv::imshow("Reference Image", imageTarget);
}
