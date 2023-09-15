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
        TT_CASE(SEPARATOR_HARD)
        TT_CASE(OP_ROUND_BRACKET_L)
        TT_CASE(OP_ROUND_BRACKET_R)
        TT_CASE(OP_SQUARE_BRACKET_L)
        TT_CASE(OP_SQUARE_BRACKET_R)
        TT_CASE(OP_CURLY_BRACKET_L)
        TT_CASE(OP_CURLY_BRACKET_R)
        TT_CASE(OP_ANGLE_BRACKET_L)
        TT_CASE(OP_SMALLER_OR_EQUAL)
        TT_CASE(OP_ANGLE_BRACKET_R)
        TT_CASE(OP_LARGER_OR_EQUAL)
        TT_CASE(OP_COLON)
        TT_CASE(OP_QUESTION_MARK)
        TT_CASE(OP_EXCLAMATION_MARK)
        TT_CASE(OP_NOT_EQUAL)
        TT_CASE(OP_MATH_ADD) 
        TT_CASE(OP_MATH_ADD_EQ)
        TT_CASE(OP_MATH_SUB) 
        TT_CASE(OP_MATH_SUB_EQ)
        TT_CASE(OP_MATH_MUL) 
        TT_CASE(OP_MATH_MUL_EQ)
        TT_CASE(OP_MATH_DIV) 
        TT_CASE(OP_MATH_DIV_EQ)
        TT_CASE(OP_MATH_MOD) 
        TT_CASE(OP_MATH_MOD_EQ)
        TT_CASE(OP_MATH_BIN_AND) 
        TT_CASE(OP_MATH_BIN_AND_EQ)
        TT_CASE(OP_MATH_BIN_OR) 
        TT_CASE(OP_MATH_BIN_OR_EQ)
        TT_CASE(OP_MATH_BIN_XOR) 
        TT_CASE(OP_MATH_BIN_XOR_EQ)
        TT_CASE(OP_MATH_BIN_NOT)
        TT_CASE(OP_MATH_INC)
        TT_CASE(OP_MATH_DEC)
        TT_CASE(OP_EQUALITY)
        TT_CASE(OP_EQUALS)
        TT_CASE(OP_LOGIC_AND_AND)
        TT_CASE(OP_LOGIC_OR_OR)
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

void print_tokens(trs::lexer::Lexer& lexer, std::string& text){
    lexer.set_source(text);

    trs::lexer::Token token;
    do{
        token = lexer.next();
        std::cout << "[" << token_to_string(token.type);

        if(token.value.has_value())
            std::cout << "=\"" << token.value.value_or("") << "\"";
        
        std::cout << "] ";
    } while(token.type != trs::lexer::TokenType::TT_EMPTY && token.type != trs::lexer::TokenType::TT_ERROR);
    std::cout << std::endl;
}

int main(int argc, char** argv){
    std::cout << "Lexer test: " << std::endl;
    std::string texts[] = {
        "var name: u64 = 10",
        "var name: u32 = 012",
        "const name: u16 = 0xa",
        "const name: u8 = 0b1010",
        "var name: u64 = 10;var name: u32 = 012;",
        "const name: u16 = 0xa;const name: u8 = 0b1010;",
        "var name: u64 = 10\nvar name: u32 = 012\n",
        "const name: u16 = 0xa\nconst name: u8 = 0b1010\n",
        "var name: bool = a == b && (c >= d || e != f || g <= h) && (i > j || k < l)",
        "a++; a--;",
        "a += b + c; a -= d - c; a *= e * c; a /= f / c; a %= g % c",
        "a[0] = ~a[1]",
        "a &= b & c; a |= d | c; a ^= e ^ c",
        "a[1] = !a[2]"
    };

    trs::lexer::Lexer lexer;
    for(auto& text: texts)
        print_tokens(lexer, text);
    
    return 0;
}