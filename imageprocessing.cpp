#include "imageprocessing.h"
#include <QDebug>

ImageProcessing::ImageProcessing(QImage *img0)
{
    this->img = *img0;//将待处理图像存储到类的QImage中
    this->imgpro = *img0;//初始化处理之后的图像
    //qDebug()<<"待处理图像加载完毕...";

    /*qDebug()<<"ImageProcessing-img";
    qDebug()<<this->img.bitPlaneCount();
    qDebug()<<"ImageProcessing-imgpro";
    qDebug()<<this->imgpro.bitPlaneCount();*/

}

char ImageProcessing::mediansort(QVector<char> &sort)//寻找数组中间值，输入数组中元素个数应为奇数
{
    //冒泡法排序
    for(int i = 0 ; i<sort.count() - 1 ; i++)
    {
        for (int j = 0; j<sort.count() - 1 - i; j++)
        {
            if (sort[j]>sort[j + 1]) // 从小到大排序，从大到小排序需将“>”换成“<”
            {
                char temp;
                temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
            }

        }
    }
    return sort[(sort.count() - 1)/2];//返回中值

}

QImage ImageProcessing::greyQVecter2img(QVector<char> greyvecter , int width , int height)//将一维数组转换成QImage
//输入：
//      greyvecter  一维灰度图像数组
//      width       输出图像宽度
//      height      输出图像高度
//输出：
//      QImage对象
{
    qDebug()<<"greyQVecter2img";
    //QImage gray = this->img->convertToFormat(QImage::Format_Grayscale8);
    int bytePerLine=(width*24+31)/8;//图像每行字节对齐
    unsigned char * graydata = new unsigned char[bytePerLine * height];//存储用于重建QImage所需要的数据
    for(int i=0;i<height;i++)
    {

        for (int j=0;j<width;j++)
        {
            graydata[i*bytePerLine+j*3]  =greyvecter[this->index(i,j)];
            graydata[i*bytePerLine+j*3+1]=greyvecter[this->index(i,j)];
            graydata[i*bytePerLine+j*3+2]=greyvecter[this->index(i,j)];
        }
    }
    return QImage(graydata, width, height, bytePerLine, QImage::Format_RGB888);

}

int ImageProcessing::index(int iheight , int iwidth)//二维坐标转一维线性下标
//转化顺序为从左到右，从上到下
{
    return iheight * this->img.width() + iwidth;

}

QVector<char> ImageProcessing::img2greyQVecter(QImage &img)//图像转一维灰度数组
//转化顺序为从左到右，从上到下
//输入：
//      img     待处理图像
//输出：
//      QVector<char>   一维灰度数组
{
    qDebug()<<"img2greyQVecter";
    //QImage gray = this->img->convertToFormat(QImage::Format_Grayscale8);

    int iwidth = img.width();//图像宽
    int iheight = img.height();//图像高
    QVector<char> greyvecter(iwidth * iheight);//存储灰度图像，以一维方式存储


    //int bytePerLine=(iwidth*24+31)/8;//图像每行字节对齐

    unsigned char *data = img.bits();//获取图像像素字节数据的首地址

    //这里要注意，采用bits()方法的到的数据data中像素的组织形式应为ARGB，但实际调试中发现，
    //每个像素中从字节从低到高依次是BGRA，
    //unsigned char * graydata = new unsigned char[bytePerLine * iheight];//存储处理后的数据
    unsigned char r,g,b;
    for(int i=0;i<iheight;i++)
    {
        for (int j=0;j<iwidth;j++)
        {
            r = *(data+2);
            g = *(data+1);
            b = *data;
             //设置灰度值    rgb转换灰度值是存在固定的公式的
            greyvecter[this->index(i,j)]  =(r*30+g*59+b*11)/100;

            data+=4;
        }
    }
    return greyvecter;

}

QImage ImageProcessing::img2grey(QImage &img)//彩色图像转灰度图像
{
    qDebug()<<"grey";
    //QImage gray = this->img->convertToFormat(QImage::Format_Grayscale8);

    int iwidget = img.width();//图像宽
    int iheight = img.height();//图像高
    int bytePerLine=(iwidget*24+31)/8;//图像每行字节对齐

    unsigned char *data = img.bits();//获取图像像素字节数据的首地址

    //这里要注意，采用bits()方法的到的数据data中像素的组织形式应为ARGB，但实际调试中发现，
    //每个像素中从字节从低到高依次是BGRA，
    unsigned char * graydata = new unsigned char[bytePerLine * iheight];//存储处理后的数据
    unsigned char r,g,b;
    for(int i=0;i<iheight;i++)
    {
        for (int j=0;j<iwidget;j++)
        {
            r = *(data+2);
            g = *(data+1);
            b = *data;
             //设置灰度值    rgb转换灰度值是存在固定的公式的
            graydata[i*bytePerLine+j*3]  =(r*30+g*59+b*11)/100;
            graydata[i*bytePerLine+j*3+1]=(r*30+g*59+b*11)/100;
            graydata[i*bytePerLine+j*3+2]=(r*30+g*59+b*11)/100;
            data+=4;
        }
    }
    return QImage(graydata, iwidget,iheight,bytePerLine , QImage::Format_RGB888);


}

