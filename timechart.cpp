#include "timechart.h"
#include <QLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDebug>
#include <QBarSeries>
#include <QBarSet>
#include <QDebug>

#include <mychart.h>

QT_CHARTS_USE_NAMESPACE

TimeChart::TimeChart(QWidget *parent) : QWidget(parent)
{

    ScaleRange = 15;
    t0 = 0;
    tend = 1;
    tstep = 0.005;


    Graphico = new QChart();
       Graphico->legend()->hide();

    chartView = new MyChart(Graphico, this);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setMinimumSize(QSize(800,400));

    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(chartView,0,0);



    SpettroCoseno = new QBarSet("Cosine");
    SpettroSeno = new QBarSet("Sine");
    SpettroCoseno->setColor(QColor(200,0,0));
    SpettroSeno->setColor(QColor(0,0,200));


    QChart *BarreSpettro = new QChart();
     //  BarreSpettro->legend()->hide();
  //     Graphico->createDefaultAxes();
       BarreSpettro->setTitle("Spectrum");

    Spettro = new QChartView(BarreSpettro);
       Spettro->setRenderHint(QPainter::Antialiasing);
       Spettro->setMinimumSize(QSize(800,100));

    gridLayout->addWidget(Spettro,1,0);


    connect(chartView, SIGNAL(updateSpec(QList<qreal> *, QList<qreal>*, int)), this, SLOT(updateSpectrum(QList<qreal> *,QList<qreal> *,int)));
}

void  TimeChart::updateSpectrum(QList<qreal> *sine, QList<qreal> *cosine, int number )
{

    SpettroCoseno->remove(0,SpettroCoseno->count());
    SpettroSeno->remove(0,SpettroSeno->count());
    SpettroCoseno->append(*cosine);
    SpettroSeno->append(*sine);

    QBarSeries *spettroSeries = new QBarSeries();
    spettroSeries->append(SpettroCoseno);
    spettroSeries->append(SpettroSeno);
    spettroSeries->setBarWidth(1);

    Spettro->chart()->removeAllSeries();
    Spettro->chart()->addSeries(spettroSeries);

    Spettro->update();

}

float TimeChart::redraw()
{
   // int nSources = sources.size();
   // Graphico->removeAllSeries();


    Graphico->createDefaultAxes();
    Graphico->axisY()->setRange(-ScaleRange,ScaleRange);
    chartView->repaint();

    return(0);
}

