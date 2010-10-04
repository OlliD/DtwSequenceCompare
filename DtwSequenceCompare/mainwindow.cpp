#include <QGraphicsRectItem>
#include <QtAlgorithms>
#include <math.h>

#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug("Starting app");
    ui->setupUi(this);
    DTWResult dtwResult;
    dtwController = new DtwController();
    ui->leftHandLabel->setAutoFillBackground(true);
    ui->rightHandLabel->setAutoFillBackground(true);
    palette = new QPalette();
    palette->setColor(QPalette::Background,QColor(0,255,0));
    ui->pushButton_2->setPalette(*palette);
    ui->leftHandLabel->setPalette(*palette);
    ui->rightHandLabel->setPalette(*palette);

    ui->similarityBar->setRange(0, 100);

    ui->timeSlider->setMinimum(0);
    ui->timeSlider->setMaximum(5000);
    ui->timeSlider->setSingleStep(500);
    ui->timeSlider->setTickInterval(500);

    plotX = new PlotWidget();
    plotY = new PlotWidget();
    plotZ = new PlotWidget();

    xList = new QList<int>;
    yList = new QList<int>;
    zList = new QList<int>;
    scaleFactor = 1000;
    connectSlots();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

// Funktion zum setzen alle Signal-Slot-Verbindungen
void MainWindow::connectSlots(){
    QObject::connect(ui->startMeasureButton,SIGNAL(clicked()), this, SLOT(startTracking()));
    QObject::connect(ui->loadButton,SIGNAL(clicked()), this, SLOT(openTemplate()));
    QObject::connect(ui->trackerBox, SIGNAL(activated(QString)), dtwController, SLOT(selectTracker(QString)));
    QObject::connect(this, SIGNAL(sendTemplate(QList<QList<int>*>*)), dtwController, SLOT(setTemplateSequence(QList<QList<int>*>*)));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(getScaleFactor()) );
    QObject::connect(ui->timeSlider, SIGNAL(sliderMoved(int)),this, SLOT(setSliderLabel(int)));
    QObject::connect(ui->calc_concat, SIGNAL(clicked()), dtwController, SLOT(calculateConcatenated()));
    QObject::connect(ui->calc_single, SIGNAL(clicked()), dtwController, SLOT(calculateDistance()));
    QObject::connect(ui->calc_seq, SIGNAL(clicked()), dtwController, SLOT(calculateSequence()));
    QObject::connect(dtwController, SIGNAL(sendResult(QString)), this, SLOT(showResult(QString)));
    QObject::connect(dtwController, SIGNAL(sendSrcVecSize(int)), this, SLOT(setSrcListSize(int)));
    QObject::connect(dtwController, SIGNAL(sendMatrix(QVector<QVector<int> >, QString)),this, SLOT(paintMatrix(QVector<QVector<int> >, QString)));
    QObject::connect(this, SIGNAL(setScaleFactor(int)), dtwController, SLOT(setScaleFactor(int)));
    QObject::connect(ui->xButton, SIGNAL(clicked()), this, SLOT(showPlotX()));
    QObject::connect(dtwController->fileTracker, SIGNAL(sendXValue(double,double)), this, SLOT(appendXTemplateValue(double,double)));
    QObject::connect(ui->yButton, SIGNAL(clicked()), this, SLOT(showPlotY()));
    QObject::connect(dtwController->fileTracker, SIGNAL(sendYValue(double,double)), this, SLOT(appendYTemplateValue(double,double)));
    QObject::connect(ui->zButton, SIGNAL(clicked()), this, SLOT(showPlotZ()));
    QObject::connect(dtwController->fileTracker, SIGNAL(sendZValue(double,double)), this, SLOT(appendZTemplateValue(double,double)));
    QObject::connect(dtwController, SIGNAL(appendFittedX(double,double)), this, SLOT(appendXValue(double,double)));
    QObject::connect(dtwController, SIGNAL(appendFittedY(double,double)), this, SLOT(appendYValue(double,double)));
    QObject::connect(dtwController, SIGNAL(appendFittedZ(double,double)), this, SLOT(appendZValue(double,double)));
    QObject::connect(dtwController, SIGNAL(dropPlotData()), plotX, SLOT(dropData()));
    QObject::connect(dtwController, SIGNAL(dropPlotData()), plotY, SLOT(dropData()));
    QObject::connect(dtwController, SIGNAL(dropPlotData()), plotZ, SLOT(dropData()));
    QObject::connect(dtwController, SIGNAL(displayXResults(QString)), this, SLOT(setXResults(QString)));
    QObject::connect(dtwController, SIGNAL(displayYResults(QString)), this, SLOT(setYResults(QString)));
    QObject::connect(dtwController, SIGNAL(displayZResults(QString)), this, SLOT(setZResults(QString)));
    QObject::connect(dtwController, SIGNAL(displayWinDow(QString)), this, SLOT(setWinDow(QString)));
    //    QObject::connect(ui->timeSlider, SIGNAL(sliderMoved(int)), dtwController, SLOT(setObservationDuration(int)));
    //    QObject::connect(tracker, SIGNAL(sendLeftHandState(int)), this, SLOT(setLeftHandState(int)));
    //    QObject::connect(tracker, SIGNAL(sendRightHandState(int)), this, SLOT(setRightHandState(int)));
    //    QObject::connect(dtwController, SIGNAL(sendSequenceSimilarity(float)),this, SLOT(setSimilarityValue(float)));

    emit setScaleFactor(scaleFactor);
}

