#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T15:55:55
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FFTBench
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    timechart.cpp \
    mychart.cpp \
    fft.cpp

HEADERS  += mainwindow.h \
    timechart.h \
    mychart.h \
    fft.h

FORMS    += mainwindow.ui
