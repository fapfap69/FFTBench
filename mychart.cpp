#include "mychart.h"
#include <QDebug>
#include "math.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPoint>
#include <QLineSeries>
#include <fft.h>

QT_CHARTS_USE_NAMESPACE

MyChart::MyChart(QChart *chart, QWidget *parent) :
    QChartView(chart, parent)
{
    theBench = parent;

    isMousePressed = false;
    numOfSamples = 1024;
    ScaleRange = 15;
    numOfArmonic = 16;

    timeInterval = 1; //one second
    timeStep = timeInterval / numOfSamples;

    theSignalColor.setRgb(5,5,5);
    theArmonicColor.setRgb(0,120,0);
    theSinArmonicColor.setRgb(180,0,0);
    theCosArmonicColor.setRgb(0,0,180);

    segnaleCampionato = new QLineSeries();
    segnaleCampionato->setPen(QPen(theSignalColor,3));
    segnaleCampionato->setName("Sampled Signal");
    for(int i=0;i<numOfSamples;i++) segnaleCampionato->append(QPointF(i*timeStep,0.0));
    chart->addSeries(segnaleCampionato);
    segnaleRicostruito = new QLineSeries();
    segnaleRicostruito->setPen(QPen(theSinArmonicColor,2));
    segnaleRicostruito->setName("Reconstructed Signal");
    chart->addSeries(segnaleRicostruito);


    QLineSeries *s;
    for(int j=0;j<numOfArmonic;j++) {
        s = new QLineSeries();
        s->setPen(QPen(theArmonicColor,1));
        s->setName(QString::number(j+1));
        armoniche.append(s);
        chart->addSeries(s);
    }

    chart->createDefaultAxes();
    chart->axisY()->setRange(-ScaleRange,ScaleRange);
    chart->setTitle("Draw the Sample Curve !");

}

void MyChart::mousePressEvent(QMouseEvent *event)
{
    QPointF pix,val;
    pix = event->localPos();

    if(isValidPoint(pix,&val)) {
        isMousePressed = true;
        startT = val.x();
        startV = val.y();
    }
}

void MyChart::mouseMoveEvent(QMouseEvent *event)
{
    if(!isMousePressed) return;

    QPointF pix,val;
    pix = event->localPos();

    if(isValidPoint(pix,&val)) {
        _changeTheSerie(val);
    }
}

bool MyChart::isValidPoint(QPointF pix, QPointF *val)
{
    QChart *c = this->chart();
    *val = c->mapToValue(pix);
    if(val->x()<0 || val->x() > timeInterval || fabs(val->y()) > ScaleRange) return(false);
    return(true);
}

void MyChart::_changeTheSerie(QPointF val)
{
    float endT = val.x();
    float endV = val.y();
    int stInd = _dicotomicSearch(startT);
    int enInd = _dicotomicSearch(endT);
    int disp = (stInd < enInd) ? 1: -1;
    int i = stInd;

    float m = (endV - startV)/(endT - startT);
    float n = (endT*startV - startT*endV) / (endT-startT);
    float nval;
    float temp;
    while(i != enInd) {
        temp = segnaleCampionato->at(i).x();
        nval = m * temp + n;
        segnaleCampionato->replace(i, temp,nval);
        i += disp;
    }

    startT = endT;
    startV = endV;
    this->update();
}

int MyChart::_dicotomicSearch(float val)
{
    QPointF p;
    int low = 0;
    int high = segnaleCampionato->count() - 1;
    int midpoint = 0;
    while (low <= high) {
        midpoint = low + (high - low)/2;
        p = segnaleCampionato->at(midpoint);
        if (val == p.x()) {
            return( midpoint);
        } else {
            if (val < p.x())
                high = midpoint - 1;
            else
                low = midpoint + 1; //when key is > array[midpoint]
        }
    }
    return(midpoint);
}

void MyChart::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed=false;
    CArray data( segnaleCampionato->count() );

    float PI = asin(1.0) * 2;
    float PI2 = asin(1.0) * 4;

    qDebug() << "Start the FFT...";
    for(int i=0;i< segnaleCampionato->count() - 1;i++) {
        data[i] = Complex( segnaleCampionato->at(i).y(),0 );
    }
    FFT *theFFT = new FFT(data);
    qDebug() << "FFT DONE !";

    cs.clear();
    ss.clear();

     for(int g=0;g<128;g++) {
        cs.append(data[g].real()/512);
        ss.append(data[g].imag()/512);
    }

    float ric[2000];
    for(int i=0; i<numOfSamples; i++) ric[i] = 0;

    data[0] = data[0] / 2.0;
    for(int k=0;k<numOfArmonic*2;k++) {
        if(k<numOfArmonic) armoniche.at(k)->clear();
        float cosamp = data[k].real()/512;
        float sinamp = data[k].imag()/512;

        for(int i=0; i<numOfSamples; i++) {
            float x,y;
            x = i * timeStep;
            y = (cosamp * cos( PI2 * k * x)) + (sinamp * sin( PI2 * k * x)) ;
            if(k<numOfArmonic) armoniche.at(k)->append(QPointF(x,y));
            ric[i] += y;
        }
    }
    segnaleRicostruito->clear();
    for(int i=0; i<numOfSamples; i++) {
        segnaleRicostruito->append(QPointF( i * timeStep, ric[i]));
    }

    this->update();
    emit updateSpec(&ss, &cs, 512);


}

void MyChart::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "keyPressEvent" ;

}
