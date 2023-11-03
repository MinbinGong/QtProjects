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

    bool execute(QWidget *parent, const QString &reference, const QString &target);

private:
    bool compare_image(const cv::Mat &src, const cv::Mat &dst);

private:
    struct comparator {
        bool operator()(std::tuple<std::vector<cv::Point>, bool, double> t1,
                        std::tuple<std::vector<cv::Point>, bool, double> t2) {
            return std::get<2>(t1) > std::get<2>(t2);
        }
    };

};

#endif // ANALYZER_WORKER_H
