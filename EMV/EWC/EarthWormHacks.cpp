#include <QtCore>

#include <QString>
#include <QStringList>

extern "C" {
#include "EarthWormHacks.h"
}

#include "EarthWormComp.h"

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

extern "C" int X_tport_putmsg( SHM_INFO* /* region */,    /* info structure for memory region    */
          MSG_LOGO *putlogo,   /* type,module,instid of incoming msg  */
          long      length,    /* size of incoming message            */
          char     *msg )      /* pointer to incoming message         */
{
    qDebug() << "X_tport_putmsg : \n"
        << "MSG_LOGO: " << putlogo->instid << putlogo->mod << putlogo->type << "\n"
        << QString::fromLatin1(msg, length) << "\n\n";

    return PUT_OK;
}


// New Hypocenter message
extern "C" int X_import_filter( char *msg, int msgLen, MSG_LOGO* putlogo )
{
    qDebug() << "X_import_filter : \n"
        << "MSG_LOGO: " << putlogo->instid << putlogo->mod << putlogo->type << "\n"
        << QString::fromLatin1(msg, msgLen) << "\n\n";


    EWC::RaiseHypoMessageReceived();



    // Not needed right now

//    HypoArc hypoArc;
//    if (parse_arc(msg, &hypoArc))
//    {
//        qDebug() << "Error on parse_arc\n";
//    }
//    else
//    {
//        qDebug() << "Success \n";
//    }



//    Hsum sum {};
//    read_hyp(msg, 0, &sum);

//    char * msgEnd = msg + msgLen * sizeof(char);

//    char * msgPtr = msg;

//    //Advance ptr to first

//    while (msgPtr < msg)
//    {

//    }



    return PUT_OK;
}


