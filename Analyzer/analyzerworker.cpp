#include "analyzerworker.h"

#include <QMessageBox>
#include <QLabel>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/flann/miniflann.hpp>

#include <algorithm>

analyzer_worker::analyzer_worker()
{
    faces.clear();
}

analyzer_worker::~analyzer_worker()
{
}

bool analyzer_worker::execute(QWidget *parent, const QString &reference, const QString &target)
{
    Q_UNUSED(parent);

    cv::Mat target_img = cv::imread(target.toStdString());
    if (target_img.empty()) {
        return false;
    }

    auto faces = detect(target_img);
    if (faces->size() != 0) {
        for (size_t i = 0; i < faces->size(); ++i) {
            cv::rectangle(target_img, faces->at(i), cv::Scalar(255, 0, 0), 2);
        }
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

std::shared_ptr<std::vector<cv::Rect>> analyzer_worker::detect(const cv::Mat &src_image)
{
    cv::Mat gray;
    cv::cvtColor(src_image, gray, cv::COLOR_BGR2GRAY);
    if (gray.empty() || faces.empty()) {
        return {};
    }

    face_cascade.detectMultiScale(gray, faces);

    return std::make_shared<std::vector<cv::Rect>>(faces);
}
