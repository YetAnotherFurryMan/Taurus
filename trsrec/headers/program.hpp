#pragma once

#include <trsre.hpp>

#include <sstream>
#include <string_view>

namespace trsrec{
    enum class Language { 
        C = 0, 
        CXX 
    };

    struct Program{
        std::string_view m_Program;
        std::string_view m_Regex;
        
        // Optional
        Language m_Language = Language::C;
        FILE* m_Output = stdout;
        std::string_view m_Label = "trsre";
        std::string_view m_Input = "input";

        // Internal
        trsre::Token m_Token;
        std::stringstream m_SS;
        size_t m_IdEnum = 0;

        int init(int argc, const char** argv);
        int load();
        int generate_c();
        int generate_cxx();
        int terminate();

        static char get_lit(const char** s);
    };

    // Debug and other "specjal" functions 
    void log_token(const trsre::Token& tok, const std::string& pref = "");
}

