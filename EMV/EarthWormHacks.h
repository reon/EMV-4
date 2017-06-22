#ifndef EARTHWORMHACKS_H
#define EARTHWORMHACKS_H

#include <transport.h>

int X_tport_putmsg( SHM_INFO* region,    /* info structure for memory region    */
          MSG_LOGO* putlogo,   /* type,module,instid of incoming msg  */
          long      length,    /* size of incoming message            */
          char     *msg );      /* pointer to incoming message         */

int X_import_filter( char *msg, int msgLen, MSG_LOGO* logo );


struct ImportGenericConfig {
//        "<MyModuleId> "
    const char * MyModuleId;
//        "<RingName> "
    const char * RingName;
//        "<HeartBeatInt> "
    int HeartBeatInt;
//        "<LogFile> "
    short LogFile;
//        "<MaxMsgSize> "
    int MaxMsgSize;
//        "<MyAliveInt> "
    int MyAliveInt;
//        "<MyAliveString>
    const char* MyAliveString;
//        "<SenderIpAdr> "
    const char* SenderIPAddress;
//        "<SenderPort> "
    short SenderPort;
//        "<SenderHeartRate
    short SenderHeartRate;
//        "<SenderHeartText
    const char* SenderHeartText;
    int SocketTimeout;
    int HeartBeatDebug;
};

#endif // EARTHWORMHACKS_H

