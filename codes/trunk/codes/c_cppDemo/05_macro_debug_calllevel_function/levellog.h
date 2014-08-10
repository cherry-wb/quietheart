/*This file contains common resource for module module.*/
/*This is use for print debug information with function call level.
Note:if we use function may be called by multi thread, we should use moule_debug2(...),module_enter2(...),module_leave2(...).
*/
#ifndef __MODULE_COMMON_H__
#define __MODULE_COMMON_H__

#define MODULE_DEBUG 1

#if MODULE_DEBUG == 1
#define MODULE_PREFIX "[module]"
/**@brief Print information use C printf like format with indent according to function calls.*/
#define module_debug(...) do{\
                extern int g_moduleTmpLeavel;\
                extern int g_moduleCallLeavel;\
                fprintf(stderr, "%s:%15.15s:%22.22s():%4.0d - ", MODULE_PREFIX, __FILE__, __func__, __LINE__);\
                for (g_moduleTmpLeavel = 0; g_moduleTmpLeavel < g_moduleCallLeavel; ++g_moduleTmpLeavel)\
                {\
                    fprintf(stderr, "-|");\
                }\
                fprintf(stderr,__VA_ARGS__);\
                }while(0)

/*@brief Use it when enter in a function.*/
#define module_enter() do{\
                extern int g_moduleCallLeavel;\
                ++g_moduleCallLeavel;\
                if (g_moduleCallLeavel < 0)\
                {\
                    g_moduleCallLeavel = 0;\
                }\
                else if (g_moduleCallLeavel > 20)\
                {\
                    g_moduleCallLeavel = 0;\
                }\
                module_debug("<<<<<<[ Enter ] >>>>>>.\n");\
                }while(0)

/*@brief Use it before leave a function.*/
#define module_leave() do{\
                extern int g_moduleCallLeavel;\
                module_debug("<<<<<<[ Leave ] >>>>>>.\n");\
                --g_moduleCallLeavel;\
                if (g_moduleCallLeavel < 0)\
                {\
                    g_moduleCallLeavel = 0;\
                }\
                else if (g_moduleCallLeavel > 20)\
                {\
                    g_moduleCallLeavel = 0;\
                }\
                }while(0)

/**@brief Print information use C printf like format without indent , better use it in thread, or when we don't care for call level.*/
#define module_debug2(...) do{\
                fprintf(stderr, "%s:%8.8s:%25.25s():%4.0d - ", MODULE_PREFIX, __FILE__, __func__, __LINE__);\
                fprintf(stderr, "|");\
                fprintf(stderr,__VA_ARGS__);\
                }while(0)

#define module_enter2() do{\
                module_debug2("<<<<<<[ Routine Enter ] >>>>>>.\n");\
                }while(0)

#define module_leave2() do{\
                module_debug2("<<<<<<[ Routine Leave ] >>>>>>.\n");\
                }while(0)

#else
#define module_debug(...)
#define module_enter()
#define module_leave()
#define module_debug2(...)
#define module_enter2()
#define module_leave2()
#endif

#endif
