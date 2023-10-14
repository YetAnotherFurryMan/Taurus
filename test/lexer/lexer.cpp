#include <core/lexer.hpp>

#include <iostream>
#include <vector>

std::vector<std::pair<std::string, std::vector<trs::core::Token>>> testware = {
    {
        "var name: u64 = 10", 
        {
            {trs::core::TokenType::TT_KW_VAR},
            {trs::core::TokenType::TT_IDENTIFIER, "name"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U64},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_DEC, "10"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "var name: u32 = 012", 
        {
            {trs::core::TokenType::TT_KW_VAR},
            {trs::core::TokenType::TT_IDENTIFIER, "name"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U32},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_OCT, "012"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "const name: u16 = 0xa", 
        {
            {trs::core::TokenType::TT_KW_CONST},
            {trs::core::TokenType::TT_IDENTIFIER, "name"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U16},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_HEX, "0xa"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "const name: u8 = 0b1010", 
        {
            {trs::core::TokenType::TT_KW_CONST},
            {trs::core::TokenType::TT_IDENTIFIER, "name"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U8},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_BIN, "0b1010"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "var a: u64 = 10;var b: u32 = 012;", 
        {
            {trs::core::TokenType::TT_KW_VAR},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U64},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_DEC, "10"},
            {trs::core::TokenType::TT_SEPARATOR, ";"},
            {trs::core::TokenType::TT_KW_VAR},
            {trs::core::TokenType::TT_IDENTIFIER, "b"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U32},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_OCT, "012"},
            {trs::core::TokenType::TT_SEPARATOR, ";"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "const c: u16 = 0xa;const d: u8 = 0b1010;", 
        {
            {trs::core::TokenType::TT_KW_CONST},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U16},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_HEX, "0xa"},
            {trs::core::TokenType::TT_SEPARATOR, ";"},
            {trs::core::TokenType::TT_KW_CONST},
            {trs::core::TokenType::TT_IDENTIFIER, "d"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U8},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_BIN, "0b1010"},
            {trs::core::TokenType::TT_SEPARATOR, ";"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "var a: u64 = 10\nvar b: u32 = 012\n", 
        {
            {trs::core::TokenType::TT_KW_VAR},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U64},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_DEC, "10"},
            {trs::core::TokenType::TT_SEPARATOR, "\n"},
            {trs::core::TokenType::TT_KW_VAR},
            {trs::core::TokenType::TT_IDENTIFIER, "b"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U32},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_OCT, "012"},
            {trs::core::TokenType::TT_SEPARATOR, "\n"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "const c: u16 = 0xa\nconst d: u8 = 0b1010\n", 
        {
            {trs::core::TokenType::TT_KW_CONST},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U16},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_HEX, "0xa"},
            {trs::core::TokenType::TT_SEPARATOR, "\n"},
            {trs::core::TokenType::TT_KW_CONST},
            {trs::core::TokenType::TT_IDENTIFIER, "d"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_U8},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_NUMBER_BIN, "0b1010"},
            {trs::core::TokenType::TT_SEPARATOR, "\n"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "var math: bool = a == b && (c >= d || e != f || g <= h) && (i > j || k < l)", 
        {
            {trs::core::TokenType::TT_KW_VAR},
            {trs::core::TokenType::TT_IDENTIFIER, "math"},
            {trs::core::TokenType::TT_OPERATOR, ":"},
            {trs::core::TokenType::TT_KW_TYPE_BOOL},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "b"},
            {trs::core::TokenType::TT_OPERATOR, "&"},
            {trs::core::TokenType::TT_OPERATOR, "&"},
            {trs::core::TokenType::TT_OPERATOR, "("},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_OPERATOR, ">"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "d"},
            {trs::core::TokenType::TT_OPERATOR, "|"},
            {trs::core::TokenType::TT_OPERATOR, "|"},
            {trs::core::TokenType::TT_IDENTIFIER, "e"},
            {trs::core::TokenType::TT_OPERATOR, "!"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "f"},
            {trs::core::TokenType::TT_OPERATOR, "|"},
            {trs::core::TokenType::TT_OPERATOR, "|"},
            {trs::core::TokenType::TT_IDENTIFIER, "g"},
            {trs::core::TokenType::TT_OPERATOR, "<"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "h"},
            {trs::core::TokenType::TT_OPERATOR, ")"},
            {trs::core::TokenType::TT_OPERATOR, "&"},
            {trs::core::TokenType::TT_OPERATOR, "&"},
            {trs::core::TokenType::TT_OPERATOR, "("},
            {trs::core::TokenType::TT_IDENTIFIER, "i"},
            {trs::core::TokenType::TT_OPERATOR, ">"},
            {trs::core::TokenType::TT_IDENTIFIER, "j"},
            {trs::core::TokenType::TT_OPERATOR, "|"},
            {trs::core::TokenType::TT_OPERATOR, "|"},
            {trs::core::TokenType::TT_IDENTIFIER, "k"},
            {trs::core::TokenType::TT_OPERATOR, "<"},
            {trs::core::TokenType::TT_IDENTIFIER, "l"},
            {trs::core::TokenType::TT_OPERATOR, ")"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "a++; a--;", 
        {
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "+"},
            {trs::core::TokenType::TT_OPERATOR, "+"},
            {trs::core::TokenType::TT_SEPARATOR, ";"},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "-"},
            {trs::core::TokenType::TT_OPERATOR, "-"},
            {trs::core::TokenType::TT_SEPARATOR, ";"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "a += b + c; a -= d - c\n a *= e * c; a /= f / c\n a %= g % c", 
        {
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "+"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "b"},
            {trs::core::TokenType::TT_OPERATOR, "+"},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_SEPARATOR, ";"},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "-"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "d"},
            {trs::core::TokenType::TT_OPERATOR, "-"},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_SEPARATOR, "\n"},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "*"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "e"},
            {trs::core::TokenType::TT_OPERATOR, "*"},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_SEPARATOR, ";"},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "/"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "f"},
            {trs::core::TokenType::TT_OPERATOR, "/"},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_SEPARATOR, "\n"},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "%"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "g"},
            {trs::core::TokenType::TT_OPERATOR, "%"},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "a[0] = ~a[1]", 
        {
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "["},
            {trs::core::TokenType::TT_NUMBER_DEC, "0"},
            {trs::core::TokenType::TT_OPERATOR, "]"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_OPERATOR, "~"},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "["},
            {trs::core::TokenType::TT_NUMBER_DEC, "1"},
            {trs::core::TokenType::TT_OPERATOR, "]"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "a &= b & c; a |= d | c\n a ^= e ^ c", 
        {
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "&"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "b"},
            {trs::core::TokenType::TT_OPERATOR, "&"},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_SEPARATOR, ";"},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "|"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "d"},
            {trs::core::TokenType::TT_OPERATOR, "|"},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_SEPARATOR, "\n"},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "^"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_IDENTIFIER, "e"},
            {trs::core::TokenType::TT_OPERATOR, "^"},
            {trs::core::TokenType::TT_IDENTIFIER, "c"},
            {trs::core::TokenType::TT_EMPTY}
        }
    },
    {
        "a[1] = !a[2]", 
        {
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "["},
            {trs::core::TokenType::TT_NUMBER_DEC, "1"},
            {trs::core::TokenType::TT_OPERATOR, "]"},
            {trs::core::TokenType::TT_OPERATOR, "="},
            {trs::core::TokenType::TT_OPERATOR, "!"},
            {trs::core::TokenType::TT_IDENTIFIER, "a"},
            {trs::core::TokenType::TT_OPERATOR, "["},
            {trs::core::TokenType::TT_NUMBER_DEC, "2"},
            {trs::core::TokenType::TT_OPERATOR, "]"},
            {trs::core::TokenType::TT_EMPTY}
        }
    }
};

