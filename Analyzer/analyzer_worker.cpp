#include "analyzer_worker.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

analyzer_worker::analyzer_worker()
{

}

void analyzer_worker::execute(QWidget *parent, const QString &fileName)
{
    Q_UNUSED(parent);
    cv::Mat image = cv::imread(fileName.toStdString(), 1);
    cv::namedWindow("My Image");
    cv::imshow("My Image", image);
}
