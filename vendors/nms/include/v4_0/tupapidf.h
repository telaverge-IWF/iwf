#ifndef TUPAPIDF_H_
#define TUPAPIDF_H_


#define EVTLSIERRIND     0xff        /* Error indication */

#define AENA             1           /* enable */
#define ADISIMM          2           /* disable - immediately */
#define ARST             4           /* reset */
#define ADEL             7           /* delete */
#define AVAL             13          /* validate circuit */

#define SAELMNT          1           /* specified element */
#define SAACNT           2           /* accounting generation */
#define SAUSTA           3           /* unsolicited status generation */
#define SATRC            4           /* trace generation */


#define TRCMSGTX         11          /* trace - message transmitted */
#define TRCMSGRX         12          /* trace- message received */

#endif
