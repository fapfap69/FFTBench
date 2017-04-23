#ifndef MYCHART_H
#define MYCHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class MyChart : public QChartView
{
    Q_OBJECT

 //   Q_OBJECT
public:
    MyChart(QChart *chart, QWidget *parent = 0);


signals:
    void updateSpec(QList<qreal> *a, QList<qreal> *b, int c);

protected:
  //  bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    int _dicotomicSearch(float val);
    void _changeTheSerie(QPointF val);
    bool isValidPoint(QPointF pix, QPointF *val);


private:
    QWidget *theBench;

    int numOfArmonic;

    int ScaleRange;
    int numOfSamples;
    float timeStep;
    float timeInterval;

    QColor theSignalColor;
    QColor theArmonicColor;
    QColor theSinArmonicColor;
    QColor theCosArmonicColor;

    QLineSeries *segnaleCampionato;
    QList<QLineSeries *> armoniche;
    QLineSeries *segnaleRicostruito;

    bool isMousePressed;
    float startT,startV;

    QList<qreal> cs;
    QList<qreal> ss;


};

#endif // MYCHART_H
