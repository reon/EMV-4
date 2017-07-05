#ifndef IMPORTGENERICCONFIG
#define IMPORTGENERICCONFIG

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


#endif // IMPORTGENERICCONFIG

