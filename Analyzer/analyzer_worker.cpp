#include "analyzer_worker.h"

#include <QMessageBox>

#include <opencv2/imgproc/imgproc.hpp>

analyzer_worker::analyzer_worker()
{

}

bool analyzer_worker::execute(QWidget *parent, const QString &reference, const QImage &target)
{
    Q_UNUSED(parent);

    cv::Mat imageRef = cv::imread(reference.toStdString(), 1);
    cv::namedWindow("Reference Image");
    cv::imshow("Reference Image", imageRef);

    cv::Mat imageTarget = convert_opencv_mat(target);
    cv::namedWindow("Target Image");
    cv::imshow("Target Image", imageTarget);

    return compare_image(imageRef, imageTarget);
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

bool analyzer_worker::compare_image(const cv::Mat &src, const cv::Mat &dst)
{
    Q_UNUSED(src);
    Q_UNUSED(dst);

    return true;
}

cv::Mat analyzer_worker::calculate_light_pattern(cv::Mat img)
{
    cv::Mat pattern;

    //通过使用相对于图像大小的大内核尺寸模糊得到背景图
    cv::blur(img, pattern, cv::Size(img.cols / 3, img.cols / 3));

    return pattern;
}

cv::Mat analyzer_worker::remove_light(cv::Mat img, cv::Mat pattern)
{
    cv::Mat img32, patter32;

    img.convertTo(img32, CV_32F);
    pattern.convertTo(patter32, CV_32F);

    //通过背景图像移除背景
    cv::Mat result = 1 - (patter32/img32);
    result *= 255;
    result.convertTo(result, CV_8U);

    return result;
}

cv::Mat analyzer_worker::prepare_image(cv::Mat input)
{
    // 去噪
    cv::Mat img_noise;
    cv::GaussianBlur(input, img_noise, cv::Size(5, 5), 0, 0);

    // 去除背景
    cv::Mat light_pattern = calculate_light_pattern(img_noise);
    cv::Mat img_no_light = remove_light(img_noise, light_pattern);

    //阈值化处理
    cv::Mat result;
    cv::threshold(img_no_light, result, 30, 255, cv::THRESH_BINARY);

    return result;
}

int analyzer_worker::target_dectation(std::string path)
{
    //读取图像
    cv::Mat imageRGB = cv::imread(path, cv::IMREAD_COLOR);
    if (imageRGB.empty())
    {
        return -1;
    }

    cv::Mat imageGray;
    cv::cvtColor(imageRGB, imageGray, cv::COLOR_RGB2GRAY);
    cv::imshow("ImageGrey", imageGray);
    cv::waitKey(0);

    //去除噪声
    cv::GaussianBlur(imageGray, imageGray, cv::Size(5,5), 0, 0);
    //获得背景
    cv::Mat imgPattern = calculate_light_pattern(imageGray);
    //移除背景
    imageGray = remove_light(imageGray, imgPattern);
    cv::imshow("ImageGray", imageGray);
    cv::waitKey(0);

    //阈值化
    cv::Mat imageThr;
    cv::threshold(imageGray, imageThr, 50, 255, cv::THRESH_BINARY);
    cv::imshow("thr", imageThr);
    cv::waitKey(0);

    return 0;
}
