#include <lexer/lexer.hpp>

#include <array>

#include <cctype>

namespace trs::lexer{
    void Lexer::set_source(const std::string& src){
        this->src = src;
        reset();
    }

    void Lexer::reset(){
        this->pos = 0;
    }

    Token Lexer::next(){
        std::string_view value{ this->src };
        value = value.substr(this->pos);

        if(value.empty())
            return {type: TokenType::TT_EMPTY};

        char ch = 0;
        size_t pos = 0;
        TokenType type = TokenType::TT_EMPTY;
        BaseTokenType base = BaseTokenType::BTT_EMPTY;

        do{
            ch = value[pos];
            base = type_of(ch);
            pos++;
        } while(pos < value.length() && base == BaseTokenType::BTT_WHITE);

        if(pos - 1 > 0){
            value = value.substr(pos - 1);
            this->pos += pos - 1;
            pos = 1;
        }

        switch(base){
            case BaseTokenType::BTT_EMPTY:
            case BaseTokenType::BTT_WHITE:
                this->pos += pos;
                return {type: TokenType::TT_EMPTY};
            case BaseTokenType::BTT_SEPARATOR:
                this->pos += pos;
                return {type: TokenType::TT_SEPARATOR};
            case BaseTokenType::BTT_OPERATOR:
                this->pos += pos;
                return {value: value.substr(0, pos), type: TokenType::TT_OPERATOR};
            case BaseTokenType::BTT_NUMBER:
                type = get_number(pos);
                break;
            case BaseTokenType::BTT_CHAR:
                type = get_identifier(pos);
                if(type != TokenType::TT_IDENTIFIER){
                    this->pos += pos;
                    return {type: type};
                }
                break;
        }

        this->pos += pos;

        return {value: value.substr(0, pos), type: type};
    }

    BaseTokenType Lexer::type_of(unsigned char c){
        switch(c){
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '&':
            case '|':
            case '^':
            case '!':
            case '~':
            case '(':
            case ')':
            case ':':
            case '=':
            case '<':
            case '>':
            case '?':
            case ',':
            case '.':
            case '[':
            case ']':
            case '{':
            case '}':
                return BaseTokenType::BTT_OPERATOR;
            case ' ':
            case '\t':
                return BaseTokenType::BTT_WHITE;
            case ';':
            case '\n':
                return BaseTokenType::BTT_SEPARATOR;
            case '0' ... '9':
                return BaseTokenType::BTT_NUMBER;
            case '_':
            case 'A' ... 'Z':
            case 'a' ... 'z':
                return BaseTokenType::BTT_CHAR;
        }

        return BaseTokenType::BTT_EMPTY;
    }

    TokenType Lexer::get_number(size_t& pos){
        std::string_view value = this->src;
        value = value.substr(this->pos);
        pos = 1;

        if(value.length() == 1)
            return TokenType::TT_NUMBER_DEC;

        TokenType type = TokenType::TT_NUMBER_DEC;
        char get_id = 0;

        if(value[0] == '0'){
            type = TokenType::TT_NUMBER_OCT;
            get_id = 1;
        }
        
        switch(type_of(value[1])){
            case BaseTokenType::BTT_NUMBER:
                break;
            case BaseTokenType::BTT_CHAR:
                if(value[1] == 'x'){
                    type = TokenType::TT_NUMBER_HEX;
                    get_id = 2;
                } else if(value[1] == 'b'){
                    type = TokenType::TT_NUMBER_BIN;
                    get_id = 3;
                } else {
                    return TokenType::TT_EMPTY;
                }

                pos++;
                break;
            default:
                return type;
        }

        using get_t = bool(char);
        std::array<get_t*, 4> get = {
            [](char c){ return c >= '0' && c <= '9'; },
            [](char c){ return c >= '0' && c <= '7'; },
            [](char c){ return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); },
            [](char c){ return c == '0' || c == '1'; }
        };

        pos++;
        while(pos < value.length() && get[get_id](value[pos]))
            pos++;

        return type;
    }

    TokenType Lexer::get_identifier(size_t& pos){
        std::string_view value = this->src;
        value = value.substr(this->pos);

        pos = 1;

        while(pos < value.length() && (value[pos] == '_' || std::isalnum(value[pos])))
            pos++;

        std::pair<TokenType, const char*> keywords[] = {
            {TokenType::TT_KW_VAR, "var"},
            {TokenType::TT_KW_CONST, "const"},
            {TokenType::TT_KW_TYPE_U8, "u8"},
            {TokenType::TT_KW_TYPE_U16, "u16"},
            {TokenType::TT_KW_TYPE_U32, "u32"},
            {TokenType::TT_KW_TYPE_U64, "u64"},
            {TokenType::TT_KW_TYPE_U128, "u128"},
            {TokenType::TT_KW_TYPE_USIZE, "usize"},
            {TokenType::TT_KW_TYPE_I8, "i8"},
            {TokenType::TT_KW_TYPE_I16, "i16"},
            {TokenType::TT_KW_TYPE_I32, "i32"},
            {TokenType::TT_KW_TYPE_I64, "i64"},
            {TokenType::TT_KW_TYPE_I128, "i128"},
            {TokenType::TT_KW_TYPE_ISIZE, "isize"},
            {TokenType::TT_KW_TYPE_F32, "f32"},
            {TokenType::TT_KW_TYPE_F64, "f64"},
            {TokenType::TT_KW_TYPE_FSIZE, "fsize"},
            {TokenType::TT_KW_TYPE_SIZE, "size"},
            {TokenType::TT_KW_TYPE_CHAR, "char"},
            {TokenType::TT_KW_TYPE_STR, "str"}
        };

        value = value.substr(0, pos);
        for(auto& kw: keywords){
            if(value == kw.second)
                return kw.first;
        }
        
        return TokenType::TT_IDENTIFIER;
    }
}