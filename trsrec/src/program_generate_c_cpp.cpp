#include "program.hpp"

#include "c.hpp"

namespace trsrec{
    int Program::generate_c(){
        this->m_SS << "// Expecting " << this->m_Input << " to be const char* with input" << std::endl;
        this->m_SS << "size_t matches = 0; // The return value" << std::endl;
       
        int status = 0;

        State state = {
            this->m_Input,
            "matches",
            this->m_Label,
            this->m_Label,
            0,
            0
        };

        for(auto& tok: this->m_Token.m_Body){
            this->m_SS << "// " << tok.m_Value << std::endl;
            trsre::TokenMode mod = (trsre::TokenMode)(tok.m_Mode);
            bool neg = (mod & trsre::TRSRE_TOKEN_MODE_NOT);
            mod = trsre::TokenMode(mod & ~trsre::TRSRE_TOKEN_MODE_NOT);
            bool expect = mod == trsre::TRSRE_TOKEN_MODE_SINGLE || mod == trsre::TRSRE_TOKEN_MODE_PLUS;
            bool loop = mod == trsre::TRSRE_TOKEN_MODE_STAR || mod == trsre::TRSRE_TOKEN_MODE_PLUS;
            switch(tok.m_Type){
                case trsre::TRSRE_TOKEN_TYPE_EMPTY:
                    return -1; // Should be unreachable 
                case trsre::TRSRE_TOKEN_TYPE_LITERAL: {
                    const char* value = tok.m_Value.c_str();
                    char c = get_lit(&value);
                    /*if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                        this->m_SS << c::get_char(c, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                        this->m_SS << c::get_chars(c, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                        this->m_SS << c::expect_chars(c, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));
                    else
                        this->m_SS << c::expect_char(c, neg, this->m_Input, "matches", this->m_Label, 0);
                    */ 
                    if(loop)
                        this->m_SS << c::get_chars(c, neg, expect, state);
                    else
                        this->m_SS << c::get_char(c, neg, expect, state);
                } break;
                case trsre::TRSRE_TOKEN_TYPE_ANY:
                case trsre::TRSRE_TOKEN_TYPE_EOE:
                case trsre::TRSRE_TOKEN_TYPE_RANGE: {
                    const char* value = tok.m_Value.c_str();
                    char a = get_lit(&value);
                    value++;
                    char b = get_lit(&value);
                    /*if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                        this->m_SS << c::get_range(a, b, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                        this->m_SS << c::get_ranges(a, b, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                        this->m_SS << c::expect_ranges(a, b, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));
                    else
                        this->m_SS << c::expect_range(a, b, neg, this->m_Input, "matches", this->m_Label, 0);*/ 
                    if(loop)
                        this->m_SS << c::get_ranges(a, b, neg, expect, state);
                    else
                        this->m_SS << c::get_range(a, b, neg, expect, state);
                } break;
                case trsre::TRSRE_TOKEN_TYPE_CHOOSE: {
                    /*if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                        this->m_SS << c::get_choose(tok.m_Body, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                        this->m_SS << c::get_chooses(tok.m_Body, neg, this->m_Input, "matches", 0, this->m_Label, &(this->m_IdEnum));
                    else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                        this->m_SS << c::expect_chooses(tok.m_Body, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));
                    else
                        this->m_SS << c::expect_choose(tok.m_Body, neg, this->m_Input, "matches", this->m_Label, 0);
                    */ 
                    if(loop)
                        this->m_SS << c::get_chooses(tok.m_Body, neg, expect, state);
                    else
                        this->m_SS << c::get_choose(tok.m_Body, neg, expect, state);
                } break;
                case trsre::TRSRE_TOKEN_TYPE_GROUP: {
                    /*if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                        this->m_SS << c::get_group(tok.m_Body, neg, this->m_Input, "matches", 0, this->m_Label, &(this->m_IdEnum));
                    else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                        this->m_SS << c::get_groups(tok.m_Body, neg, this->m_Input, "matches", 0, this->m_Label, &(this->m_IdEnum));
                    else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                        this->m_SS << c::expect_groups(tok.m_Body, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));
                    else
                        this->m_SS << c::expect_group(tok.m_Body, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));*/
                    if(loop)
                        this->m_SS << c::get_groups(tok.m_Body, neg, expect, state);
                    else
                        this->m_SS << c::get_group(tok.m_Body, neg, expect, state);
                } break;
            }
        }

        this->m_SS << this->m_Label << ":" << std::endl;
        return status;
    }