void MainWindow::startTracking(){
//    MainWindow::tracker->run();
}

// Setter fuer das Restzeit LCD
void MainWindow::setRemainingTime(int i){
    ui->lcdNumber->display(i);
}

// Die beiden LCD-Gui Elemente werden gesetzt
void MainWindow::setSliderLabel(int i){
    ui->timeLabel->display(i);
    ui->lcdNumber->display(i);

}

void MainWindow::setSrcListSize(int s){
    ui->src_number->display(s);
}

void MainWindow::setXResults(QString s){
ui->xResults->setText(s);
}

void MainWindow::setYResults(QString s){
ui->yResults->setText(s);
}

void MainWindow::setZResults(QString s){
ui->zResults->setText(s);
}

void MainWindow::setWinDow(QString s){
ui->errLabel->setText(s);
}


void MainWindow::showPlotX(){
    plotX->diplayData();
    plotX->setTitle("X-Achse");
    plotX->show();
    plotX->replot();
}

void MainWindow::showPlotY(){
    plotY->diplayData();
    plotY->setTitle("Y-Achse");
    plotY->show();
    plotY->replot();
}

void MainWindow::showPlotZ(){
    plotZ->diplayData();
    plotZ->setTitle("Z-Achse");
    plotZ->show();
    plotZ->replot();
}

void MainWindow::appendXTemplateValue(double x, double y){
    plotX->addDataTempl(x, y);
}

void MainWindow::appendYTemplateValue(double x, double y){
    plotY->addDataTempl(x, y);
}
void MainWindow::appendZTemplateValue(double x, double y){
    plotZ->addDataTempl(x, y);
}


void MainWindow::appendXValue(double x, double y){
    plotX->addDataObs(x, y);
}

void MainWindow::appendYValue(double x, double y){
    plotY->addDataObs(x, y);
}
void MainWindow::appendZValue(double x, double y){
    plotZ->addDataObs(x, y);
}

// Der Scale Faktor wird eingelesen und ueber ein Signal verteilt
void MainWindow::getScaleFactor(){
    bool ok;
    MainWindow::scaleFactor = QInputDialog::getInt(this, tr("Set scale factor"),
                                 tr("Value:"), 1, 0, 100000, 1, &ok);
    if (ok){
        emit setScaleFactor(scaleFactor);
    }

}

// Setter fuer das GUI-Label similarity
void MainWindow::setSimilarityValue(float f){
    int i = (int)f;
    ui->similarityBar->setValue(i);
}


// Die Datei mit dem GestenTemplate wird geladen und Zeilen verabeitet
// Jede Zeile wird in das entsprechende Feld geschrieben und ebenfalls
// in eine QList die zum Schluss ueber ein Signal bereitgestellt wird.
void MainWindow::openTemplate(){
    QString filename = QFileDialog::getOpenFileName(this,tr("load gesture"), "/Users/odamm/Dropbox/DtwSequenceCompare", tr("Text Files (*.csv)"));
    //templateFile = ;
    QFile file(filename);
    qDebug() << "loading file" ;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    timeline = 0;
    while (!file.atEnd()) {

        QByteArray line = file.readLine();
        MainWindow::processLine(line);
        timeline++;
    }

    coordinatesList = new QList< QList<int>* >;
    coordinatesList->append(xList);
    //xList = computeZScores(*xList);
    coordinatesList->append(yList);
    coordinatesList->append(zList);
    emit sendTemplate(coordinatesList);

}


// Die drei Koordinaten werden in die Felder geschrieben und, mit dem ScaleFactor skaliert,
// in die entsprechende Liste geschrieben
void MainWindow::processLine(QByteArray line){
    QString s(line);
    s.replace("\n","");
    s.replace(",","");
    QStringList sList = s.split(";");
    s ="";
    //qDebug() << "String " << sList;
    QString x = sList.at(0);
    //ui->leftHandOutPut->appendPlainText(x);

    float floatx = x.toFloat() * scaleFactor;
    MainWindow::xList->append(floatx);
    plotX->addDataObs((double)timeline, x.toDouble());
    //qDebug() << "fileTracker: Adding x: " << floatx << " with length of x: " << xList->length();

    QString y = sList.at(1);
    int inty = y.toInt() * scaleFactor;
    //ui->leftHandOutPut->appendPlainText(y);
    float floaty = y.toFloat() * scaleFactor;
    MainWindow::yList->append(floaty);
    plotY->addDataObs((double)timeline, y.toDouble());

    //qDebug() << "fileTracker: Adding y: " << floaty << " with length of y: " << yList->length();

    QString z = sList.at(2);
    int intz = z.toInt() * scaleFactor;
    //ui->leftHandOutPut->appendPlainText(z);
    float floatz = z.toFloat() * scaleFactor;
    MainWindow::zList->append(floatz);
    plotZ->addDataObs((double)timeline, z.toDouble());

    //qDebug() << "fileTracker: Adding z: " << floatz << " with length of z: " << zList->length();
    int length = xList->length();
    QString str = (QString)length;
    ui->obs_number->display(xList->length());
}



