#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QObject>
#include <QDateTime>
#include <QFile>

class Logger{

    private:
      //Ein Pointer zum Speichern der Instanz
      static Logger* instance;
      //Konstruktor private, damit man sich keine Instanzen holen kann.
      Logger(QString path);
      //Den Kopierkonstruktor schützen um zu vermeiden, dass das Objekt unbeabsichtigt kopiert wird.
      Logger(const Logger& cc);
      //~Logger();
      void logging(QString, int);
      int index;
      QDateTime *logtimer;
      QFile *logfile;
    public:
      static Logger& getInstance(QString path = "../../../log.txt");
      void log(QString, int);
      //void log(std::string, int);
      //void log(char , int);
      static void Destroy();

};

#endif // LOGGER_H

