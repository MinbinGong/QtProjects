#ifndef ANALYZERWORKER_H
#define ANALYZERWORKER_H

#include <QString>
#include <QWidget>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>

#include <vector>
//#include <memory>

class analyzer_worker
{
public:
    explicit analyzer_worker();
    ~analyzer_worker();

    bool execute(QWidget *parent, const QString &reference, const QString &target);

private:
    void detectAndDraw(cv::Mat &img);

private:
    cv::CascadeClassifier mCascade;
    std::vector<cv::Rect> mFaces;
};

#endif // ANALYZERWORKER_H
