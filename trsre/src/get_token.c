#include <trsre.h>

trsre_Token trsre_get_token(const char* rule){
    trsre_Token tok = {0};

    if(rule[0] == '^'){
        tok.m_Mode = TRSRE_TOKEN_MODE_NOT;
        rule++;
    }

    tok.m_Value = rule;
    
    long x = 0;
    switch(rule[0]){
        case '(': {
            tok.m_Type = TRSRE_TOKEN_TYPE_GROUP;
            x = trsre_match_group(rule, " ", 0);
            if(x < 0)
                x *= -1;
        } break;
        case '[': {
            tok.m_Type = TRSRE_TOKEN_TYPE_CHOOSE;
            x = trsre_match_char(rule, ' ');
            if(x < 0)
                x *= -1;
        } break;
        case '$': {
            tok.m_Type = TRSRE_TOKEN_TYPE_EOE;
            x = 1;
        } break;
        case '.': {
            tok.m_Type = TRSRE_TOKEN_TYPE_ANY;
            x = 1;
        } break;
        default: {
            tok.m_Type = TRSRE_TOKEN_TYPE_LITERAL;
            x = trsre_match_char(rule, ' ');
            if(x < 0)
                x *= -1;
            for(long i = 0; i < x; i++){
                if(rule[i] == '\\')
                    i++;
                else if(rule[i] == '-'){
                    tok.m_Type = TRSRE_TOKEN_TYPE_RANGE;
                    break;
                }
            }
        }
    }

    if(x == 0){
        tok.m_Type = 0;
        return tok;
    }

    tok.m_Length = x;

    rule += x;
    switch(rule[0]){
        case '+': {
            tok.m_Mode |= TRSRE_TOKEN_MODE_PLUS;
        } break;
        case '*': {
            tok.m_Mode |= TRSRE_TOKEN_MODE_STAR;
        } break;
        case '?': {
            tok.m_Mode |= TRSRE_TOKEN_MODE_QUESTION;
        } break;
        default: {
            //tok.m_Length--;
        }
    }

    return tok;
}

