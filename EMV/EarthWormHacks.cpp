#include <QtCore>

#include <QString>
#include <QStringList>

#include "EarthWormHacks.h"

//extern "C" void logit_init(char *prog, short mid, int bufSize, int logflag ) /* logit.c      sys-independent  */
//{
//    QString strProg;

//    if (prog == nullptr)
//        strProg = "NULL";
//    else
//        strProg = QString(prog);

//    QStringList args {QString(mid), QString(bufSize), QString(logflag)};

//    qDebug() << "X_logit_init() \n " << args.join(' ') << '\n' << "end X_logit_init()";
//}

int X_tport_putmsg( SHM_INFO *region,    /* info structure for memory region    */
          MSG_LOGO *putlogo,   /* type,module,instid of incoming msg  */
          long      length,    /* size of incoming message            */
          char     *msg )      /* pointer to incoming message         */
{
    qDebug() << "X_tport_putmsg : \n"
        << "MSG_LOGO: " << putlogo->instid << putlogo->mod << putlogo->type << "\n"
        << QString::fromLatin1(msg, length) << "\n\n";

    return PUT_OK;
}
