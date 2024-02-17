#define TRSRE_EXT
#define _TRSRE_HPP_NO_WARN_
#include "program.hpp"

#include <trscli.hpp>

namespace trsrec{
    void log_token(const trsre::Token& tok, const std::string& pref){
        std::string log = pref;
        log += "Got: ";
        log += trsre::trsre_token_type_to_string_ext(tok.m_Type);
        log += "-";
        log += trsre::trsre_token_mode_to_string_ext(tok.m_Mode);
        log += ":";
        log += tok.m_Value;
        trscli::log(trscli::TRSCLI_LOG_TYPE_INF, log);

        if(tok.m_Type == trsre::TRSRE_TOKEN_TYPE_CHOOSE || tok.m_Type == trsre::TRSRE_TOKEN_TYPE_GROUP){
            for(auto& t: tok.m_Body){
                log_token(t, pref + "    ");
            }
        }
    }

}

