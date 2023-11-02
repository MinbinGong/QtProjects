#ifndef ANALYZER_WORKER_H
#define ANALYZER_WORKER_H

#include <QString>
#include <QWidget>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <tuple>
#include <vector>

class analyzer_worker
{
public:
    analyzer_worker();
    virtual ~analyzer_worker() {}

    bool execute(QWidget *parent, const QString &reference, const QImage &target);

private:
    void qimage_to_opencv_mat(const QImage &inImage, cv::Mat &outImage);
    void opencv_mat_to_qimage(const cv::Mat &inImage, QImage &outImage);
    bool compare_image(const cv::Mat &src, const cv::Mat &dst);
//    cv::Mat prepare_image(cv::Mat& input);
//    void detect_pattern(cv::Mat& image, cv::Mat& templ);

private:
    struct comparator {
        bool operator()(std::tuple<std::vector<cv::Point>, bool, double> t1,
                        std::tuple<std::vector<cv::Point>, bool, double> t2) {
            return std::get<2>(t1) > std::get<2>(t2);
        }
    };

};

#endif // ANALYZER_WORKER_H
