#include <QApplication>

#include "emv.h"

#ifndef NO_EARTHWORM
extern "C" {
#include "EWC/EarthWormHacks.h"
}
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("ISTI");
    QCoreApplication::setOrganizationDomain("ISTI.com");
    QCoreApplication::setApplicationName("EMV");

    EMV w;

    w.showMaximized();

    return a.exec();
}
