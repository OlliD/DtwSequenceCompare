#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <QObject>
#include <QList>

#include "dtw.h"

class DataHolder : public QObject
{
    Q_OBJECT

public:
    explicit DataHolder(QObject *parent = 0);

private:
    QList < QList<DTWResult> > *data;
signals:

public slots:
    void addResult(QList<DTWResult>);
    void getResult(QList<DTWResult>);
};

#endif // DATAHOLDER_H
