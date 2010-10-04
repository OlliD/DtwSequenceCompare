// based on singleton
#include <string>
#include <iostream>
#include <QFile>
#include <QTextStream>

#include "logger.h"


Logger* Logger::instance = NULL;

Logger::Logger(QString path = "c:")
{
    logfile = new QFile(path);
    logtimer = new QDateTime();
    QString logtime = logtimer->currentDateTime().toString();
    std::cout<< "logger started at: " << logtime.toStdString() << std::endl;
    index = 0;
}

/*void Logger::log(std::string str, int lvl){
    Logger::logging(str, lvl);
}

void Logger::log(char cstr, int lvl){
    std::string str = cstr;
    Logger::logging(str, lvl);
}
*/

void Logger::log(QString str, int lvl){
    Logger::logging(str, lvl);
}

void Logger::logging(QString str, int lvl){

    QString logtime = Logger::logtimer->currentDateTime().toString("yyyy-MM-dd hh:mm");
    switch (lvl)
    {
    case 0:  // nothing to do in this case
        break;
    case 1:  // let's put it on the console
        std::cout << "@@@LOGGER@@@ at " << logtime.toStdString() << ": " << str.toStdString() << std::endl;
        break;
    case 2: // that should be written to a file
        if (Logger::logfile->open(QIODevice::WriteOnly | QIODevice::Text )) {
            QTextStream out(Logger::logfile);
            out << qSetFieldWidth(10) << logtime << " : " << str.toAscii();
        }
        else
            std::cout << "failed to open file" << std::endl;

        Logger::logfile->close();
        break;
    }
}

Logger& Logger::getInstance(QString path){
    if( !instance )
        instance = new Logger(path);
    return *instance;
}

void Logger::Destroy(){
    // static
    delete instance;
    instance = NULL;
}


