#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QVector>
#include <include/qwt_plot.h>
#include <include/qwt_plot_marker.h>
#include <include/qwt_plot_curve.h>
#include <include/qwt_legend.h>
#include <include/qwt_data.h>
#include <include/qwt_text.h>
#include <include/qwt_math.h>
#include <include/qwt_data.h>
#include <include/qwt_array.h>

class PlotWidget : public QwtPlot
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = 0);
    void addDataTempl(double x, double y);
    void addDataObs(double x, double y);
signals:

public slots:
    void dropData();

private:
    QVector<double> *curve_1_x;
    QVector<double> *curve_1_y;
    QVector<double> *curve_2_x;
    QVector<double> *curve_2_y;
    QwtPlot *myPlot;

    QwtPlotCurve *curve1;
    QwtPlotCurve *curve2;
public:
    void diplayData();
};

#endif // PLOTWIDGET_H
