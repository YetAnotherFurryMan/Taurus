#ifndef _TRSCLI_H_
#define _TRSCLI_H_

/*
 * enum trscli_LogType
 * @description An enum of log types.
 */
typedef enum{
    TRSCLI_LOG_TYPE_INF = 0,
    TRSCLI_LOG_TYPE_WAR,
    TRSCLI_LOG_TYPE_ERR
} trscli_LogType;

/*
 * trscli_log_type_cstr
 * @param t - a type
 * @return cstr of type short.
 */
const char* trscli_log_type_cstr(trscli_LogType t);

/*
 * trscli_log
 * @param t - a type
 * @param msg - a message in cstr
 * @description Prints log with given type.
 */
void trscli_log(trscli_LogType t, const char* msg);

#endif //_TRSCLI_H_
