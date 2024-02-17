#include "program.hpp"

namespace trsrec{
    char Program::get_lit(const char** s){
        if(**s == '\\')
            (*s)++;

        char r = **s;
        
        (*s)++;

        return r;
    }
}

