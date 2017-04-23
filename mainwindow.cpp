#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <timechart.h>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QFont theFont("Arial",13);
    QColor theColor(0,0,60);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Background, theColor);
    this->setWindowTitle("Fourier Work Bench  v.0  - inFrAnto Software (CopyLeft)");

    // -----------------------
    QWidget *centralW = new QWidget(parent);
    QGridLayout *centralL = new QGridLayout(centralW);

    QHBoxLayout *maincontrolL = new QHBoxLayout();
    maincontrolL->setSpacing(0);
    maincontrolL->setMargin(0);
    maincontrolL->setContentsMargins(5,0,0,0);


    QLabel *l = new QLabel("Scale Range ");
    l->setFont(theFont);
    l->setAutoFillBackground(true);
    l->setPalette(palette);
    l->setMaximumWidth(90);
    maincontrolL->addWidget(l);

    centralL->addLayout(maincontrolL,0,1);

    QHBoxLayout *benchL = new QHBoxLayout();
    benchL->setSpacing(0);
    benchL->setMargin(0);
    benchL->setContentsMargins(5,0,0,0);


    Bench = new TimeChart(this);
    benchL->addWidget(Bench);

    centralL->addLayout(benchL,1,1);

    centralW->setLayout(centralL);
    setCentralWidget(centralW);


}

MainWindow::~MainWindow()
{

}
