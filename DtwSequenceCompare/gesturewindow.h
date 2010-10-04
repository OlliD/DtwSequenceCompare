// This class builds an sliding windows with a given length,
// the sequence will be written to an vector

#ifndef GESTUREWINDOW_H
#define GESTUREWINDOW_H

#include <QObject>
#include <QTimer>
#include <QList>

//#include "iisutracker.h"
#include "dataholder.h"
#include "dtw.h"

class GestureWindow : public QObject
{
    Q_OBJECT
public:
    explicit GestureWindow(QList<QList<int>* >*, DataHolder*, QObject *parent = 0);
    //explicit GestureWindow(QList<QList<int>* >*, IisuTracker*, DataHolder*, QObject *parent = 0);
    bool stopCaptureSignal;
private:
    //IisuTracker *tracker;
    QList< QList<int>* >* gesture;
    QList< int > *xList;
    QList< int > *yList;
    QList< int > *zList;
    DTW *dtw;
    QList<DTWResult> results;
    DataHolder *dataHolder;

signals:
    void sendResult(QList <DTWResult>);

public slots:
    void stopCapture();
    void receiveCoordinatesList(QList<int>);
};

#endif // GESTUREWINDOW_H
