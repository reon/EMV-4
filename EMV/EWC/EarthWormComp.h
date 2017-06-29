#ifndef EARTHWORMCOMP_H
#define EARTHWORMCOMP_H

//#include <QMutex>

#include "emv.h"

#include "hypomessage.h"

class EMV;


namespace EWC {
    int StartImportGeneric();
    void * ImportGeneric(void* );

    void RaiseHypoMessageReceived();

    extern HypoMessage* hypoMessage;
    extern EMV* emv;

}





#endif // EARTHWORMCOMP_H