void ImageProcessing::calculateHistograms()
{
    qDebug()<<"grey";
    /*QImage gray = this->img->convertToFormat(QImage::Format_Grayscale8);

    int iwidget = this->img->width();//图像宽
    int iheight = this->img->height();//图像高
    int bytePerLine=(iwidget*24+31)/8;//图像每行字节对齐

    unsigned char *data = this->img->bits();//获取图像像素字节数据的首地址

    //这里要注意，采用bits()方法的到的数据data中像素的组织形式应为ARGB，但实际调试中发现，
    //每个像素中从字节从低到高依次是BGRA，
    unsigned char * graydata = new unsigned char[bytePerLine * iheight];//存储处理后的数据
    unsigned char r,g,b;
    for(int i=0;i<iheight;i++)
    {
        for (int j=0;j<iwidget;j++)
        {
            r = *(data+2);
            g = *(data+1);
            b = *data;
             //设置灰度值    rgb转换灰度值是存在固定的公式的
            graydata[i*bytePerLine+j*3]  =(r*30+g*59+b*11)/100;
            graydata[i*bytePerLine+j*3+1]=(r*30+g*59+b*11)/100;
            graydata[i*bytePerLine+j*3+2]=(r*30+g*59+b*11)/100;
            data+=4;
        }
    }

    this->imgpro = QImage(graydata, iwidget,iheight,bytePerLine , QImage::Format_RGB888);*/

    this->imgpro = this->imggrey;

}

void ImageProcessing::meanFiltering()//均值滤波,3*3
//直接处理类中的greyQVecter
{
    qDebug()<<"meanFiltering";
    //定义模板
    QVector<double> k{0.11111111112,0.1111111111,0.11111111112,
                         0.11111111112,0.1111111111,0.11111111112,
                         0.1111111111,0.11111111112,0.1111111111} ;
    QVector<char> imgfed(this->imgheight * this->imgwidth);//存储处理后数据
    imgfed = this->greyQVecter;//初始化


    for(int i=1;i<this->imgheight-1;i++)
    {

        for (int j=1;j<this->imgwidth-1;j++)
        {

            imgfed[this->index(i,j)] = this->greyQVecter[this->index(i-1,j-1)] * k[0] +
                                        this->greyQVecter[this->index(i-1,j)] * k[1] +
                                        this->greyQVecter[this->index(i-1,j+1)] * k[2] +
                                        this->greyQVecter[this->index(i,j-1)] * k[3] +
                                        this->greyQVecter[this->index(i,j)] * k[4] +
                                        this->greyQVecter[this->index(i,j+1)] * k[5] +
                                        this->greyQVecter[this->index(i+1,j-1)] * k[6] +
                                        this->greyQVecter[this->index(i+1,j)] * k[7] +
                                        this->greyQVecter[this->index(i+1,j+1)] * k[8];


        }
    }


    this->imgpro = this->greyQVecter2img(imgfed,this->imgwidth,this->imgheight);

}

