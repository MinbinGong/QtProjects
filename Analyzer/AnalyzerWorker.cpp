#include "AnalyzerWorker.h"

#include <QMessageBox>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/flann/miniflann.hpp>

#include <QLabel>

#include <algorithm>

analyzer_worker::analyzer_worker()
{

}

bool analyzer_worker::execute(QWidget *parent, const QString &reference, const QString &target)
{
    Q_UNUSED(parent);

    cv::Mat target_img = cv::imread(target.toStdString());
    if (target_img.empty()) {
        return false;
    }
    cv::namedWindow("Target Image");
    cv::imshow("Target Image", target_img);

    cv::Mat image_ref = cv::imread(reference.toStdString());
    if (image_ref.empty()) {
        return false;
    }

    cv::namedWindow("Source Image");
    cv::imshow("Source Image", image_ref);

    return compare_image(image_ref, target_img);
}

bool analyzer_worker::compare_image(const cv::Mat &src, const cv::Mat &dst)
{
    Q_UNUSED(src);
    Q_UNUSED(dst);

    return true;
}
