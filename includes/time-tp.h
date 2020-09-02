#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER tp_provider

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./time-tp.h"

#if !defined(_time_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _time_TP_H

//! Defines if tracing is enabled
//#define TRACENEWFILE
#define TRACEOLDFILE

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(
        tp_provider,
        time_tracepoint_dummy_old,
        TP_ARGS(
                int, probe_nr
        ),
        TP_FIELDS(
                ctf_integer(int, probeNumber, probe_nr)
        )
)

TRACEPOINT_EVENT(
        tp_provider,
        time_tracepoint_dummy_new,
        TP_ARGS(
                int, probe_nr
        ),
        TP_FIELDS(
                ctf_integer(int, probeNumber, probe_nr)
        )
)

#endif /* _time_TP_H */

#include <lttng/tracepoint-event.h>