void ImageProcessing::medianFiltering()//中值滤波，3*3
//直接处理类中的greyQVecter
{
    qDebug()<<"medianFiltering";

    QVector<char> imgfed(this->imgheight * this->imgwidth);
    imgfed = this->greyQVecter;

    QVector<char> sort(9);//存储9个像素点的数组

    for(int i=1;i<this->imgheight-1;i++)
    {

        for (int j=1;j<this->imgwidth-1;j++)
        {
            //像素点数组赋值
            sort[0] = this->greyQVecter[this->index(i-1,j-1)];
            sort[1] = this->greyQVecter[this->index(i-1,j)];
            sort[2] = this->greyQVecter[this->index(i-1,j+1)];
            sort[3] = this->greyQVecter[this->index(i,j-1)];
            sort[4] = this->greyQVecter[this->index(i,j)];
            sort[5] = this->greyQVecter[this->index(i,j+1)];
            sort[6] = this->greyQVecter[this->index(i+1,j-1)];
            sort[7] = this->greyQVecter[this->index(i+1,j)];
            sort[8] = this->greyQVecter[this->index(i+1,j+1)];

            imgfed[this->index(i,j)] = mediansort(sort);//寻找中值，调用median函数

        }
    }


    this->imgpro = this->greyQVecter2img(imgfed,this->imgwidth,this->imgheight);

}
void ImageProcessing::gaussianFiltering()//高斯滤波
//直接处理类中的greyQVecter
{
    qDebug()<<"gaussianFiltering";
    QVector<double> k{0.0625,0.125,0.0625,
                         0.125,0.25,0.125,
                         0.0625,0.125,0.0625} ;//定义模板
    QVector<char> imgfed(this->imgheight * this->imgwidth);//存储处理后数据
    imgfed = this->greyQVecter;//初始化


    for(int i=1;i<this->imgheight-1;i++)
    {

        for (int j=1;j<this->imgwidth-1;j++)
        {

            imgfed[this->index(i,j)] = this->greyQVecter[this->index(i-1,j-1)] * k[0] +
                                        this->greyQVecter[this->index(i-1,j)] * k[1] +
                                        this->greyQVecter[this->index(i-1,j+1)] * k[2] +
                                        this->greyQVecter[this->index(i,j-1)] * k[3] +
                                        this->greyQVecter[this->index(i,j)] * k[4] +
                                        this->greyQVecter[this->index(i,j+1)] * k[5] +
                                        this->greyQVecter[this->index(i+1,j-1)] * k[6] +
                                        this->greyQVecter[this->index(i+1,j)] * k[7] +
                                        this->greyQVecter[this->index(i+1,j+1)] * k[8];


        }
    }



    this->imgpro = this->greyQVecter2img(imgfed,this->imgwidth,this->imgheight);

}

void ImageProcessing::robertEdgeExtract()//robert边缘提取
//直接处理类中的greyQVecter
{
    qDebug()<<"robertEdgeExtract";
    //定义模板，有x，y两个方向
    QVector<double> k1{-1,0,0,1} ;
    QVector<double> k2{0,-1,1,0} ;
    QVector<char> imgfed(this->imgheight * this->imgwidth);
    imgfed = this->greyQVecter;


    for(int i=0;i<this->imgheight-1;i++)
    {

        for (int j=0;j<this->imgwidth-1;j++)
        {

            imgfed[this->index(i,j)] =  this->greyQVecter[this->index(i,j)] * k1[0] *0.5 +
                                        this->greyQVecter[this->index(i,j+1)] * k1[1] *0.5 +
                                        this->greyQVecter[this->index(i+1,j)] * k1[2] *0.5 +
                                        this->greyQVecter[this->index(i+1,j+1)] * k1[3] *0.5 +
                                        this->greyQVecter[this->index(i,j)] * k2[0] *0.5 +
                                        this->greyQVecter[this->index(i,j+1)] * k2[1] *0.5 +
                                        this->greyQVecter[this->index(i+1,j)] * k2[2] *0.5 +
                                        this->greyQVecter[this->index(i+1,j+1)] * k2[3] *0.5;


        }
    }
    this->imgpro = this->greyQVecter2img(imgfed,this->imgwidth,this->imgheight);


}

void ImageProcessing::sobelEdgeExtract()//sobel边缘提取
//直接处理类中的greyQVecter
{
    qDebug()<<"robertEdgeExtract";
    //定义模板，有x，y两个方向
    QVector<double> k1{-1,0,1,
                       -1,0,1,
                       -1,0,1} ;
    QVector<double> k2{-1,-1,-1,
                       0,0,0,
                       1,1,1} ;
    QVector<char> imgfed(this->imgheight * this->imgwidth);
    imgfed = this->greyQVecter;


    for(int i=1;i<this->imgheight-1;i++)
    {

        for (int j=1;j<this->imgwidth-1;j++)
        {

            imgfed[this->index(i,j)] = this->greyQVecter[this->index(i-1,j-1)] * k1[0]*0.5 +
                                        this->greyQVecter[this->index(i-1,j)] * k1[1]*0.5 +
                                        this->greyQVecter[this->index(i-1,j+1)] * k1[2]*0.5 +
                                        this->greyQVecter[this->index(i,j-1)] * k1[3]*0.5 +
                                        this->greyQVecter[this->index(i,j)] * k1[4]*0.5 +
                                        this->greyQVecter[this->index(i,j+1)] * k1[5]*0.5 +
                                        this->greyQVecter[this->index(i+1,j-1)] * k1[6]*0.5 +
                                        this->greyQVecter[this->index(i+1,j)] * k1[7]*0.5 +
                                        this->greyQVecter[this->index(i+1,j+1)] * k1[8]*0.5 +
                                        this->greyQVecter[this->index(i-1,j-1)] * k2[0]*0.5 +
                                        this->greyQVecter[this->index(i-1,j)] * k2[1]*0.5 +
                                        this->greyQVecter[this->index(i-1,j+1)] * k2[2]*0.5 +
                                        this->greyQVecter[this->index(i,j-1)] * k2[3]*0.5 +
                                        this->greyQVecter[this->index(i,j)] * k2[4]*0.5 +
                                        this->greyQVecter[this->index(i,j+1)] * k2[5]*0.5 +
                                        this->greyQVecter[this->index(i+1,j-1)] * k2[6]*0.5 +
                                        this->greyQVecter[this->index(i+1,j)] * k2[7]*0.5 +
                                        this->greyQVecter[this->index(i+1,j+1)] * k2[8]*0.5;


        }
    }
    this->imgpro = this->greyQVecter2img(imgfed,this->imgwidth,this->imgheight);


}

