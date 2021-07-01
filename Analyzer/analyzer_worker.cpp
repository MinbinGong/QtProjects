#include "analyzer_worker.h"

#include <QMessageBox>

analyzer_worker::analyzer_worker()
{

}

void analyzer_worker::execute(QWidget *parent, const QString &reference, const QImage &target)
{
    Q_UNUSED(parent);
    Q_UNUSED(target);

    cv::Mat imageRef = cv::imread(reference.toStdString(), 1);
    cv::namedWindow("Reference Image");
    cv::imshow("Reference Image", imageRef);

    cv::Mat imageTarget = convert_opencv_mat(target);
    cv::namedWindow("Target Image");
    cv::imshow("Target Image", imageTarget);
}

cv::Mat analyzer_worker::convert_opencv_mat(const QImage &inImage, bool inCloneImageData)
{
    switch ( inImage.format() )
    {
    // 8-bit, 4 channel
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat  mat( inImage.height(), inImage.width(),
                      CV_8UC4,
                      const_cast<uchar*>(inImage.bits()),
                      static_cast<size_t>(inImage.bytesPerLine())
                      );

        return (inCloneImageData ? mat.clone() : mat);
    }

    // 8-bit, 3 channel
    case QImage::Format_RGB32:
    case QImage::Format_RGB888:
    {
        if ( !inCloneImageData )
        {
        }

        QImage   swapped = inImage;

        if ( inImage.format() == QImage::Format_RGB32 )
        {
            swapped = swapped.convertToFormat( QImage::Format_RGB888 );
        }

        swapped = swapped.rgbSwapped();

        return cv::Mat( swapped.height(), swapped.width(),
                        CV_8UC3,
                        const_cast<uchar*>(swapped.bits()),
                        static_cast<size_t>(swapped.bytesPerLine())
                        ).clone();
    }

    // 8-bit, 1 channel
    case QImage::Format_Indexed8:
    {
        cv::Mat  mat( inImage.height(), inImage.width(),
                      CV_8UC1,
                      const_cast<uchar*>(inImage.bits()),
                      static_cast<size_t>(inImage.bytesPerLine())
                      );

        return (inCloneImageData ? mat.clone() : mat);
    }

    default:
        break;
    }

    return cv::Mat();
}