    int Program::generate_cxx(){
        this->m_SS << "// Excepting " << this->m_Input << " to be std::string with input" << this->m_Input << std::endl;
        this->m_SS << "size_t matches = 0; // The return value" << std::endl;
       
        int status = 0;

        /*for(auto& tok: this->m_Token.m_Body){
            this->m_SS << "// " << tok.m_Value << std::endl;
            trsre::TokenMode mod = (trsre::TokenMode)(tok.m_Mode);
            bool neg = (mod & trsre::TRSRE_TOKEN_MODE_NOT);
            mod = trsre::TokenMode(mod & ~trsre::TRSRE_TOKEN_MODE_NOT);
            switch(tok.m_Type){
                case trsre::TRSRE_TOKEN_TYPE_EMPTY:
                    return -1; // Should be unreachable 
                case trsre::TRSRE_TOKEN_TYPE_LITERAL: {
                    const char* value = tok.m_Value.c_str();
                    char c = get_lit(&value);
                    if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                        this->m_SS << c::get_char(c, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                        this->m_SS << c::get_chars(c, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                        this->m_SS << c::expect_chars(c, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));
                    else
                        this->m_SS << c::expect_char(c, neg, this->m_Input, "matches", this->m_Label, 0);
                } break;
                case trsre::TRSRE_TOKEN_TYPE_ANY:
                case trsre::TRSRE_TOKEN_TYPE_EOE:
                case trsre::TRSRE_TOKEN_TYPE_RANGE: {
                    const char* value = tok.m_Value.c_str();
                    char a = get_lit(&value);
                    value++;
                    char b = get_lit(&value);
                    if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                        this->m_SS << c::get_range(a, b, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                        this->m_SS << c::get_ranges(a, b, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                        this->m_SS << c::expect_ranges(a, b, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));
                    else
                        this->m_SS << c::expect_range(a, b, neg, this->m_Input, "matches", this->m_Label, 0);
                } break;
                case trsre::TRSRE_TOKEN_TYPE_CHOOSE: {
                    if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                        this->m_SS << c::get_choose(tok.m_Body, neg, this->m_Input, "matches", 0);
                    else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                        this->m_SS << c::get_chooses(tok.m_Body, neg, this->m_Input, "matches", 0, this->m_Label, &(this->m_IdEnum));
                    else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                        this->m_SS << c::expect_chooses(tok.m_Body, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));
                    else
                        this->m_SS << c::expect_choose(tok.m_Body, neg, this->m_Input, "matches", this->m_Label, 0);
                } break;
                case trsre::TRSRE_TOKEN_TYPE_GROUP: {
                    if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                        this->m_SS << c::get_group(tok.m_Body, neg, this->m_Input, "matches", 0, this->m_Label, &(this->m_IdEnum));
                    else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                        this->m_SS << c::get_groups(tok.m_Body, neg, this->m_Input, "matches", 0, this->m_Label, &(this->m_IdEnum));
                    else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                        this->m_SS << c::expect_groups(tok.m_Body, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));
                    else
                        this->m_SS << c::expect_group(tok.m_Body, neg, this->m_Input, "matches", this->m_Label, 0, this->m_Label, &(this->m_IdEnum));
                } break;
            }
        }*/

        this->m_SS << this->m_Label << ":" << std::endl;
        return status;
    }
}

