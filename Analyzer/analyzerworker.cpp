#include "analyzerworker.h"

#include <QMessageBox>
#include <QLabel>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/flann/miniflann.hpp>

#include <string>
#include <fstream>

#define CASCADE_PATH  "cascades/haarcascade_frontalface_default.xml"
#define DET_SCALE_FACTOR   1.01
#define DET_MIN_NEIGHBORS  40
#define DET_MIN_SIZE_RATIO 0.06
#define DET_MAX_SIZE_RATIO 0.18

analyzer_worker::analyzer_worker()
    : m_facedetector(std::string(CASCADE_PATH),
                     DET_SCALE_FACTOR,
                     DET_MIN_NEIGHBORS,
                     DET_MIN_SIZE_RATIO,
                     DET_MAX_SIZE_RATIO)
{
    m_trainingset.clear();
    m_faces.clear();
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

void analyzer_worker::read_training_set(const std::string &list_path, std::vector<cv::Mat> &images)
{
    std::ifstream file(list_path.c_str());
    std::string path;
    while (std::getline(file, path)) {
        images.push_back(cv::imread(path, IMREAD_GRAYSCALE));
    }
}
