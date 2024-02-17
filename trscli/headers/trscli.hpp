#pragma once 

#include <string>

#include <cstring>

namespace trscli {
    extern "C" {
        #include "trscli.h" 
    }

    using LogType = trscli_LogType;

    /*
     * trscli::log_type_cstr (aka trscli_log_type_cstr)
     * @param t - a type
     * @return cstr of type short.
     */
    inline const char* log_type_cstr(LogType t){
        return trscli_log_type_cstr(t);
    }

    /*
     * trscli::log (aka trscli_log)
     * @param t - a type
     * @param msg - a message in cstr 
     * @description Prints log with given type.
     */
    inline void log(LogType t, const char* msg){
        trscli_log(t, msg);
    }

    /*
     * trscli::log (aka trscli_log)
     * @param t - a type
     * @param msg - a message in std::string
     * @description Prints log with given type.
     */
    inline void log(LogType t, const std::string& msg){
        trscli_log(t, msg.c_str());
    }
}

