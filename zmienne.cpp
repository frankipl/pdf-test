#include "zmienne.h"

Singleton::Singleton() {
    // konstruktor klasy - nie używany :))
  //  mainPath=QString("%1/").arg(QDir::currentPath());
  //  databasePath=mainPath+"database"+QDir::separator();
  //  databasePath=QString("%1/%2/").arg(mainPath).arg("database");
}

Singleton& Zm() {
// funkcja glowna singletonu
        static Singleton zmienne;
        return zmienne;
}
