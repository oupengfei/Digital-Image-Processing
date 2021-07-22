#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Digital Image Processing");
    /*QString strpath = QApplication::applicationDirPath();
    strpath += "/ico/help.png";
    w.setWindowIcon(QIcon(strpath));*/
    w.show();
    return a.exec();
}
