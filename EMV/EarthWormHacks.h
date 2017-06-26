#ifndef EARTHWORMHACKS_H
#define EARTHWORMHACKS_H

#include <transport.h>
#include <read_arc.h>

int X_tport_putmsg( SHM_INFO* region,    /* info structure for memory region    */
          MSG_LOGO* putlogo,   /* type,module,instid of incoming msg  */
          long      length,    /* size of incoming message            */
          char     *msg );      /* pointer to incoming message         */

int X_import_filter( char *msg, int msgLen, MSG_LOGO* logo );


struct ImportGenericConfig {        //Unorder
    const char * MyModuleId;
    const char * RingName;
    int HeartBeatInt;
    short LogFile;
    int MaxMsgSize;
    int MyAliveInt;
    const char* MyAliveString;
    const char* SenderIPAddress;
    short SenderPort;
    short SenderHeartRate;
    const char* SenderHeartText;
    int SocketTimeout;
    int HeartBeatDebug;
};

#endif // EARTHWORMHACKS_H