void MainWindow::setStatusBar(int i){
   ui->similarityBar->setValue(i);
}

// Zwei Funktionen zum aktualiseren der Handdetektion-Labels.
// 0: rot - Hand nicht gefunden
// 1: gruen - Hand gefunden
// 2: gruen - Hand gefunden


void MainWindow::getResult(float res){
    int i = (int)res;
    QString s(i);
    ui->leftHandOutPut->appendPlainText(s);
}



void MainWindow::setLeftHandState(int i){
    switch (i)
    {
    case 0:
        MainWindow::palette->setColor(QPalette::Background,QColor(255,0,0));
        ui->leftHandLabel->setText("left hand NOT found");
        break;

    case 1:
       MainWindow::palette->setColor(QPalette::Background,QColor(0,255,0));
       ui->leftHandLabel->setText("left hand found");
       break;
    case 2:
       MainWindow::palette->setColor(QPalette::Background,QColor(0,255,0));
       ui->leftHandLabel->setText("left hand found");
       break;
    default:
       MainWindow::palette->setColor(QPalette::Background,QColor(255,0,0));
       ui->leftHandLabel->setText("left hand NOT found");
       break;
   }

    ui->leftHandLabel->setPalette(*palette);

}



void MainWindow::setRightHandState(int i){
    switch (i)
    {
    case 0:
       MainWindow::palette->setColor(QPalette::Background,QColor(255,0,0));
       ui->rightHandLabel->setText("right hand NOT found");
       break;
    case 1:
       MainWindow::palette->setColor(QPalette::Background,QColor(0,255,0));
       ui->rightHandLabel->setText("right hand found");
       break;
    case 2:
       MainWindow::palette->setColor(QPalette::Background,QColor(0,255,0));
       ui->rightHandLabel->setText("right hand found");
       break;
    default:
       MainWindow::palette->setColor(QPalette::Background,QColor(255,0,0));
       ui->rightHandLabel->setText("right hand NOT found");
       break;
   }

    ui->leftHandLabel->setPalette(*palette);

}

void MainWindow::showResult(QString res){
    ui->leftHandOutPut->appendPlainText(res);
}

void MainWindow::paintMatrix(QVector<QVector<int> > matrix, QString axis){
    QGraphicsScene *scene;
    scene = new QGraphicsScene;
    int size = 4;
    int x = 0;
    int y = 0;
    QList<int> list;
    for (int i = 0; i < matrix.size(); i++ ){
        QVector<int> vector = matrix[i];
        for (int j = 0; j < vector.size(); j++){
            list.append(vector[j]);
        }
    }
    qSort(list.begin(), list.end());
    double colorNorm = 255 / (float)list.last();

    for (int i = 0; i < matrix.size(); i++ ){
        QVector<int> vector = matrix[i];
        for (int j = 0; j < vector.size(); j++){
            QColor color;
            int val = vector[j];
            float r = vector[j] * colorNorm;
            float g = vector[j] * colorNorm;
            color.setRgb(r,50,g);
             QGraphicsRectItem *rect ;
            rect = new QGraphicsRectItem;
            QBrush brush(color);
            QPen pen(Qt::SolidLine);
            pen.setBrush(brush);
            rect = scene->addRect(QRectF(x,y,size,size), pen, brush);
            //qDebug() << "Matrix at:  [" << i << ":" << j <<"] " << vector.at(j) << "colorvalue is: " <<  colorNorm;
            y = y + size;

        }
        y = 0;
        x = x + size;
    }
    if (axis == "x"){
        ui->xView->setScene(scene);

    }else if(axis == "y"){
        ui->yView->setScene(scene);

    }else if(axis == "z"){
        ui->zView->setScene(scene);

    }
}

QList<int>*  MainWindow::computeZScores(QList<int> bla){
    QList<int> *retVec = new QList<int>;
    float mean;
    foreach(double v, bla) {
       mean += v;
    }
    mean /= bla.size();

    float dev;

    foreach(float v, bla) {
        dev += pow((v-mean),2);
    }
    dev /= bla.size();

    foreach(float v, bla){
        float zscore = ((v-mean)/dev);
        qDebug() << "got the value: " << v << " zscore is: " << zscore;
        retVec->append((int)zscore);
    }
    return retVec;
}
