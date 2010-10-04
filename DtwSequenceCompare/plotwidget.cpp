#include "plotwidget.h"
#include <include/qwt_plot_curve.h>
#include <QDebug>
#include <qbrush.h>
#include <qcolor.h>

PlotWidget::PlotWidget(QWidget *parent) :
        QwtPlot( parent)
{
    myPlot = new QwtPlot(parent);

    curve_1_x = new QVector<double>;
    curve_1_y = new QVector<double>;

    curve_2_x = new QVector<double>;
    curve_2_y = new QVector<double>;

    curve1 = new QwtPlotCurve("Curve 1");
    curve2 = new QwtPlotCurve("Curve 2");

    myPlot->setAxisScale(1, 0, 50, 1);;
    setAxisAutoScale(2);
    // finally, refresh the plot
    myPlot->replot();

  }

void PlotWidget::addDataTempl(double x, double y){
    //qDebug()<< "Appending new templ value" << x << " and " << y;
    curve_1_x->append(x);
    curve_1_y->append(y*1000);
    //qDebug()<< "Length of the lists now: " << curve_1_x->size() << " and " << curve_1_y->size();

}
void PlotWidget::addDataObs(double x, double y){
    //qDebug()<< "Appending new obs value" << x << " and " << y;
    curve_2_x->append(x);
    curve_2_y->append(y*1000);
    //qDebug()<< "Length of the lists now: " << curve_2_x->size() << " and " << curve_2_y->size();

}

void PlotWidget::diplayData(){
    qDebug()<< "Setting new Data";

    curve1->attach(this);
    curve1->setData(*curve_1_x, *curve_1_y);

    curve2->attach(this);
    curve2->setData(*curve_2_x, *curve_2_y);
    myPlot->replot();
}

void PlotWidget::dropData(){
    curve1->detach();
    curve2->detach();
    //curve_1_x->clear();
    //curve_1_y->clear();
    curve_2_x->clear();
    curve_2_y->clear();
}
