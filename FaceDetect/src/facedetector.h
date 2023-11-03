#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H
//opencv includes

#include <opencv2/objdetect.hpp>
#include <opencv2/core/types_c.h>

//qt & C++ includes
#include <QImage>
#include <vector>

using namespace cv;
class FaceDetector
{
public:
    FaceDetector();

public slots:
    QImage detect(Mat frame);

private:
    String                   cascade_name;
    cv::CascadeClassifier        face_cascade;
    std::vector<Rect>        foundFaces;
    QList<CvScalar>          colorsCol;
};

#endif // FACEDETECTOR_H
