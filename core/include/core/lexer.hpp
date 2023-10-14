#pragma once

#include <string>
#include <optional>
#include <string_view>

namespace trs::core{
    //This enum represents lexical token type
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
        TT_CHAR,
        TT_WHITE,
        TT_SEPARATOR,
        TT_OPERATOR,
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

    //This class represents one lexical token
    struct Token{
        TokenType m_Type = TokenType::TT_EMPTY;
        std::optional<std::string_view> m_Value;

        //Returns true if this equals t (both m_Type and m_Value)
        inline bool operator==(const Token& t){
            return (t.m_Type == m_Type) && (t.m_Value.value_or("") == m_Value.value_or(""));
        }
    };

    //The Lexer class
    class Lexer{
    public:
        //Sets source for the lexer
        void set_source(const std::string& src);
        
        //Resets position in source
        void reset();

        //Returns next token
        Token next();

    private:
        size_t m_Positition = 0;
        std::string m_Source;

        TokenType get_number(size_t& pos);
        TokenType get_identifier(size_t& pos);
    };
}