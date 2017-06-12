#include <QApplication>

#include "emv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EMV w;

    w.showMaximized();

    return a.exec();
}
