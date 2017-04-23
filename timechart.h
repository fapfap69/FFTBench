#ifndef TIMECHART_H
#define TIMECHART_H

#include <QWidget>
#include <QLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <mychart.h>
#include <QBarSet>

QT_CHARTS_USE_NAMESPACE
class TimeChart : public QWidget
{
    Q_OBJECT
public:
    explicit TimeChart(QWidget *parent = 0);

signals:

public slots:
    float redraw();
    void  updateSpectrum(QList<qreal> *sine, QList<qreal> *cosine, int number );

protected:

private:

    float t0;
    float tend;
    float tstep;

    bool showComponents;
    float ScaleRange;

    QBarSet *SpettroCoseno;
    QBarSet *SpettroSeno;

    QList<QLineSeries*> series;

    QChartView *Spettro;
    QChart *Graphico;
    MyChart *chartView;
    QGridLayout *gridLayout;
};

#endif // TIMECHART_H
