#include "filetracker.h"

FileTracker::FileTracker(QWidget *parent) :
    QWidget(parent)
{
    xList = new QList<int>;
    yList = new QList<int>;
    zList = new QList<int>;

    qDebug() << "creating Filetracker";


}

void FileTracker::initialize(){

    QString filename = QFileDialog::getOpenFileName(this,tr("Open Text"), "/homes/", tr("Text Files (*.csv)"));
    QFile file(filename);
    qDebug() << "loading file" ;
    if (!file.open(QIODevice::ReadOnly | QIODevice::ReadOnly))
        return;
    timeline = 0;

    while (!file.atEnd()) {
        //qDebug()<< "processing line \n";
        QByteArray line = file.readLine();
        FileTracker::processLine(line);
        timeline++;

    }

    //scaleFactor = 1000000;
    coordinatesList = new QList< QList<int>* >;
    coordinatesList->append(xList);
    coordinatesList->append(yList);
    coordinatesList->append(zList);
    //qDebug() << "length of coordinatesList: " << coordinatesList->length();
    emit sendSequence(coordinatesList);

}

// Die drei Koordinaten werden in die Felder geschrieben und, mit dem ScaleFactor skaliert,
// in die entsprechende Liste geschrieben
void FileTracker::processLine(QByteArray line){
    scaleFactor = 1000;
    QString s(line);
    s.replace("\n","");
    s.replace(",","");
    QStringList sList = s.split(";");
    s ="";
    //qDebug() << "String " << sList;

    QString x = sList.at(0);
    //ui->leftHandOutPut->appendPlainText(x);
    float floatx = x.toFloat() * scaleFactor;
    FileTracker::xList->append(floatx);
    emit sendXValue((double)timeline, x.toDouble());
    //qDebug() << "fileTracker: Adding x: " << floatx << " with length of x: " << xList->length();

    QString y = sList.at(1);
    //ui->leftHandOutPut->appendPlainText(y);
    float floaty = y.toFloat() * scaleFactor;
    FileTracker::yList->append(floaty);
    emit sendYValue((double)timeline, y.toDouble());
    //qDebug() << "fileTracker: Adding y: " << floaty << " with length of y: " << yList->length();

    QString z = sList.at(2);
    //ui->leftHandOutPut->appendPlainText(z);
    float floatz = z.toFloat() * scaleFactor;
    FileTracker::zList->append(floatz);
    emit sendZValue((double)timeline, z.toDouble());
    //qDebug() << "fileTracker: Adding z: " << floatz << " with length of z: " << zList->length();

}
