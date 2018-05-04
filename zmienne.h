#ifndef ZMIENNE_H
#define ZMIENNE_H

#include <QtCore>
#include <QObject>


class Singleton {
// definicja klasy o nazwie Singleton - jest
// to nazwa wlasna :)
public:
       // QString mainPath;
       // QString databasePath;
private:
        Singleton();
        Singleton(const Singleton&);
        // konstruktor klasy

        friend Singleton& Zm();
};

Singleton& Zm();

#endif // ZMIENNE_H
