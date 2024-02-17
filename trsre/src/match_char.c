#include <trsre.h>

long trsre_match_char(const char* rule, char c){
    char rc = rule[0];
    if(!rc || !c)
        return 0;
    
    size_t r = 0;
    switch(rc){
        case '[': {
            int x = -1;
            r++;
            while(rule[r] != ']' && rule[r]){
                rc = rule[r];
                if(rc == '\\')
                    rc = rule[++r];
                else if(rc == '.')
                    rc = c;
                else if(rc == '-' && r > 0 && rule[++r])
                    if(c >= rule[r - 2] && c <= rule[r])
                        rc = c;

                if(rc == c){
                    while(rule[r] != ']' && rule[r])
                        r++;
                    x = 1;
                    break;
                }

                r++;
            }
            r++;
            r *= x; // Negate if not match
        } break;
        case '.': {
            r++;
        } break;
        case '\\': {
            r = 2;
            rc = rule[1];
            if(rc != c)
                r *= -1;
        } break;
        default: {
            r = -1;
            if(rule[1] == '-' && rule[2]){
                r = -3;
                if((c >= rc && c <= rule[2]) || (c >= rule[2] && c <= rc))
                    r *= -1;
            } else if(rc == c)
                r *= -1;
        }
    }

    return r;
}

