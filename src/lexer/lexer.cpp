#include "headers/lexer.hpp"

namespace trs::lexer{
    void Lexer::set_source(std::istream& src){
        this->begin = 0;
        this->pos = 0;
        this->src = src;
    }

    void Lexer::reset(){
        this->begin = 0;
        this->pos = 0;
    }

    Token Lexer::next(){
        return {};
    }
}