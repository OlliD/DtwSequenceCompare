#ifndef DTWCONTROLLER_H
#define DTWCONTROLLER_H

#include <QObject>
#include <QList>

#include "dtw.h"
//#include "iisutracker.h"
#include "filetracker.h"
#include "gesturewindow.h"
#include "dataholder.h"

class DtwController : public QObject
{
    Q_OBJECT
public:
    explicit DtwController(QObject *parent = 0 );

signals:
    void sendSequenceSimilarity(float);
    void sendResult(QString);
    void sendMatrix( QVector<QVector<int> >, QString);
    void sendSrcVecSize(int);
    void appendFittedX(double, double);
    void appendFittedY(double, double);
    void appendFittedZ(double, double);
    void dropPlotData();
    void displayXResults(QString);
    void displayYResults(QString);
    void displayZResults(QString);
    void displayWinDow(QString);

public slots:
    void setTemplateSequence(QList< QList<int>* >*);
    void setSequence(QList< QList<int>* >*);
    void setScaleFactor(int);
    void receiveData(QList <DTWResult>);
    void setObservationDuration(int);
    void spawnGestureWindow();
    void startObservation();
    void selectTracker(QString);
    void calculateDistance();
    void calculateConcatenated();
    void calculateSequence();

private:
    QList < QList<int>* > *templateGesture;
    QList < QList<int>* > *sequence;
    DTW *dtw;
    DTWResult *result;
    int scaleFactor;
    int templateDuration;
    //IisuTracker *tracker;
    DataHolder *dataholder;


public:
    FileTracker *fileTracker;

};

#endif // DTWCONTROLLER_H
