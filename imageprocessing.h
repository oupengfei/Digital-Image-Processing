#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class ImageProcessing
{
public:
    ImageProcessing(QImage *img0);
    QImage img;
    void calculateHistograms();
    void meanFiltering();
    void medianFiltering();
    void gaussianFiltering();
    void robertEdgeExtract();
    void sobelEdgeExtract();
    void prewittEdgeExtract();
    void logEdgeExtract();
    void lowpassEnhance();
    void highpassEnhance();
    char mediansort(QVector<char> &sort);
    QImage img2grey(QImage &img);
    QVector<char> img2greyQVecter(QImage &img);
    QImage greyQVecter2img(QVector<char> greyvecter , int width , int height);
    QVector<char> greyQVecter;
    int index(int iheight , int iwidth);
    QImage imgpro;
    QImage imggrey;
    int imgwidth;
    int imgheight;



};

#endif // IMAGEPROCESSING_H
