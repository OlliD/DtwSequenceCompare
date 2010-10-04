// Die Klasse bildet ein Zeitfenster der Laenge MSEC. Solange es laeuft werden Daten vom IisTracker
// empfangen und in eine Liste geschrieben. Nach Beendigung wird die Liste ueber das Signal sendResults
// weiter gegeben.


#include "gesturewindow.h"

GestureWindow::GestureWindow(QList<QList<int>* >* gestureTemplate, DataHolder *data, QObject *parent) :
    QObject(parent)
{
    //dataHolder = new DataHolder;
    dataHolder = data;
    dtw = new DTW;
     xList = new QList<int>;
    yList = new QList<int>;
    zList = new QList<int>;
    gesture = new QList < QList <int>* >;
    gesture = gestureTemplate;
    //QObject::connect(this, SIGNAL(sendResult(QList<DTWResult>)), controller, SLOT(receiveData(QList<DTWResult>)));
    //QObject::connect(this->tracker, SIGNAL(sendRightHandPos(QList<int>)),this, SLOT(receiveCoordinatesList(QList<int>)));

    // Der Timer soll immer etwas laenger laufen als fuer das gesuchte Template notwendig
    // Dazu wird geschaut wie viele Koordinaten im Template vorhanden sind und dies
    // mit 50 (der Abtastraste des Tracker) multipliziert.
    // Im Anschluss wird dann noch ein Wert aufaddiert um so diesen Ueberhang zu bekommen
    int msec = gestureTemplate->length() * 50;
    msec = msec + 300;
    QTimer::singleShot(msec, this, SLOT(stopCapture()));
}

void GestureWindow::receiveCoordinatesList(QList<int> list){
    xList->append(list.at(0));
    yList->append(list.at(1));
    zList->append(list.at(2));
}

void GestureWindow::stopCapture(){
    //QObject::disconnect(this->tracker,SIGNAL(sendRightHandPos(QList<int>)), this, SLOT(receiveCoordinatesList(QList<int>)));
    DTWResult result;
    result = dtw->classify(*gesture->at(0), *xList);
    results.append(result);
    result = dtw->classify(*gesture->at(1), *yList);
    results.append(result);
    result = dtw->classify(*gesture->at(2), *zList);
    results.append(result);
    emit sendResult(results);
}


