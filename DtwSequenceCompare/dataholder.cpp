#include "dataholder.h"

DataHolder::DataHolder(QObject *parent) :
    QObject(parent)
{
    data = new QList< QList <DTWResult> >;
}

void DataHolder::addResult(QList<DTWResult> result ){
    data->append(result);
}

void DataHolder::getResult(QList<DTWResult> result){
    if (data->length()>0){
        result = data->at(0);
    }
    data->removeAt(0);
}
