#include "iisutracker.h"

IisuTracker::IisuTracker() : QThread()
{

/*    IisuTracker::shouldStop = false;

    Logger::getInstance().log("Tracker startet", 0);

    isRunning = false;
    lastLeftPos = new QList<int>;
    lastRightPos = new QList<int>;

    //initialize the hardware
   // ISkDevice pkDevice;

    SkResult result;
    result = load_iisu();
    if(result != SK_RESULT_OK){
        qDebug() << "IISU-ERROR: " << SkGetErrorCode(result) << " " << SkGetErrorDescription(result);
    }
    result = iisu_createLocalDevice( &pkDevice );

    if(result != SK_RESULT_OK){
        qDebug() << "IISU-ERROR: " << SkGetErrorCode(result) << " " << SkGetErrorDescription(result);
    }

    // Initializing the device
    pkDevice->setPluginsLoading(false);

    result = pkDevice->initialize();

    if(result != SK_RESULT_OK){
        qDebug() << "IISU-ERROR: " << SkGetErrorCode(result) << " " << SkGetErrorDescription(result);
    }


    // Register all the needed data-streams

    userlocation = pkDevice->registerDataHandle("USER#.Position");
    rightHandVec = pkDevice->registerDataHandle("PARTS.RightHand");
    leftHandVec = pkDevice->registerDataHandle("PARTS.RightHand");

    //IisuTracker::pkDevice->sendCmd("loadBackground");
    //IisuTracker::pkDevice->sendCmd("loadCalibration");

    pkDevice->registerEventListener(this);
    pkDevice->start();
*/

}
/*
void IisuTracker::onEvent(const ISkEvent &pkEvent){
    Logger::getInstance().log("Event registered: ", 0);
    //TODO:handle event here, maybe with an simple debug output?
}

void IisuTracker::requestStop(){
    iisu_destroyDevice(IisuTracker::pkDevice);
    this->terminate();
}
*/


void IisuTracker::run(){
/*
    if(pkDevice->hasFatalErrors()){
        //SkResult result = IisuTracker::pkDevice->getFatalError();
        Logger::getInstance().log("Fatal Error detected: ", 0);
        this->terminate();
    }
    if (!IisuTracker::isRunning){
        pkDevice->beginRead();
        isRunning = true;
    }
    // create new Softkinetic-Vectors to put the received coords into
    int leftHandState, rightHandState;

    /* iisu Ver 1.5 Style
    IisuTracker::pkDevice->getData("USER.Position",userlocation);
    IisuTracker::pkDevice->getData("PARTS.RightHand", hand1);
    IisuTracker::pkDevice->getData("PARTS.LeftHand", hand2);
    IisuTracker::pkDevice->getData("PARTS.RightHandStatus", rightHandState);
    IisuTracker::pkDevice->getData("PARTS.LeftHandStatus", leftHandState);



    // tell the gui whether the hands was found or not
    emit sendLeftHandState(leftHandState);
    emit sendRightHandState(rightHandState);

    // check whether the left hand is the left hand for real (;
    if (hand1.x > userlocation.x){
        rightHandVec = hand1;
        leftHandVec = hand2;
    }
    else {
        rightHandVec = hand2;
        leftHandVec = hand1;
    }

    // get the current lefthand position

    IisuTracker::leftHandVec.updateValue();
    // convert the SKVectors to QList

    QList<int> leftHandqVec;// = new  QVector<int>;

    leftHandqVec = IisuTracker::skVec2qVec(leftHandVec);
    emit sendLeftHandPos(leftHandqVec);

    // get the current lefthand position

    IisuTracker::rightHandVec.updateValue();
    // convert the SKVectors to QList

    QList<int> rightHandqVec;
    rightHandqVec = IisuTracker::skVec2qVec(rightHandVec);
    emit sendRightHandPos(rightHandqVec);
*/
    this->sleep(50);
}

/*
QList<int> IisuTracker::skVec2qVec(IisuData<iisu::Vector3> vec){
    QList<int> retVec;
    //if (vec!=NULL){
    iisu::Vector3 vec3;

        retVec.append(vec.x);
        retVec.append(vec.y);
        retVec.append(vec.z);
    //}
    return retVec;
}
*/
