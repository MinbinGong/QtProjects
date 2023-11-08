#include "analyzerworker.h"

#include <QMessageBox>
#include <QLabel>
#include <QDir>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/flann/miniflann.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <fstream>

analyzer_worker::analyzer_worker()
{
    mFaces.clear();
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

    detectAndDraw(target_img);

    cv::namedWindow("Target Image");
    cv::imshow("Target Image", target_img);

    cv::Mat image_ref = cv::imread(reference.toStdString());
    if (image_ref.empty()) {
        return false;
    }

    cv::namedWindow("Source Image");
    cv::imshow("Source Image", image_ref);

    return true;
}

void analyzer_worker::detectAndDraw(cv::Mat &img)
{
    QString currentPath = QDir::currentPath();
    qDebug("current directory: %s", qPrintable(currentPath));

//    mCascade.load("./cascades/haarcascade_frontface_alt.xml");

//    cv::Mat gray;
//    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
//    mCascade.detectMultiScale(gray, mFaces);
//    for (unsigned int i = 0; i < mFaces.size(); i++) {
//        cv::rectangle(img, mFaces[i], cv::Scalar(255, 0, 0), 2);
//    }
}
