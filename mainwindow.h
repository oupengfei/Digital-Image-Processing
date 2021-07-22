#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageprocessing.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ImageProcessing *imageprocessing;
    bool isimgloaded;//判断用于处理的图片是否被加载的标志位


private slots:
    void on_actionopen_triggered();//打开图片

    void on_actionf1_triggered();//获取灰度图像

    void on_actionMean_triggered();//均值滤波

    void on_actionMedian_triggered();//中值滤波

    void on_action_Gaussian_triggered();//高斯滤波

    void on_actionRobert_triggered();//robert算子滤波

    void on_actionSobel_triggered();//sobel算子滤波

    void on_actionPrewitt_triggered();//prewitt算子滤波

    void on_actionLOG_triggered();//log算子滤波

    void on_actionLowpass_triggered();//低通滤波

    void on_actionHighpass_triggered();//高通滤波

    void on_actionsave_triggered();//保存图片

    void on_actionHelp_triggered();//帮助

    void on_actionAbout_triggered();//关于

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
