#include <trscli.h>

#include <stdio.h>

const char* trscli_log_type_cstr(trscli_LogType t){
    switch(t){
#define CASE_T(t) case TRSCLI_LOG_TYPE_##t: return #t;
        CASE_T(INF)
        CASE_T(WAR)
        CASE_T(ERR)
#undef CASE_T
        default:
            return "???";
    }
}


void trscli_log(trscli_LogType t, const char* msg){
    int color = 0;
    switch(t){
        case TRSCLI_LOG_TYPE_INF:
            break;
        case TRSCLI_LOG_TYPE_WAR:
            color = 93;
            break;
        case TRSCLI_LOG_TYPE_ERR:
            color = 91;
            break;
        default:
            color = 1;
            break;
    }
    fprintf(stderr, "\033[%dm[%s]: %s\n\033[m", color, trscli_log_type_cstr(t), msg);
}

