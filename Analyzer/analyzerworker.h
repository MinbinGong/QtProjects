#ifndef ANALYZERWORKER_H
#define ANALYZERWORKER_H

#include <QString>
#include <QWidget>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>

#include "FaceDetector.h"

#include <vector>
//#include <memory>

class analyzer_worker
{
public:
    explicit analyzer_worker();
    ~analyzer_worker();

    bool execute(QWidget *parent, const QString &reference, const QString &target);

private:
    void read_training_set(const std::string &list_path, std::vector<cv::Mat> &images);

private:
    FaceDetector m_facedetector;
    std::vector<cv::Mat> m_trainingset;
    std::vector<cv::Rect> m_faces;
};

#endif // ANALYZERWORKER_H
