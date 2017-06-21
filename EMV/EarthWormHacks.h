#ifndef EARTHWORMHACKS_H
#define EARTHWORMHACKS_H

#include <transport.h>

extern "C" int X_tport_putmsg( SHM_INFO* region,    /* info structure for memory region    */
          MSG_LOGO* putlogo,   /* type,module,instid of incoming msg  */
          long      length,    /* size of incoming message            */
          char     *msg );      /* pointer to incoming message         */

#endif // EARTHWORMHACKS_H

