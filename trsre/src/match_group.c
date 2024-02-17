#include <trsre.h>

long trsre_match_group_ext(const char* rule, const char* text, size_t* ti, bool n){
    bool plus = false;
    bool matches = true;

    size_t r = (rule[0] == '('?1:0); char rc;
    size_t t = 0; char tc;
    while((rc = rule[r]) && (tc = text[t])){
        if(rc == ')')
            break;
        
        bool neg = false;
        if(rc == '^'){
            neg = true;
            rc = rule[++r];
        }
        if(n)
            neg = !neg;

        long x = 0;
        if(rc == '('){
            size_t tib = 0;
            x = trsre_match_group(&rule[r], &text[t], &tib);
            if(!neg && tib > 0)
                t += tib - 1;
        } else{
            x = trsre_match_char(&rule[r], tc);
        }

        // Matching failed
        if(x <= 0){
            x *= -1;
            matches = neg; // if(neg) matches = true;
        } else{
            matches = !neg; // if(neg) matches = false;
        }

        r += x;
        rc = rule[r];

        // Remember ^
        if(neg)
            x++; 

        // * + and ?
        if(rc == '?'){
            matches = true;
            r++; 
        } else if(rc == '*' || rc == '+'){
            if(matches){
                r -= x;
                plus = true;
            } else{
                r++;
                if(!plus && rc == '+')
                    break;
                matches = true;
                continue;
            }
        }

        if(!matches)
            break;

        t++;
    }

    // Match $ and find out if rule is not complete
    tc = text[t];
    rc = rule[r];

    if(tc == 0){
        if(matches && rc == '$'){
            r++;
        } else if(rc != 0 && rc != ')' && !plus){
            matches = false;
            
            // Group still matches for rule like "ab*c*" and text "a"
            size_t rr = r;
            while((rc = rule[rr])){
                if(rc == ')')
                    break;

                if(rc == '^')
                    rc = rule[++rr];

                long x = 0;
                if(rc == '(')
                    x = trsre_match_group(&rule[rr], "", 0);
                else
                    x = trsre_match_char(&rule[rr], ' ');

                if(x < 0)
                    x *= -1;

                rr += x;

                if(rule[rr] == '*' || rule[rr] == '?'){
                    matches = true;
                    rr++;
                } else if(rule[rr] == 0 || rule[rr] == ')'){ 
                    break;
                } else{
                    matches = false;
                    break;
                }
            }
        } 
    }

    // Find end of group
    int brackets = 1;
    while((rc = rule[r]) && brackets){
        if(rc == '\\')
            r++;
        else if(rc == '(')
            brackets++;
        else if(rc == ')')
            brackets--;
        r++;
    }

    if(ti)
        *ti = t;

    // Negate if not matched
    if(!matches)
        r *= -1;

    return r;
}

long trsre_match_group(const char* rule, const char* text, size_t* ti){
    return trsre_match_group_ext(rule, text, ti, false);
}