void ImageProcessing::prewittEdgeExtract()//prewitt边缘提取
//直接处理类中的greyQVecter
{
    qDebug()<<"prewittEdgeExtract";
    //定义模板，有x，y两个方向
    QVector<double> k1{-1,0,1,
                       -2,0,2,
                       -1,0,1} ;
    QVector<double> k2{-1,-2,-1,
                       0,0,0,
                       1,2,1} ;
    QVector<char> imgfed(this->imgheight * this->imgwidth);
    imgfed = this->greyQVecter;


    for(int i=1;i<this->imgheight-1;i++)
    {

        for (int j=1;j<this->imgwidth-1;j++)
        {

            imgfed[this->index(i,j)] = this->greyQVecter[this->index(i-1,j-1)] * k1[0]*0.5 +
                                        this->greyQVecter[this->index(i-1,j)] * k1[1]*0.5 +
                                        this->greyQVecter[this->index(i-1,j+1)] * k1[2]*0.5 +
                                        this->greyQVecter[this->index(i,j-1)] * k1[3]*0.5 +
                                        this->greyQVecter[this->index(i,j)] * k1[4]*0.5 +
                                        this->greyQVecter[this->index(i,j+1)] * k1[5]*0.5 +
                                        this->greyQVecter[this->index(i+1,j-1)] * k1[6]*0.5 +
                                        this->greyQVecter[this->index(i+1,j)] * k1[7]*0.5 +
                                        this->greyQVecter[this->index(i+1,j+1)] * k1[8]*0.5 +
                                        this->greyQVecter[this->index(i-1,j-1)] * k2[0]*0.5 +
                                        this->greyQVecter[this->index(i-1,j)] * k2[1]*0.5 +
                                        this->greyQVecter[this->index(i-1,j+1)] * k2[2]*0.5 +
                                        this->greyQVecter[this->index(i,j-1)] * k2[3]*0.5 +
                                        this->greyQVecter[this->index(i,j)] * k2[4]*0.5 +
                                        this->greyQVecter[this->index(i,j+1)] * k2[5]*0.5 +
                                        this->greyQVecter[this->index(i+1,j-1)] * k2[6]*0.5 +
                                        this->greyQVecter[this->index(i+1,j)] * k2[7]*0.5 +
                                        this->greyQVecter[this->index(i+1,j+1)] * k2[8]*0.5;


        }
    }
    this->imgpro = this->greyQVecter2img(imgfed,this->imgwidth,this->imgheight);

}

void ImageProcessing::logEdgeExtract()//log边缘提取
//直接处理类中的greyQVecter
{
    qDebug()<<"logEdgeExtract";
    //定义处理模板
    QVector<double> k{-1,-1,-1,
                      -1,8,-1,
                      -1,-1,-1} ;
    QVector<char> imgfed(this->imgheight * this->imgwidth);
    imgfed = this->greyQVecter;


    for(int i=1;i<this->imgheight-1;i++)
    {

        for (int j=1;j<this->imgwidth-1;j++)
        {

            imgfed[this->index(i,j)] = this->greyQVecter[this->index(i-1,j-1)] * k[0] +
                                        this->greyQVecter[this->index(i-1,j)] * k[1] +
                                        this->greyQVecter[this->index(i-1,j+1)] * k[2] +
                                        this->greyQVecter[this->index(i,j-1)] * k[3] +
                                        this->greyQVecter[this->index(i,j)] * k[4] +
                                        this->greyQVecter[this->index(i,j+1)] * k[5] +
                                        this->greyQVecter[this->index(i+1,j-1)] * k[6] +
                                        this->greyQVecter[this->index(i+1,j)] * k[7] +
                                        this->greyQVecter[this->index(i+1,j+1)] * k[8];
        }
    }



    this->imgpro = this->greyQVecter2img(imgfed,this->imgwidth,this->imgheight);

}

void ImageProcessing::lowpassEnhance()
{
    qDebug()<<"lowpassEnhance";
    this->imgpro = this->img;

}

void ImageProcessing::highpassEnhance()
{
    qDebug()<<"highpassEnhance";
    this->imgpro = this->img;

}
