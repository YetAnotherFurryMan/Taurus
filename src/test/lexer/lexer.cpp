#include <lexer/lexer.hpp>

#include <iostream>

std::string token_to_string(trs::lexer::TokenType t){
#define TT_CASE(x) case trs::lexer::TokenType::TT_##x: return #x;
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
        TT_CASE(OPERATOR)
        TT_CASE(CHAR)
        TT_CASE(WHITE)
        TT_CASE(SEPARATOR)
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
    }
#undef TT_CASE
    return "TT_ERROR";
}

void print_tokens(trs::lexer::Lexer& lexer, std::string& text){
    lexer.set_source(text);

    trs::lexer::Token token;
    do{
        token = lexer.next();
        std::cout << "[" << token_to_string(token.type);

        if(token.value.has_value())
            std::cout << "=\"" << token.value.value_or("") << "\"";
        
        std::cout << "]" << std::endl;
    } while(token.type != trs::lexer::TokenType::TT_EMPTY && token.type != trs::lexer::TokenType::TT_ERROR);
}

int main(int argc, char** argv){
    std::cout << "Lexer test: " << std::endl;
    std::string texts[] = {
        "var name: u64 = 10",
        "var name: u32 = 012",
        "const name: u16 = 0xa",
        "const name: u8 = 0b1010",
        "var name: u64 = 10;var name: u32 = 012;",
        "const name: u16 = 0xa;const name: u8 = 0b1010;"
    };

    trs::lexer::Lexer lexer;
    for(auto& text: texts)
        print_tokens(lexer, text);
    
    return 0;
}