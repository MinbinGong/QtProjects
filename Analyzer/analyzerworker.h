#ifndef ANALYZERWORKER_H
#define ANALYZERWORKER_H

#include <QString>
#include <QWidget>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "facedetector.h"

#include <tuple>
#include <vector>
#include <memory>

class analyzer_worker
{
public:
    explicit analyzer_worker();
    ~analyzer_worker();

    bool execute(QWidget *parent, const QString &reference, const QString &target);

private:
    bool compare_image(const cv::Mat &src, const cv::Mat &dst);
    std::shared_ptr<std::vector<cv::Rect>> detect(const cv::Mat &src_image);

private:
    cv::CascadeClassifier face_cascade;
    std::vector<cv::Rect> faces;

private:
    struct comparator {
        bool operator()(std::tuple<std::vector<cv::Point>, bool, double> t1,
                        std::tuple<std::vector<cv::Point>, bool, double> t2) {
            return std::get<2>(t1) > std::get<2>(t2);
        }
    };    
};

#endif // ANALYZERWORKER_H
