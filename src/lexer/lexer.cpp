#include <lexer/lexer.hpp>

#include <array>
#include <unordered_map>

#include <cctype>

namespace trs::lexer{
    void Lexer::set_source(const std::string& src){
        this->m_Source = src;
        reset();
    }

    void Lexer::reset(){
        this->m_Positition = 0;
    }

    Token Lexer::next(){
        std::string_view value{ this->m_Source };
        value = value.substr(this->m_Positition);

        if(value.empty())
            return {type: TokenType::TT_EMPTY};

        char ch = 0;
        size_t pos = 0;
        TokenType type = TokenType::TT_EMPTY;

        // Skipp white characters
        while(pos < value.length() && (value[pos] == ' ' || value[pos] == '\t'))
            pos++;

        if(pos > 0){
            value = value.substr(pos);
            this->m_Positition += pos;
            pos = 0;
        }

        // Operator-case
        std::array<char, 23> operators = {
            '+', '-', '*', '/', '%', '&', '|', '^', '!', '~', '(', ')', ':', '=', '<', '>', '?', ',', '.', '[', ']', '{', '}'
        };

        for(char c: operators){
            if(c == value[0]){
                this->m_Positition++;
                return {value: value.substr(0, 1), type: TokenType::TT_OPERATOR};
            }
        }

        // Separator-case
        if(value[0] == '\n' || value[0] == ';'){
            this->m_Positition++;
            return {type: TokenType::TT_SEPARATOR};
        }

        // Number-case, identifier-case and error-case
        if(value[0] >= '0' && value[0] <= '9'){
            type = get_number(pos);
        } else if(value[0] == '_' || (value[0] >= 'A' && value[0] <= 'Z') || (value[0] >= 'a' && value[0] <= 'z')){
            type = get_identifier(pos);
        } else{
            // TODO: Lexer error!!!
            this->m_Positition++;
            return {type: TokenType::TT_EMPTY};
        }

        //Update global position
        this->m_Positition += pos;

        return {value: value.substr(0, pos), type: type};
    }

    TokenType Lexer::get_number(size_t& pos){
        std::string_view value = this->m_Source;
        value = value.substr(this->m_Positition);

        // First character already checked
        pos = 1;

        if(value.length() == 1)
            return TokenType::TT_NUMBER_DEC;

        TokenType type = TokenType::TT_NUMBER_DEC;
        char get_id = 0;

        // Octal numbers starts with 0 (e.g. 012 = 10)
        if(value[0] == '0'){
            type = TokenType::TT_NUMBER_OCT;
            get_id = 1;
        }
        
        switch(value[1]){
            // Decimal number
            case '0' ... '9':
                break;
            // Hexadecimal number (skipp x) (e.g. 0xa = 10)
            case 'x':
                type = TokenType::TT_NUMBER_HEX;
                get_id = 2;
                pos++;
                break;
            // Binary number (skipp b) (e.g. 0b1010 = 10)
            case 'b':
                type = TokenType::TT_NUMBER_BIN;
                get_id = 3;
                pos++;
                break;
            // Error case
            default:
                // TODO: Error case!!!
                return TokenType::TT_EMPTY;
        }

        // Validation functions
        using get_t = bool(char);
        std::array<get_t*, 4> get = {
            [](char c){ return c >= '0' && c <= '9'; },
            [](char c){ return c >= '0' && c <= '7'; },
            [](char c){ return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); },
            [](char c){ return c == '0' || c == '1'; }
        };

        // Move position to last valid character
        pos++;
        while(pos < value.length() && get[get_id](value[pos]))
            pos++;

        return type;
    }

    TokenType Lexer::get_identifier(size_t& pos){
        std::string_view value = this->m_Source;
        value = value.substr(this->m_Positition);

        // First character already checked
        pos = 1;

        // Move position to last valid character
        while(pos < value.length() && (value[pos] == '_' || std::isalnum(value[pos])))
            pos++;

        // Keyword-case
        std::unordered_map<std::string_view, TokenType> keywords = {
            {"var", TokenType::TT_KW_VAR},
            {"const", TokenType::TT_KW_CONST},
            {"u8", TokenType::TT_KW_TYPE_U8},
            {"u16", TokenType::TT_KW_TYPE_U16},
            {"u32", TokenType::TT_KW_TYPE_U32},
            {"u64", TokenType::TT_KW_TYPE_U64},
            {"u128", TokenType::TT_KW_TYPE_U128},
            {"usize", TokenType::TT_KW_TYPE_USIZE},
            {"i8", TokenType::TT_KW_TYPE_I8},
            {"i16", TokenType::TT_KW_TYPE_I16},
            {"i32", TokenType::TT_KW_TYPE_I32},
            {"i64", TokenType::TT_KW_TYPE_I64},
            {"i128", TokenType::TT_KW_TYPE_I128},
            {"isize", TokenType::TT_KW_TYPE_ISIZE},
            {"f32", TokenType::TT_KW_TYPE_F32},
            {"f64", TokenType::TT_KW_TYPE_F64},
            {"fsize", TokenType::TT_KW_TYPE_FSIZE},
            {"size", TokenType::TT_KW_TYPE_SIZE},
            {"char", TokenType::TT_KW_TYPE_CHAR},
            {"str", TokenType::TT_KW_TYPE_STR}
        };

        value = value.substr(0, pos);
        
        if(keywords.contains(value))
            return keywords[value];
        
        return TokenType::TT_IDENTIFIER;
    }
}