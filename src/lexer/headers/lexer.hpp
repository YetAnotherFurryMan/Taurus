#pragma once

#include <string_view>

namespace trs::lexer{
    enum class TokenType{
        TT_EMPTY = 0,
        TT_IDENTIFIER,
        TT_STRING,
        TT_NUMBER,
        TT_FLOAT,
        TT_OPERATOR
    };

    struct Token{
        std::string_view value;
        TokenType type;
    };

    class Lexer{
    public:
        void set_source(std::istream& src);
        void reset();
        Token next();

    private:
        size_t pos = 0;
        size_t begin = 0;
        std::istream& src;
    };
}