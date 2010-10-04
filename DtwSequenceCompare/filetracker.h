#ifndef FILETRACKER_H
#define FILETRACKER_H

#include <QObject>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QList>
#include <QWidget>

class FileTracker : public QWidget
{
    Q_OBJECT
public:
    explicit FileTracker(QWidget *parent = 0);
    void initialize();

signals:
    void sendSequence(QList< QList<int>* >*);
    void sendXValue(double, double);
    void sendYValue(double, double);
    void sendZValue(double, double);

public slots:

private:
    void processLine(QByteArray);
    QList<int> *xList;
    QList<int> *yList;
    QList<int> *zList;
    QList< QList<int>* > *coordinatesList;
    QFile *file;
    int scaleFactor;
    int timeline;

};

#endif // FILETRACKER_H
