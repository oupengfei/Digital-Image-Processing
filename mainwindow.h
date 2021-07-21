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
    bool isimgloaded;//判断勇于处理的图片是否被加载


private slots:
    void on_actionopen_triggered();

    void on_actionf1_triggered();

    void on_actionMean_triggered();

    void on_actionMedian_triggered();

    void on_action_Gaussian_triggered();

    void on_actionRobert_triggered();

    void on_actionSobel_triggered();

    void on_actionPrewitt_triggered();

    void on_actionLOG_triggered();

    void on_actionLowpass_triggered();

    void on_actionHighpass_triggered();

    void on_actionsave_triggered();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
