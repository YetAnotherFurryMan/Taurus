#pragma once

#include <trsre.hpp>

#include <vector>
#include <string>
#include <string_view>

#include "state.hpp"

// TODO !!! optimize 
// TODO !!! get_specjal(s) for EOE, any and things like \w \t \n \r \01 \x01

namespace trsrec{
    namespace c{
        std::string get_char(char c, bool neg, bool expect, State& state);
        std::string get_chars(char c, bool neg, bool expect, State& state);

        std::string get_range(char a, char b, bool neg, bool expect, State& state);
        std::string get_ranges(char a, char b, bool neg, bool expect, State& state);

        std::string get_specjal(char c, bool neg, bool expect, State& state);
        std::string get_specjals(char c, bool neg, bool expect, State& state);

        std::string get_choose(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state);
        std::string get_chooses(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state);

        std::string get_group(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state);
        std::string get_groups(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state);
    }
}

