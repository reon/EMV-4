#include <stdlib.h>

#include <QtCore>
#include "EarthWormComp.h"
#include "EarthWormHacks.h"

extern "C" int Initialize_Import_Generic( int argc, char **argv, ImportGenericConfig config );

extern "C" int StartThread( void* fun(void *), unsigned stack_size, unsigned *thread_id );



int EWC::StartImportGeneric()
{
    unsigned int ID {};
    StartThread(ImportGeneric, 16000, &ID);
}

void* EWC::ImportGeneric(void *)
{
    //setenv("EW_LOG", "/home/alex/Documents/EMV/EMV/EarthWorm/logs", 0);

    ImportGenericConfig config {};
    config.MyModuleId = "MOD_IMPORT_GENERIC";
    config.RingName = "HYPO_RING";
    config.HeartBeatInt = 120;

    config.LogFile = 1;
    config.MaxMsgSize = 65000;
    config.MyAliveString = "alive";
    config.MyAliveInt = 30;

//    config.SenderIPAddress = "108.61.62.101";
    config.SenderIPAddress = "192.168.4.15";

    config.SenderPort = 16095;
    config.SenderHeartRate = 60;
    config.SenderHeartText = "alive";

    config.SocketTimeout = 60000;

    config.HeartBeatDebug = 1;

    int argc;
    const char* argv[2];

    const char* empty = "";
    const char* configFile = "/home/alex/Documents/EMV/EMV/EarthWorm/src/data_exchange/import_generic/import_generic.d";

    argv[0] = empty;
    argv[1] = configFile;
    argc = 2;

    Initialize_Import_Generic( argc, const_cast<char**>(argv), config);

    return nullptr;
}

