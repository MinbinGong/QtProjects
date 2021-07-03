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

    //通过连通组件算法分割
    cv::Mat labels, stats, centroids;
    int num_objects = cv::connectedComponentsWithStats(imageThr, labels, stats, centroids);
    if (num_objects < 2)
    {
        return -1;
    }

    //展示图像分割结果
    cv::Mat output = cv::Mat::zeros(imageThr.rows, imageThr.cols, CV_8UC3);
    cv::RNG rands(0xFFFFFFFF);
    for (int i = 1; i < num_objects; ++i)
    {
        cv::Mat mask = labels == i;
        output.setTo(random_color(rands), mask);

        std::stringstream ss;
        ss << "area: " << stats.at<int>(i, cv::CC_STAT_AREA);

        cv::putText(output, ss.str(), centroids.at<cv::Point2d>(i),
                    cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 255, 255));
    }

    cv::imshow("Result", output);
    cv::waitKey(0);
    return 0;
}

cv::Scalar analyzer_worker::random_color(cv::RNG &rng)
{
    int color = (unsigned)rng;
    return cv::Scalar(color&255, (color >> 8)&255, (color >> 16) & 255);
}

//std::vector<std::vector<float>> analyzer_worker::extract_features(cv::Mat img, std::vector<int> &left, std::vector<int> &top)
//{
//    std::vector<std::vector<cv::Point>> contours;
//    std::vector<cv::Vec4i> hierarchy;
//    cv::Mat input = img.clone();
//    cv::findContours(input, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
//    if (contours.size() == 0)
//    {
//        return std::vector<std::vector<float>>();
//    }

//    std::vector<std::vector<float>> output{};
//    cv::RNG rng(0xFFFFFFFF);
//    for (unsigned int i = 0; i < contours.size(); ++i)
//    {
//        cv::Mat mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
//        //使用值1绘制形状，可以求和统计面积
//        cv::drawContours(mask, contours, i, cv::Scalar(1), cv::FILLED, cv::LINE_8, hierarchy, 1);
//        cv::Scalar area_s = cv::sum(mask);
//        float area = area_s[0];
//        float MIN_AREA = 500;
//        if (area > MIN_AREA)
//        {
//            cv::RotatedRect r = cv::minAreaRect(contours[i]);
//            float width = r.size.width;
//            float height = r.size.height;
//            //第二个特征纵横比
//            float ar = (width < height) ? height / width : width / height;
//            std::vector<float> row;
//            row.push_back(area);
//            row.push_back(ar);
//            output.push_back(row);
//            left.push_back(r.center.x);
//            top.push_back((int)r.center.x);
//        }
//    }

//    return output;
//}
