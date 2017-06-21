#include <stdlib.h>

#include <QtCore>
#include "EarthWormComp.h"

extern "C" int Initialize_Import_Generic( int argc, char **argv );

extern "C" int StartThread( void* fun(void *), unsigned stack_size, unsigned *thread_id );



int EWC::StartImportGeneric()
{
    unsigned int ID {};
    StartThread(ImportGeneric, 16000, &ID);
}

void* EWC::ImportGeneric(void *)
{
    //setenv("EW_LOG", "/home/alex/Documents/EMV/EMV/EarthWorm/logs", 0);

    int argc;
    const char* argv[2];

    const char* empty = "";
    const char* configFile = "/home/alex/Documents/EMV/EMV/EarthWorm/src/data_exchange/import_generic/import_generic.d";

    argv[0] = empty;
    argv[1] = configFile;
    argc = 2;

    Initialize_Import_Generic( argc, const_cast<char**>(argv) );

    return nullptr;
}

