#pragma once

#include <string>
#include <optional>
#include <string_view>

namespace trs::lexer{
    enum class TokenType{
        TT_EMPTY = 0,
        TT_IDENTIFIER,
        TT_STRING,
        TT_NUMBER,
        TT_NUMBER_DEC,
        TT_NUMBER_OCT,
        TT_NUMBER_HEX,
        TT_NUMBER_BIN,
        TT_FLOAT,
        TT_OPERATOR,
        TT_CHAR,
        TT_WHITE,
        TT_SEPARATOR,
        TT_KW_VAR,
        TT_KW_CONST,
        TT_KW_TYPE_U8,
        TT_KW_TYPE_U16,
        TT_KW_TYPE_U32,
        TT_KW_TYPE_U64,
        TT_KW_TYPE_U128,
        TT_KW_TYPE_USIZE,
        TT_KW_TYPE_I8,
        TT_KW_TYPE_I16,
        TT_KW_TYPE_I32,
        TT_KW_TYPE_I64,
        TT_KW_TYPE_I128,
        TT_KW_TYPE_ISIZE,
        TT_KW_TYPE_F32,
        TT_KW_TYPE_F64,
        TT_KW_TYPE_FSIZE,
        TT_KW_TYPE_SIZE,
        TT_KW_TYPE_CHAR,
        TT_KW_TYPE_STR
    };

    struct Token{
        std::optional<std::string_view> value;
        TokenType type = TokenType::TT_EMPTY;
    };

    class Lexer{
    public:
        void set_source(const std::string& src);
        void reset();
        Token next();

    private:
        size_t m_Positition = 0;
        std::string m_Source;

        TokenType get_number(size_t& pos);
        TokenType get_identifier(size_t& pos);
    };
}