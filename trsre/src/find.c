#include <trsre.h>

const char* trsre_find(const char* rule, const char* text, size_t* len){
    const char* found = text;
    size_t matches = 0;

    long x = -1;

    while(*found){
        x = trsre_match_group(rule, found, &matches);

        if(x > 0)
            break;
        
        found++;
    }

    if(len){
        *len = matches;
    }

    return found;
}

