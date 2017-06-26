#include <QApplication>

#include "emv.h"

#include "teststring.h"

//to delete
extern "C" {
#include "EarthWormHacks.h"
}

int main(int argc, char *argv[])
{
//    MSG_LOGO blank {};
//    X_import_filter(const_cast<char*>(TestString::testString), 4607, &blank);


    QApplication a(argc, argv);
    EMV w;

    w.showMaximized();

    return a.exec();
}
