#include <trsre.h>

size_t trsre_match(const char* rule, const char* text) {
    size_t matches = 0;

    trsre_match_group(rule, text, &matches);

    return matches;
}

