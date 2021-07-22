QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    imageprocessing.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    fftw3.h \
    imageprocessing.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/./ -llibfftw3-3 -llibfftw3f-3 -llibfftw3l-3

DISTFILES += \
    ico/VersionManagement.png \
    ico/about.png \
    ico/add_fridge.png \
    ico/help.png \
    ico/save.png \
    ico/添加新的样本盒.png

RESOURCES += \
    ico.qrc
