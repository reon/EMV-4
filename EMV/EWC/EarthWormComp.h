#ifndef EARTHWORMCOMP_H
#define EARTHWORMCOMP_H

//#include <QMutex>

#include "emv.h"

#include "importgenericconfig.h"

/// TODO delete hypomessage
#include "hypomessage.h"

class EMV;


namespace EWC {
    int StartImportGeneric();

    void * ImportGeneric(void* );
    ImportGenericConfig DefaultConfig();


    void RaiseHypoMessageReceived();

    extern HypoMessage* hypoMessage;
    extern EMV* emv;

}





#endif // EARTHWORMCOMP_H
