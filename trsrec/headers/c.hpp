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

        // Funny that this is the oposite of EOE 
        std::string expect_any(char c, bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth);
        std::string expect_anys(char c, bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth, std::string_view prefix, size_t* id);
        std::string get_any(char c, bool neg, std::string_view input, std::string_view iter, size_t depth);
        std::string get_anys(char c, bool neg, std::string_view input, std::string_view iter, size_t depth);

        // Looping of EOE has no sens
        std::string expect_eoe(bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth);
        std::string get_eoe(bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth);

        /*std::string expect_range(char a, char b, bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth);
        std::string expect_ranges(char a, char b, bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth, std::string_view prefix, size_t* id);
        std::string get_range(char a, char b, bool neg, std::string_view input, std::string_view iter, size_t depth);
        std::string get_ranges(char a, char b, bool neg, std::string_view input, std::string_view iter, size_t depth);*/ 

        std::string get_range(char a, char b, bool neg, bool expect, State& state);
        std::string get_ranges(char a, char b, bool neg, bool expect, State& state);

        std::string get_choose(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state);
        std::string get_chooses(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state);

        std::string get_group(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state);
        std::string get_groups(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state);
    }
}

