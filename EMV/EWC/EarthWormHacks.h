#ifndef EARTHWORMHACKS_H
#define EARTHWORMHACKS_H

#include <transport.h>
#include <read_arc.h>

#include "importgenericconfig.h"

int X_tport_putmsg( SHM_INFO* region,    /* info structure for memory region    */
          MSG_LOGO* putlogo,   /* type,module,instid of incoming msg  */
          long      length,    /* size of incoming message            */
          char     *msg );      /* pointer to incoming message         */

int X_import_filter( char *msg, int msgLen, MSG_LOGO* logo );



#endif // EARTHWORMHACKS_H

