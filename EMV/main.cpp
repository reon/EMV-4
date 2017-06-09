#include "emv.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EMV w;
    w.show();

    return a.exec();
}
