#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QInputDialog>
#include <QFileDialog>
#include <iostream>
#include <QDebug>


#include "dtw.h"
#include "dtwcontroller.h"
#include "plotwidget.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendTemplate(QList< QList<int>* >*);
    void setScaleFactor(int);

public slots:
    void startTracking();
    void openTemplate();
    void setLeftHandState(int);
    void setRightHandState(int);
    void setStatusBar(int);
    void getResult(float res);
    void setSimilarityValue(float);
    void getScaleFactor();
    void setSrcListSize(int);
    void setRemainingTime(int);
    void showResult(QString);
    void paintMatrix( QVector<QVector<int> >, QString);
    void showPlotX();
    void showPlotY();
    void showPlotZ();

    void appendXValue(double, double);
    void appendYValue(double, double);
    void appendZValue(double, double);
    void appendXTemplateValue(double x, double y);
    void appendYTemplateValue(double x, double y);
    void appendZTemplateValue(double x, double y);

    void setXResults(QString);
    void setYResults(QString);
    void setZResults(QString);

    void setWinDow(QString);

private slots:
    void setSliderLabel(int);

protected:
    void changeEvent(QEvent *e);

private:
    void connectSlots();
    void processLine(QByteArray);
    QList<int>* computeZScores(QList<int>);
    Ui::MainWindow *ui;
    //IisuTracker *tracker;
    DtwController *dtwController;
    DTW *dtw;
    int scaleFactor;
    int timeline;
    PlotWidget *plotX;
    PlotWidget *plotY;
    PlotWidget *plotZ;

    QList<int> *xList;
    QList<int> *yList;
    QList<int> *zList;
    QList< QList<int>* > *coordinatesList;
    QFile *file;
    QPalette *palette;
    QString *templateFile;};

#endif // MAINWINDOW_H
