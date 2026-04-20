#ifndef _NK_LOG_H
#define _NK_LOG_H 1

// This entire logging system is dependent on this macro being defined. If it's
// not, then nothing will be logged. No logging code will even be generated.
#ifdef NK_LOG_LEVEL
#include <stdio.h>
enum __nk_log_level { nkTRACE, nkDEBUG, nkINFO, nkWARNING, nkERROR, nkOFF };

#ifndef NK_LOG_OUTPUT
#define NK_LOG_OUTPUT stderr
#endif

#define __nk_log(LEVEL, COLOR, LABEL, FMT, ...)                                \
    if (NK_LOG_LEVEL <= LEVEL) {                                               \
        fprintf(NK_LOG_OUTPUT,                                                 \
                "\x1b[37m[\x1b[" #COLOR "m" LABEL "\x1b[37m]\x1b[m %s:%d " FMT \
                "\n",                                                          \
                __FILE__, __LINE__, ##__VA_ARGS__);                            \
    }
#define nklog_trace(FMT, ...) __nk_log(nkTRACE, 36, "trace", FMT, ##__VA_ARGS__)
#define nklog_debug(FMT, ...) __nk_log(nkDEBUG, 34, "debug", FMT, ##__VA_ARGS__)
#define nklog_info(FMT, ...) __nk_log(nkINFO, 32, "info", FMT, ##__VA_ARGS__)
#define nklog_warn(FMT, ...) __nk_log(nkWARNING, 33, "warn", FMT, ##__VA_ARGS__)
#define nklog_error(FMT, ...) __nk_log(nkERROR, 31, "error", FMT, ##__VA_ARGS__)
#else

// If the NK_LOG_LEVEL is not defined, then those calls to `nklog_*` generated
// no code. Hence, it costs nothing to leave these calls in your codebase.
#define nklog_trace(...)
#define nklog_debug(...)
#define nklog_info(...)
#define nklog_warn(...)
#define nklog_error(...)

#endif // ifdef NK_LOG_LEVEL

#endif // #ifndef _NK_LOG_H
