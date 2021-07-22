#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->isimgloaded = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionopen_triggered()//点击open之后的动作
{
    //打开文件对话框，选择文件
    QString filename = QFileDialog::getOpenFileName(this,
                                                            "please choose a picture",
                                                            "F:",
                                                            "picture(*jpg);;"
                                                            "picture(*png)");
     if(filename.isEmpty())
     {
         return;
     }

     else
     {
        //将图像加载到img1中
        QImage* img1=new QImage;

        bool isexit = img1->load(filename);
        //定义ImageProcessing类对象imageprocessing，用img1初始化
        imageprocessing = new ImageProcessing(img1);


        if(! isexit ) //判断图像是否正确加载
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img1;
            return;
        }


        //获取图像储存并存入对象中的变量中
        imageprocessing->imgwidth = imageprocessing->img.width();
        imageprocessing->imgheight = imageprocessing->img.height();
        //获取灰度图像并存储到对象中的变量中
        imageprocessing->imggrey = imageprocessing->img2grey(imageprocessing->img);

        //获取一维灰度数组并存入对象变量
        imageprocessing->greyQVecter.resize(imageprocessing->img.width() * imageprocessing->img.height());

        imageprocessing->greyQVecter = imageprocessing->img2greyQVecter(imageprocessing->img);


        //重新设置窗口的大小，适应图片大小
        resize(imageprocessing->img.width()+20, imageprocessing->img.height() +
               frameGeometry().height() - geometry().height()+20);

        ui->label->setGeometry(10,10,imageprocessing->img.width(), imageprocessing->img.height());
        //ui->label->setPixmap(QPixmap::fromImage(*imageprocessing->img));
        /*imageprocessing->imgpro = imageprocessing->greyQVecter2img(imageprocessing->greyQVecter,
                                                                   imageprocessing->img->width(),
                                                                   imageprocessing->img->height());*/
        //加载图像到窗口
        ui->label->setPixmap(QPixmap::fromImage(imageprocessing->img));
        //设置图像加载成功位
        this->isimgloaded = true;
        QMessageBox::information(NULL, "Open", "Image loaded");
        qDebug()<<"The image is loaded successfully and the size is obtained. The gray image and one dimensional gray image array are generated";

      }
}

void MainWindow::on_actionf1_triggered()//计算图片的灰度直方图
{

    if(this->isimgloaded)
    {
        imageprocessing->calculateHistograms();

        ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

    }

    else
    {
       QMessageBox::warning(NULL, "Warning", "No image is loaded");
    }


}

void MainWindow::on_actionMean_triggered()//均值滤波
{
    if(this->isimgloaded)
    {
        imageprocessing->meanFiltering();
        ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

    }

    else
    {
       QMessageBox::warning(NULL, "Warning", "No image is loaded");
    }

}

void MainWindow::on_actionMedian_triggered()//中值滤波
{
    if(this->isimgloaded)
    {
        imageprocessing->medianFiltering();
        ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

    }

    else
    {
       QMessageBox::warning(NULL, "Warning", "No image is loaded");
    }
}

void MainWindow::on_action_Gaussian_triggered()//高斯滤波
{
    if(this->isimgloaded)
    {
        imageprocessing->gaussianFiltering();
        ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

    }

    else
    {
       QMessageBox::warning(NULL, "Warning", "No image is loaded");
    }
}

void MainWindow::on_actionRobert_triggered()
{
    if(this->isimgloaded)
    {
        imageprocessing->robertEdgeExtract();
        ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

    }

    else
    {
       QMessageBox::warning(NULL, "Warning", "No image is loaded");
    }
}

void MainWindow::on_actionSobel_triggered()
{
    if(this->isimgloaded)
        {
            imageprocessing->sobelEdgeExtract();
            ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

        }

        else
        {
           QMessageBox::warning(NULL, "Warning", "No image is loaded");
        }
}

void MainWindow::on_actionPrewitt_triggered()
{
    if(this->isimgloaded)
        {
            imageprocessing->prewittEdgeExtract();
            ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

        }

        else
        {
           QMessageBox::warning(NULL, "Warning", "No image is loaded");
        }
}

void MainWindow::on_actionLOG_triggered()
{
    if(this->isimgloaded)
        {
            imageprocessing->logEdgeExtract();
            ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

        }

        else
        {
           QMessageBox::warning(NULL, "Warning", "No image is loaded");
        }
}

void MainWindow::on_actionLowpass_triggered()
{
    if(this->isimgloaded)
        {
            imageprocessing->lowpassEnhance();
            ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

        }

        else
        {
           QMessageBox::warning(NULL, "Warning", "No image is loaded");
        }
}

void MainWindow::on_actionHighpass_triggered()
{
    if(this->isimgloaded)
        {
            imageprocessing->highpassEnhance();
            ui->label->setPixmap(QPixmap::fromImage(imageprocessing->imgpro));

        }

        else
        {
           QMessageBox::warning(NULL, "Warning", "No image is loaded");
        }
}

void MainWindow::on_actionsave_triggered()
{
    if(this->isimgloaded)
        {
            QString filePath = QFileDialog::getExistingDirectory(this, "Please choose a path ... ", "./");
            QDateTime time = QDateTime::currentDateTime();   //获取当前时间
            int timeT = time.toTime_t();   //将当前时间转为时间戳

            filePath.append("/ImageProcessed-").append(filePath.number(timeT)).append(".jpg");
            qDebug()<<filePath;
            imageprocessing->imgpro.save(filePath, "JPG", 100);
            QMessageBox::information(NULL, "Save", "Image saved");
            //imageprocessing->img = imageprocessing->imgpro;

        }

        else
        {
           QMessageBox::warning(NULL, "Warning", "No image is loaded");
        }
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(NULL, "About", "Digital image processing, written by Qt5.12\n20216149-Ou Pengfei");
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::about(NULL, "Help", "Too easy to help");
}
