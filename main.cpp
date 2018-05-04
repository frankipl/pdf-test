#include <QCoreApplication>
#include "backend.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Backend backend;

    return a.exec();
}
