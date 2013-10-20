#include <QCoreApplication>
#include "netter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Netter *netter;
    netter = new Netter(&a);

    return a.exec();
}
