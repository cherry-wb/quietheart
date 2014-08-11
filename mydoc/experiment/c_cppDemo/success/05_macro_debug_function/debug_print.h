#ifndef __DEBUG_PRINT_H
#define __DEBUG_PRINT_H
#include <iostream>
using std::cerr;
using std::endl;

//======XXX For Debug.======
//XXX More informations about log print to be added.
//! @brief If you want to use debug functions below, set this to "1".
#define DECK_DEBUG 1

//XXX play feed back
//#define MIND_PLAY_FEEDBACK

//XXX Temp fixed problem, for bug of read from pipe with stdc fread fgetc...
#define DECSIM_MAGIC 190

#if DECK_DEBUG == 1

//XXX Improve the log level control in the future, used for selecting which log information to print.
//! @brief Log levels, if print log regard of levels, the log whose level equals "DECK_LOG_LEVEL" will be print.
#define DECK_LOG_LEVEL 3
//#define DECK_SYS_LOG_LEVEL 0

//! @brief The prefix of your log information.
//! @detail This string is added before your log information.
#define DECK_LOG_PREFIX "@@"

//======Debug functions print without regard of log levels.======
//! @brief Print information use C printf like format regardless of log levels.
#define pr_debug(...) fprintf(stderr,__VA_ARGS__)

//! @brief Only print current "File", "Function", "line" of this log, regardless of log levels.
#define pr_debug_loc() do{cerr<<DECK_LOG_PREFIX<<__FILE__<<":"<<__PRETTY_FUNCTION__<<":"<<__LINE__<<endl;}while(0)

//! @brief Only print one argument with any basic type regardless of log levels.
#define pr_debug_var(var) \
		do{cerr<<DECK_LOG_PREFIX<<__FILE__<<":"\
			<<__PRETTY_FUNCTION__<<":"<<__LINE__<<"variable \""<<#var<<"\" is:"\
			<<var<<":"<<endl;}while(0)

//! @brief Important log for send and receive messages.
//XXX To be improved.This log level is high.
//#define pr_sysdebug(...) pr_level_debug((DECK_SYS_LOG),__VA_ARGS__)
#define pr_sysdebug pr_debug

//======Debug functions only print when the "lv" parameter equals to "DECK_LOG_LEVEL".======
//! @brief Print information use C printf like format, if lv equals DECK_LOG_LEVEL.
#define pr_level_debug(lv, ...) do{if((lv) == (DECK_LOG_LEVEL)){pr_debug(__VA_ARGS__);}}while(0)

//! @brief Only print current "File", "Function", "line" of this log, if lv equals DECK_LOG_LEVEL.
#define pr_level_debug_loc(lv) do{if((lv) == (DECK_LOG_LEVEL)){pr_debug_loc();}}while(0)

//! @brief Only print one argument with any basic type, if lv equals DECK_LOG_LEVEL.
#define pr_level_debug_var(lv, var) do{if((lv) == (DECK_LOG_LEVEL)){pr_debug_var(var);}}while(0)

#else
#define pr_debug(...)
#define pr_sysdebug
#define pr_debug_loc()
#define pr_debug_var(var)

#define pr_level_debug(lv, ...)
#define pr_level_debug_loc(lv)
#define pr_level_debug_var(lv, var)
#endif

#endif
