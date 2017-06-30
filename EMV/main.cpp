#include <QApplication>

#include "emv.h"

#include "EWC/teststring.h"

extern "C" {
#include "EWC/EarthWormHacks.h"
}

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
