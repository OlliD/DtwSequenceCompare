#ifndef IISUTRACKER_H
#define IISUTRACKER_H

#include <QObject>
#include <assert.h>
#include <math.h>
//just for compiling on windows-based platforms
//#include <windows.h>
#include <QList>
#include <QThread>

//#include "../../../../../../../Programme/Softkinetic/iisu/include/iisuSDK.h"

//#include "../../../../../../../Programme/Softkinetic/iisu/include/iisu_loader.c"
//#include "iisu_loader.c"


#include "logger.h"

class IisuTracker : public QThread
{
    Q_OBJECT

public:
    IisuTracker();
    //void requestStop();
    bool shouldStop;

signals:
    void sendLeftHandPos(QList<int> pos);
    void sendRightHandPos(QList<int> pos);
    void sendLeftHandState(int i);
    void sendRightHandState(int i);


private:
    //void onEvent(const ISkEvent&);
    //QList<int> skVec2qVec(IisuData<iisu::Vector3>);
    //ISkDevice* pkDevice;
    QList<int> *lastLeftPos;
    QList<int> *lastRightPos;
    bool isRunning;
/*
    IisuData<iisu::Vector3> userlocation;
    IisuData<iisu::Vector3> rightHandVec;
    IisuData<iisu::Vector3> leftHandVec;
    IisuData<iisu::Vector3> hand1;
    IisuData<iisu::Vector3> hand2;
*/

protected:
    void run();

};

#endif // IISUTRACKER_H
