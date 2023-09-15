#pragma once

#include <string>
#include <optional>
#include <string_view>

namespace trs::lexer{
    enum class TokenType{
        TT_ERROR = -1,
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
        TT_SEPARATOR_HARD,
        TT_OP_ROUND_BRACKET_L,
        TT_OP_ROUND_BRACKET_R,
        TT_OP_SQUARE_BRACKET_L,
        TT_OP_SQUARE_BRACKET_R,
        TT_OP_CURLY_BRACKET_L,
        TT_OP_CURLY_BRACKET_R,
        TT_OP_ANGLE_BRACKET_L,
        TT_OP_SMALLER_OR_EQUAL,
        TT_OP_ANGLE_BRACKET_R,
        TT_OP_LARGER_OR_EQUAL,
        TT_OP_COLON,
        TT_OP_QUESTION_MARK,
        TT_OP_EXCLAMATION_MARK,
        TT_OP_NOT_EQUAL,
        TT_OP_MATH_ADD, 
        TT_OP_MATH_ADD_EQ,
        TT_OP_MATH_SUB, 
        TT_OP_MATH_SUB_EQ,
        TT_OP_MATH_MUL, 
        TT_OP_MATH_MUL_EQ,
        TT_OP_MATH_DIV, 
        TT_OP_MATH_DIV_EQ,
        TT_OP_MATH_MOD, 
        TT_OP_MATH_MOD_EQ,
        TT_OP_MATH_BIN_AND, 
        TT_OP_MATH_BIN_AND_EQ,
        TT_OP_MATH_BIN_OR, 
        TT_OP_MATH_BIN_OR_EQ,
        TT_OP_MATH_BIN_XOR, 
        TT_OP_MATH_BIN_XOR_EQ,
        TT_OP_MATH_BIN_NOT,
        TT_OP_MATH_INC,
        TT_OP_MATH_DEC,
        TT_OP_EQUALITY,
        TT_OP_EQUALS,
        TT_OP_LOGIC_AND_AND,
        TT_OP_LOGIC_OR_OR,
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
        TT_KW_TYPE_STR,
        TT_KW_TYPE_BOOL
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
        TokenType get_operator(size_t& pos);
    };
}