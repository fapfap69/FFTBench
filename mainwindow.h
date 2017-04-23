#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <timechart.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    TimeChart *Bench;

};

#endif // MAINWINDOW_H
