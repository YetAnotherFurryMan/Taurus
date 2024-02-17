#pragma once

#include <vector>
#include <string>

// !!!TODO: implement for stringview

#if defined(TRSRE_EXT) && !defined(_TRSRE_HPP_NO_WARN_)
#warning "Taurus regex extensions are not forked to C++ header, so you must use C versions."
#endif

namespace trsre {
    extern "C" {
        #include "trsre.h"
    }

    using cToken = trsre_Token;
    using TokenType = trsre_TokenType;
    using TokenMode = trsre_TokenMode;

    /*
     * struct Token 
     * @description C++ reimplementation of trsre_Token allows to store the body of group or choose
     */
    struct Token{
        std::string m_Value = "";
        std::vector<Token> m_Body;
        TokenType m_Type = TRSRE_TOKEN_TYPE_EMPTY;
        TokenMode m_Mode = TRSRE_TOKEN_MODE_SINGLE;

        Token() = default;
        Token(cToken t):
            m_Value{std::string(t.m_Value).substr(0, t.m_Length)},
            m_Type{t.m_Type},
            m_Mode{t.m_Mode}
        {}
    };

    /*
     * trsre::match_char (aka trsre_match_char)
     * @param rule - cstr with regex 
     * @param c - char to match 
     * @return length of rule that matches c, negative if c does'n match, 0 if rule or c equals 0
     */
    inline long match_char(const char* rule, char c){
        return trsre_match_char(rule, c);
    }

     /*
     * trsre::match_char (aka trsre_match_char)
     * @param rule - std::string with regex 
     * @param c - char to match 
     * @return length of rule that matches c, negative if c does'n match, 0 if rule or c equals 0
     */
    inline long match_char(const std::string& rule, char c){
        return trsre_match_char(rule.c_str(), c);
    }

    /*
     * trsre::match (aka trsre_match)
     * @param rule - cstr with regex 
     * @param text - cstr with text to match 
     * @return length of text that matches rule 
     */
    inline size_t match(const char* rule, const char* text){
        return trsre_match(rule, text);
    }

    /*
     * trsre::match (aka trsre_match)
     * @param rule - std::string with regex 
     * @param text - std::string with text to match 
     * @return length of text that matches rule 
     */
    inline size_t match(const std::string& rule, const std::string& text){
        return trsre_match(rule.c_str(), text.c_str());
    }

    /*
     * trsre::find (aka trsre_find)
     * @param rule - cstr with regex 
     * @param text - cstr with text to match 
     * @return a std::psir with ptr to the first char of found match, or ptr to \0 in text if not found and length of found match should be pasted
     */
    inline std::pair<const char*, size_t> find(const char* rule, const char* text){
        size_t len = 0;
        auto r = trsre_find(rule, text, &len);
        return std::pair<const char*, size_t>(r, len);
    }

    /*
     * trsre::find (aka trsre_find)
     * @param rule - std::string with regex 
     * @param text - std::string with text to match 
     * @return a std::psir with ptr to the first char of found match, or ptr to \0 in text if not found and length of found match should be pasted
     */
    inline std::pair<const char*, size_t> find(const std::string& rule, const std::string& text){
        size_t len = 0;
        auto r = trsre_find(rule.c_str(), text.c_str(), &len);
        return std::pair<const char*, size_t>(r, len);
    }

    /*
     * get_ctoken (aka trsre_get_token)
     * @param rule - cstr with regex 
     * @return the very first token in rule
     */
    inline cToken get_ctoken(const char* rule){
        return trsre_get_token(rule);
    }
    
    /*
     * get_ctoken (aka trsre_get_token)
     * @param rule - std::string with regex 
     * @return the very first token in rule
     */
    inline cToken get_ctoken(const std::string& rule){
        return trsre_get_token(rule.c_str());
    }

    /**/ 
    inline std::vector<Token> parse_rule(const char* rule){
        std::vector<Token> tokens;

        do{
            cToken tok = get_ctoken(rule);
            rule += tok.m_Length;

            if(tok.m_Mode & TRSRE_TOKEN_MODE_NOT)
                rule++;

            if(tok.m_Mode & ~TRSRE_TOKEN_MODE_NOT)
                rule++;

            tokens.emplace_back(tok);
        } while(*rule);

        for(auto& tok: tokens){
            if(tok.m_Type == TRSRE_TOKEN_TYPE_CHOOSE || tok.m_Type == TRSRE_TOKEN_TYPE_GROUP)
                tok.m_Body = parse_rule(tok.m_Value.substr(1, tok.m_Value.length() - 2).c_str());
        }

        return tokens;
    }
}