std::string token_to_string(trs::core::TokenType t){
#define TT_CASE(x) case trs::core::TokenType::TT_##x: return #x;
    switch(t){
        TT_CASE(EMPTY)
        TT_CASE(IDENTIFIER)
        TT_CASE(STRING)
        TT_CASE(NUMBER)
        TT_CASE(NUMBER_DEC)
        TT_CASE(NUMBER_OCT)
        TT_CASE(NUMBER_HEX)
        TT_CASE(NUMBER_BIN)
        TT_CASE(FLOAT)
        TT_CASE(CHAR)
        TT_CASE(WHITE)
        TT_CASE(SEPARATOR)
        TT_CASE(OPERATOR)
        TT_CASE(KW_VAR)
        TT_CASE(KW_CONST)
        TT_CASE(KW_TYPE_U8)
        TT_CASE(KW_TYPE_U16)
        TT_CASE(KW_TYPE_U32)
        TT_CASE(KW_TYPE_U64)
        TT_CASE(KW_TYPE_U128)
        TT_CASE(KW_TYPE_USIZE)
        TT_CASE(KW_TYPE_I8)
        TT_CASE(KW_TYPE_I16)
        TT_CASE(KW_TYPE_I32)
        TT_CASE(KW_TYPE_I64)
        TT_CASE(KW_TYPE_I128)
        TT_CASE(KW_TYPE_ISIZE)
        TT_CASE(KW_TYPE_F32)
        TT_CASE(KW_TYPE_F64)
        TT_CASE(KW_TYPE_FSIZE)
        TT_CASE(KW_TYPE_SIZE) 
        TT_CASE(KW_TYPE_CHAR)
        TT_CASE(KW_TYPE_STR)
        TT_CASE(KW_TYPE_BOOL)
    }
#undef TT_CASE
    return "TT_ERROR";
}

void print_tokens(trs::core::Lexer& lexer){
    trs::core::Token token;
    do{
        token = lexer.next();
        std::cout << "[" << token_to_string(token.m_Type);

        if(token.m_Value.has_value())
            std::cout << "=\"" << token.m_Value.value_or("") << "\"";
        
        std::cout << "] ";
    } while(token.m_Type != trs::core::TokenType::TT_EMPTY && token.m_Type != trs::core::TokenType::TT_ERROR);
    std::cout << std::endl;
}

bool validate(trs::core::Lexer& lexer, const std::vector<trs::core::Token>& data){
    trs::core::Token token;
    size_t i = 0;

    do{
        token = lexer.next();

        if(token.m_Type == trs::core::TokenType::TT_ERROR || i >= data.size())
            return false;
        
        if(token != data[i])
            return false;

        i++;
    } while(token.m_Type != trs::core::TokenType::TT_EMPTY);

    return true;
}

int main(int argc, char** argv){
    std::cout << "Lexer test: " << std::endl;

    trs::core::Lexer lexer;
    size_t passed = 0;
    for(auto& e: testware){
        lexer.set_source(e.first);

        if(!validate(lexer, e.second)){
            lexer.reset();
            std::cout << "Failed: ";
            print_tokens(lexer);
            continue;
        }

        passed++;
    }

    std::cout << passed << "/" << testware.size() << std::endl;
    
    return 0;
}