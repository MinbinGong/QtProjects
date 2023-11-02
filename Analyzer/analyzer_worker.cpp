#include "analyzer_worker.h"

#include <QMessageBox>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/flann/miniflann.hpp>

#include <algorithm>

analyzer_worker::analyzer_worker()
{

}

bool analyzer_worker::execute(QWidget *parent, const QString &reference, const QImage &target)
{
    Q_UNUSED(parent);

    cv::Mat target_img{};
    qimage_to_opencv_mat(target, target_img);
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

void analyzer_worker::qimage_to_opencv_mat(const QImage &inImage, cv::Mat &outImage)
{
    switch (inImage.format()) {
    case QImage::Format_Invalid: {
        cv::Mat empty;
        empty.copyTo(outImage);
        break;
    }
    case QImage::Format_RGB32: {
        cv::Mat image(inImage.height(), inImage.width(), CV_8UC4, (void*)inImage.constBits(), inImage.bytesPerLine());
        image.copyTo(outImage);
        break;
    }
    case QImage::Format_RGB888: {
        cv::Mat image(inImage.height(), inImage.width(), CV_8UC3, (void *)inImage.constBits(), inImage.bytesPerLine());
        cv::cvtColor(image, outImage, cv::COLOR_RGB2BGR);
        break;
    }
    default: {
        QImage conv = inImage.convertToFormat(QImage::Format_ARGB32);
        cv::Mat image(conv.height(), conv.width(), CV_8UC4, (void *)conv.constBits(), conv.bytesPerLine());
        image.copyTo(outImage);
        break;
    }
    }
}

void analyzer_worker::opencv_mat_to_qimage(const cv::Mat &inImage, QImage &outImage)
{
    switch (inImage.type()) {
    case CV_8UC4: {
        QImage view2(inImage.data, inImage.cols, inImage.rows, inImage.step[0], QImage::Format_ARGB32);
        outImage = view2.copy();
        break;
    }
    case CV_8UC3: {
        cv::Mat mat;
        cv::cvtColor(inImage, mat, cv::COLOR_BGR2BGRA);
        QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
        outImage = view.copy();
        break;
    }
    case CV_8UC1: {
        cv::Mat mat;
        cv::cvtColor(inImage, mat, cv::COLOR_GRAY2BGRA);
        QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
        outImage = view.copy();
        break;
    }
    default: {
        throw std::invalid_argument("Image format not supported");
        break;
    }
    }
}

bool analyzer_worker::compare_image(const cv::Mat &src, const cv::Mat &dst)
{
    Q_UNUSED(src);
    Q_UNUSED(dst);

    return true;
}

//cv::Mat analyzer_worker::prepare_image(cv::Mat& image)
//{
//    cv::Mat modifiedImg;
//    cv::cvtColor(image, modifiedImg, cv::COLOR_BGR2BGRA);
//    cv::cvtColor(image, modifiedImg, cv::COLOR_BGRA2GRAY);

//    cv::Mat thresh;
//    cv::threshold(modifiedImg, thresh, 127, 255, cv::THRESH_BINARY_INV|cv::THRESH_OTSU);

//    std::vector<std::vector<cv::Point>> contours;
//    std::vector<cv::Vec4i> hierarchy;
//    cv::findContours(thresh, contours, hierarchy, cv::RETR_TREE,
//                     cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

//    std::vector<std::tuple<std::vector<cv::Point>, bool, double>> vec;
//    for (unsigned int i = 0; i < contours.size(); ++i) {
//        vec.emplace_back(std::make_tuple(contours.at(i),
//                                         cv::isContourConvex(contours.at(i)),
//                                         cv::contourArea(contours.at(i))));
//    }

//    std::sort(vec.begin(), vec.end(),
//              [](std::tuple<std::vector<cv::Point>, bool, double> t1,
//                 std::tuple<std::vector<cv::Point>, bool, double> t2) {
//                return std::get<2>(t1) > std::get<2>(t2);
//              });
//    std::tuple<std::vector<cv::Point>, bool, double> maxContour = vec.at(0);

//    cv::Mat mask = cv::Mat::zeros(thresh.size(), CV_8U);
//    for (unsigned int i = 0; i < contours.size(); ++i) {
//        cv::fillConvexPoly(mask, std::get<0>(vec.at(i)), cv::Scalar(255, 0, 0), 8, 0);
//    }

//    cv::Mat res;
//    cv::bitwise_and(image, image, res, mask);

//    cv::Mat dst, rgb[3];
//    cv::split(res, rgb);

//    cv::Mat rgba[4] = {rgb[0], rgb[1], rgb[2]};
//    cv::merge(rgba, 4, dst);

//    return dst;
//}

//void analyzer_worker::detect_pattern(cv::Mat& image, cv::Mat& templ)
//{
//    cv::Mat grayImg;
//    cv::cvtColor(image, grayImg, cv::COLOR_RGB2GRAY);

//    std::vector<cv::Vec4f> positionBallard, positionGuil;

//    int w = templ.cols;
//    int h = templ.rows;

//    cv::Ptr<cv::GeneralizedHoughBallard> ballard = cv::createGeneralizedHoughBallard();
//    ballard->setMinDist(10);
//    ballard->setLevels(360);
//    ballard->setDp(2);
//    ballard->setMaxBufferSize(1000);
//    ballard->setVotesThreshold(40);

//    ballard->setCannyHighThresh(110);
//    ballard->setCannyLowThresh(30);
//    ballard->setTemplate(templ);

//    ballard->detect(grayImg, positionBallard);

//    cv::Ptr<cv::GeneralizedHoughGuil> guil = cv::createGeneralizedHoughGuil();
//    guil->setMinDist(10);
//    guil->setLevels(360);
//    guil->setDp(3);
//    guil->setMaxBufferSize(1000);

//    guil->setMinAngle(0);
//    guil->setMaxAngle(360);
//    guil->setAngleStep(1);
//    guil->setAngleThresh(1500);

//    guil->setMinScale(0.5);
//    guil->setMaxScale(2.0);
//    guil->setScaleStep(0.05);
//    guil->setScaleThresh(50);

//    guil->setPosThresh(10);

//    guil->setCannyLowThresh(30);
//    guil->setCannyHighThresh(110);

//    guil->setTemplate(templ);

//    guil->detect(grayImg, positionGuil);

//    for (auto itr = positionBallard.begin(); itr != positionBallard.end(); ++itr) {
//        cv::RotatedRect rRect =
//            cv::RotatedRect(cv::Point2f((*itr)[0], (*itr)[1]),
//                            cv::Size2f(w * (*itr)[2], h * (*itr)[2]), (*itr)[3]);
//        cv::Point2f vertices[4];
//        rRect.points(vertices);
//        for (int i = 0; i < 4; ++i) {
//            cv::line(image, vertices[i], vertices[(i + 1) % 4],
//                     cv::Scalar(255, 0, 0), 6);
//        }
//    }

//    for (auto itr = positionGuil.begin(); itr != positionGuil.end(); ++itr) {
//        cv::RotatedRect rRect =
//            cv::RotatedRect(cv::Point2f((*itr)[0], (*itr)[1]),
//                            cv::Size2f(w * (*itr)[2], h * (*itr)[2]), (*itr)[3]);
//        cv::Point2f vertices[4];
//        rRect.points(vertices);
//        for (int i = 0; i < 4; ++i) {
//            cv::line(image, vertices[i], vertices[(i + 1) % 4],
//                     cv::Scalar(255, 0, 0), 6);
//        }
//    }

//}
