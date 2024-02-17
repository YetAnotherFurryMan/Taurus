#include "program.hpp"

#include <cstdio>

namespace trsrec{
    int Program::terminate(){
        if(this->m_Output != stdout)
            fclose(this->m_Output);

        this->m_Output = stdout;

        return 0;
    }
}

