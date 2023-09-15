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

            if(value.empty())
                return {type: TokenType::TT_EMPTY};
        }

        switch(value[0]){
            // Separator-case
            case '\n':
                this->m_Positition++;
                return {type: TokenType::TT_SEPARATOR};
            case ';':
                this->m_Positition++;
                return {type: TokenType::TT_SEPARATOR_HARD};
            // Number-case
            case '0' ... '9':
                type = get_number(pos);
                break;
            // Identifier-case
            case '_':
            case 'A' ... 'Z':
            case 'a' ... 'z':
                type = get_identifier(pos);
                break;
            // String-case
            case '\"':
                //TODO: String-case!!!
                return {type: TokenType::TT_ERROR};
            // Char-case
            case '\'':
                //TODO: Char-case!!!
                return {type: TokenType::TT_ERROR};
            // Operator-case
            default:
                type = get_operator(pos);
                this->m_Positition += pos;
                return {type: type};
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
            // Decimal or octal number
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
            // Single number
            default:
                return TokenType::TT_NUMBER_DEC;
        }

        // Validation functions
        using get_t = bool(char);
        std::array<get_t*, 4> get = {
            [](char c){ return c >= '0' && c <= '9'; },
            [](char c){ return c >= '0' && c <= '7'; },
            [](char c){ return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); },
            [](char c){ return c == '0' || c == '1'; }
        };

        //Validate if next is needed and is correct
        if(get_id > 0){
            if(pos >= value.length() || !get[get_id](value[pos]))
                return TokenType::TT_ERROR;
        }

        // Move position to last valid character
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
            {"str", TokenType::TT_KW_TYPE_STR},
            {"bool", TokenType::TT_KW_TYPE_BOOL}
        };

        value = value.substr(0, pos);
        
        if(keywords.contains(value))
            return keywords[value];
        
        return TokenType::TT_IDENTIFIER;
    }

    TokenType Lexer::get_operator(size_t& pos){
        std::string_view value = this->m_Source;
        value = value.substr(this->m_Positition);

        pos = 1;

        TokenType type = TokenType::TT_EMPTY;

        switch(value[0]){
            // Brackets
            case '(':
                return TokenType::TT_OP_ROUND_BRACKET_L;
            case ')':
                return TokenType::TT_OP_ROUND_BRACKET_R;
            case '[':
                return TokenType::TT_OP_SQUARE_BRACKET_L;
            case ']':
                return TokenType::TT_OP_SQUARE_BRACKET_R;
            case '{':
                return TokenType::TT_OP_CURLY_BRACKET_L;
            case '}':
                return TokenType::TT_OP_CURLY_BRACKET_R;
            // Can make logic operator (>= <=)
            case '<':
                type =  TokenType::TT_OP_ANGLE_BRACKET_L;
                break;
            case '>':
                type = TokenType::TT_OP_ANGLE_BRACKET_R;
                break;
            // Colon
            case ':':
                return TokenType::TT_OP_COLON;
            // Marks
            case '?':
                return TokenType::TT_OP_QUESTION_MARK;
            // Can make logic operator (!=)
            case '!':
                type =  TokenType::TT_OP_EXCLAMATION_MARK;
                break;
            // Math, can make equality operator
            case '+':
                type = TokenType::TT_OP_MATH_ADD;
                break;
            case '-':
                type = TokenType::TT_OP_MATH_SUB;
                break;
            case '*':
                type = TokenType::TT_OP_MATH_MUL;
                break;
            case '/':
                type = TokenType::TT_OP_MATH_DIV;
                break;
            case '%':
                type = TokenType::TT_OP_MATH_MOD;
                break;
            // Binary
            case '~':
                return TokenType::TT_OP_MATH_BIN_NOT;
            // Can make equality operator or/and logical operator
            case '&':
                type = TokenType::TT_OP_MATH_BIN_AND;
                break;
            case '|':
                type = TokenType::TT_OP_MATH_BIN_OR;
                break;
            case '^':
                type = TokenType::TT_OP_MATH_BIN_XOR;
                break;
            // Equalizer, can make logic operator (==)
            case '=':
                type = TokenType::TT_OP_EQUALITY;
                break;
            // Unknown character
            default:
                return TokenType::TT_ERROR;
        }

        if(value.length() == 1)
            return type;

        // 2-chars operators
        switch(value[1]){
            case '=':
                type = (TokenType)(((int)type) + 1);
                break;
            case '+':
                if(type == TokenType::TT_OP_MATH_ADD)
                    type = TokenType::TT_OP_MATH_INC;
                else
                    return type;
                break;
            case '-':
                if(type == TokenType::TT_OP_MATH_SUB)
                    type = TokenType::TT_OP_MATH_DEC;
                else
                    return type;
                break;
            case '&':
                if(type == TokenType::TT_OP_MATH_BIN_AND)
                    type = TokenType::TT_OP_LOGIC_AND_AND;
                else
                    return type;
                break;
            case '|':
                if(type == TokenType::TT_OP_MATH_BIN_OR)
                    type = TokenType::TT_OP_LOGIC_OR_OR;
                else
                    return type;
                break;
            default:
                return type;
        }

        pos++;
        return type;
    }
}