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

    bool execute(QWidget *parent, const QString &reference, const QImage &target);

private:
    cv::Mat convert_opencv_mat( const QImage &inImage, bool inCloneImageData = true);
    bool compare_image(const cv::Mat &src, const cv::Mat &dst);
    cv::Mat calculate_light_pattern(cv::Mat img);
    cv::Mat remove_light(cv::Mat img, cv::Mat pattern);
    cv::Mat prepare_image(cv::Mat input);
    int target_dectation(std::string path);
};

#endif // ANALYZER_WORKER_H
