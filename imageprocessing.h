#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class ImageProcessing
{
public:
    ImageProcessing(QImage *img0);

    QImage img;//接收待处理图片
    QImage imgpro;//存储处理之后的图像
    QImage imggrey;//存储待处理的灰度图像

    //图片的宽和高
    int imgwidth;
    int imgheight;

    void calculateHistograms();//计算灰度直方图，实际用来计算灰度图

    //以下为滤波函数
    void meanFiltering();
    void medianFiltering();
    void gaussianFiltering();

    //以下为边缘提取函数
    void robertEdgeExtract();//边缘提取函数
    void sobelEdgeExtract();
    void prewittEdgeExtract();
    void logEdgeExtract();

    //以下为增强函数
    void lowpassEnhance();
    void highpassEnhance();

    char mediansort(QVector<char> &sort);//用于寻找一组数中的中间值，用于中值滤波中

    QImage img2grey(QImage &img);//将图像转换为灰度图

    QVector<char> img2greyQVecter(QImage &img);//将灰度图像转换为一维数组

    QImage greyQVecter2img(QVector<char> greyvecter , int width , int height);//将一维数组转换为QImage图片

    QVector<char> greyQVecter;//用于存储灰度图像一维数组

    int index(int iheight , int iwidth);//将二维下标转化成一维线性下标

};

#endif // IMAGEPROCESSING_H
