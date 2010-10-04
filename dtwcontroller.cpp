#include "dtwcontroller.h"
#include <QDebug>
#include <QTimer>
#include <QVector>
#include <math.h>
#include "gesturewindow.h"


DtwController::DtwController(QObject *parent) :
    QObject(parent)
{
    dtw = new DTW();
    //scaleFactor = 0;
    result = new DTWResult();
    templateDuration = 100;
    //tracker = new IisuTracker();
    //tracker = iisuTracker;
    dataholder = new DataHolder();
    fileTracker = new FileTracker();

}

void DtwController::setTemplateSequence(QList < QList<int>* > *list){
    templateGesture = list;
    qDebug() << "dtwController: got new template with the length " << templateGesture->length();
    //calculateDistance();
}

void DtwController::setScaleFactor(int i){
    DtwController::scaleFactor = i;
    qDebug() << "scale factor set to: " << DtwController::scaleFactor;
}

void DtwController::calculateDistance(){

    //qDebug() << "now starts the dtw";
    const QList<int> templx = *templateGesture->at(0);
    const QList<int> obsx = *sequence->at(0);
    DTWResult resx = dtw->classify(templx, obsx);
    //qDebug() << "got the results " << resx.distance;
    QVector<QVector<int> > matrix;
    matrix = resx.D;
    emit sendMatrix(matrix, "x");

    const QList<int> temply = *templateGesture->at(1);
    const QList<int> obsy = *sequence->at(1);
    DTWResult resy = dtw->classify(temply, obsy);
    //qDebug() << "got the results " << resy.distance;

    matrix = resy.D;
    emit sendMatrix(matrix, "y");

    const QList<int> templz = *templateGesture->at(2);
    const QList<int> obsz = *sequence->at(2);
    DTWResult resz = dtw->classify(templz, obsz);
    //qDebug() << "got the results " << resz.distance;

    matrix = resz.D;
    emit sendMatrix(matrix, "z");

}

void DtwController::calculateConcatenated(){

    QList<int> templ_concat;
    QList<int> xList = *templateGesture->at(0);
    QList<int> yList = *templateGesture->at(1);
    QList<int> zList = *templateGesture->at(2);
    for(int i = 0; i < xList.size(); i++){
        templ_concat.append( xList.at(i) );
    }
    qDebug() << "length is: " << templ_concat.length();

    for(int i = 0; i < yList.size(); i++){
        templ_concat.append( yList.at(i) );
    }
    qDebug() << "length is: " << templ_concat.length();

    for(int i = 0; i < zList.size(); i++){
        templ_concat.append( zList.at(i) );
    }
    qDebug() << "length is: " << templ_concat.length();

    QList<int> seq_concat;
    QList<int> xsList = *sequence->at(0);
    QList<int> ysList = *sequence->at(1);
    QList<int> zsList = *sequence->at(2);
    for(int i = 0; i < xsList.size(); i++){
        seq_concat.append( xsList.at(i) );
    }
    //qDebug() << "length is: " << seq_concat.length();

    for(int i = 0; i < ysList.size(); i++){
        seq_concat.append( ysList.at(i) );
    }
    //qDebug() << "length is: " << seq_concat.length();

    for(int i = 0; i < zsList.size(); i++){
        seq_concat.append( zsList.at(i) );
    }
    //qDebug() << "length is: " << seq_concat.length();

    DTWResult resz = dtw->classify(templ_concat, seq_concat);

    //qDebug() << "got the results " << resz.distance / scaleFactor;


}

