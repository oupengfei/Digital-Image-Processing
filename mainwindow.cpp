#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>


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


void MainWindow::on_actionopen_triggered()
{

    //connect(this,SIGNAL(send()),imageprocessing,SLOT(recvData()));
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
        QImage* img1=new QImage;
        bool isexit = img1->load(filename);

        imageprocessing = new ImageProcessing(img1);


        if(! isexit ) //判断图像是否正确加载
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img1;
            return;
        }
        imageprocessing->imgwidth = imageprocessing->img.width();
        imageprocessing->imgheight = imageprocessing->img.height();

        imageprocessing->imggrey = imageprocessing->img2grey(imageprocessing->img);
        imageprocessing->greyQVecter.resize(imageprocessing->img.width() * imageprocessing->img.height());

        qDebug()<<"greyQVecter-count:";
        qDebug()<<imageprocessing->greyQVecter.count();


        imageprocessing->greyQVecter = imageprocessing->img2greyQVecter(imageprocessing->img);
        qDebug()<<"greyQVecter-test:";
        qDebug()<<imageprocessing->greyQVecter[100];

        resize(imageprocessing->img.width()+20, imageprocessing->img.height() +
               frameGeometry().height() - geometry().height()+20);
        ui->label->setGeometry(10,10,imageprocessing->img.width(), imageprocessing->img.height());
        //ui->label->setPixmap(QPixmap::fromImage(*imageprocessing->img));
        /*imageprocessing->imgpro = imageprocessing->greyQVecter2img(imageprocessing->greyQVecter,
                                                                   imageprocessing->img->width(),
                                                                   imageprocessing->img->height());*/

        ui->label->setPixmap(QPixmap::fromImage(imageprocessing->img));








        this->isimgloaded = true;

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
       qDebug()<<"no image loaded";
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
       qDebug()<<"no image loaded";
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
       qDebug()<<"no image loaded";
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
       qDebug()<<"no image loaded";
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
       qDebug()<<"no image loaded";
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
           qDebug()<<"no image loaded";
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
           qDebug()<<"no image loaded";
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
           qDebug()<<"no image loaded";
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
           qDebug()<<"no image loaded";
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
           qDebug()<<"no image loaded";
        }
}

void MainWindow::on_actionsave_triggered()
{
    if(this->isimgloaded)
        {
            imageprocessing->img = imageprocessing->imgpro;

        }

        else
        {
           qDebug()<<"no image loaded";
        }
}
