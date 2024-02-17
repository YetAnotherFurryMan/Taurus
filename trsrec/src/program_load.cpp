#include "program.hpp"

namespace trsrec{
    int Program::load(){
        if(this->m_Regex.empty())
            return -1; // Should be unreachable

        trsre::Token tok;
        tok.m_Body = trsre::parse_rule(this->m_Regex.data());

        if(tok.m_Body.empty())
            return 1; // TODO: !!! Real errno

        this->m_Token = tok;

        return 0;
    }
}