void DtwController::calculateSequence(){
    QMap<int, float> xMap;
    QMap<int, float> yMap;
    QMap<int, float> zMap;

    float xmin=1000000;
    int xminPos = 0;
    float ymin=1000000;
    int yminPos = 0;
    float zmin=1000000;
    int zminPos = 0;
    int timeWindow = templateGesture->at(0)->length();
    timeWindow = timeWindow * 1;
    qDebug() << "timewindow is:  " << timeWindow;
    QList<int> xsList = *sequence->at(0);
    QList<int> ysList = *sequence->at(1);
    QList<int> zsList = *sequence->at(2);
    QList<int> xWindow;
    QList<int> yWindow;
    QList<int> zWindow;
    emit dropPlotData();
    for (int i = 0; i < sequence->at(0)->length(); i+=8){
        //qDebug() << "results of window ... i:  " << i/8 <<" with start at: " << i;
        xWindow.clear();
        yWindow.clear();
        zWindow.clear();
        for (int j = 0 + i; j < timeWindow+i; j++){
            //qDebug() << "calulating ... j:  " << j ;
            if (j < xsList.length()){
                xWindow.append(xsList.at(j));
                yWindow.append(ysList.at(j));
                zWindow.append(zsList.at(j));
                }
            }
        //const QList<int> *seqX = xWindow;
        const QList<int> templx = *templateGesture->at(0);
        //qDebug() << "length of template list: " << templx.length() << " length of slinding window " << xWindow.length();
        DTWResult resX = dtw->classify(templx, xWindow);
        if (xmin > resX.distance / scaleFactor){
            xmin = resX.distance / scaleFactor;
            xminPos = i;

        }
        xMap[i] = resX.distance / scaleFactor;

        //qDebug() << "got the results for X " << resX.distance / scaleFactor;
        const QList<int> temply = *templateGesture->at(1);
        DTWResult resY = dtw->classify(temply, yWindow);
        if (ymin > resY.distance / scaleFactor){
            ymin = resY.distance / scaleFactor;
            yminPos = i;
        }
        yMap[i] = resY.distance / scaleFactor;

        //qDebug() << "got the results for Y " << resY.distance / scaleFactor;
        const QList<int> templz = *templateGesture->at(2);
        DTWResult resZ = dtw->classify(templz, zWindow);
        if (zmin > resZ.distance / scaleFactor){
            zmin = resZ.distance / scaleFactor;
            zminPos = i;
        }
        zMap[i] = resZ.distance / scaleFactor;

        //qDebug() << "got the results for Z " << resZ.distance / scaleFactor;

    }

    const QList<int> templateX = *templateGesture->at(0);
    for (int i = 0; i < templateX.length(); i++){
       emit appendFittedX(double(xminPos+i), (double)templateX.at(i)/1000);
    }
    const QList<int> templateY = *templateGesture->at(1);
    for (int i = 0; i < templateY.length(); i++){
       emit appendFittedY(double(yminPos+i), (double)templateY.at(i)/1000);
    }
    const QList<int> templateZ = *templateGesture->at(2);
    for (int i = 0; i < templateZ.length(); i++){
       emit appendFittedZ(double(zminPos+i), (double)templateZ.at(i)/1000);
    }
    QString strXmin, strXPos;
    strXmin = strXmin.setNum(xmin);
    strXPos = strXPos.setNum(xminPos);
    QString sx = "Err:" + strXmin + " Win:" + strXPos;
    emit displayXResults(sx);
    strXmin = strXmin.setNum(ymin);
    strXPos = strXPos.setNum(yminPos);
    QString sy = "Err:" + strXmin + " Win:" + strXPos;
    emit displayYResults(sy);
    strXmin = strXmin.setNum(zmin);
    strXPos = strXPos.setNum(zminPos);
    QString sz = "Err:" + strXmin + " Win:" + strXPos;
    emit displayZResults(sz);

    float meanX = ((pow(xmin,2) + pow(yMap[xmin],2)+pow(zMap[xmin],2))/3);
    float meanY = ((pow(ymin,2) + pow(yMap[ymin],2)+pow(zMap[ymin],2))/3);
    float meanZ = ((pow(zmin,2) + pow(yMap[zmin],2)+pow(zMap[zmin],2))/3);

    QList<float> meanList;
    meanList.append(meanX);
    meanList.append(meanY);
    meanList.append(meanZ);
    qSort(meanList);
    QMap<float, QString> meanMap;
    meanMap[meanX] = QString::number(xminPos);
    meanMap[meanY] = QString::number(yminPos);
    meanMap[meanZ] = QString::number(zminPos);
    emit displayWinDow(meanMap[meanList.at(0)]);

    qDebug() << "The best x value thems to be: " << xmin << " in window starts at: " << xminPos;
    qDebug() << "while y value in window" << xminPos << " is " << yMap[xminPos] ;
    qDebug() << "and z in window "<< xminPos << " is " << zMap[xminPos];
    qDebug() << "and mean is "<< meanX;

    qDebug() << "The best y value thems to be: " << ymin << " in window starts at: " << yminPos;
    qDebug() << "while x value in window" << yminPos << " is " << xMap[yminPos] ;
    qDebug() << "and z in window "<< yminPos << " is " << zMap[yminPos];
    qDebug() << "and mean is " << meanY;

    qDebug() << "The best z value thems to be: " << zmin << " in window starts at: " << zminPos;
    qDebug() << "while x value in window" << zminPos << " is " << xMap[zminPos] ;
    qDebug() << "and y in window "<< zminPos << " is " << yMap[zminPos];
    qDebug() << "and mean is " << meanZ;


}

void DtwController::startObservation(){
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()),this, SLOT(spawnGestureWindow()));
    timer->start(200);
    QTimer::singleShot(5000, timer, SLOT(stop()));

}
void DtwController::setSequence(QList< QList<int>* >* list){
    //sequence = new QList< QList<int>* >*;
    sequence = list;
    QList<int> *subList = sequence->at(1);
    emit sendSrcVecSize(subList->length());

}

void DtwController::receiveData(QList <DTWResult> results){

}

void DtwController::setObservationDuration(int i){

}

void DtwController::spawnGestureWindow(){
    new GestureWindow(templateGesture, dataholder);

}

void DtwController::selectTracker(QString tracker){
    if (tracker == "FileTracker"){
        qDebug() << "Filetracker select";
        QObject::connect(fileTracker, SIGNAL(sendSequence(QList<QList<int>*>*)), this, SLOT(setSequence(QList<QList<int>*>*)));
        fileTracker->initialize();
    } else if (tracker == "IisuTracker"){
        qDebug() << "Isutracker select, but it will currently not work";


    } else {
        qDebug() << "what?";

    }

}
