#pragma once

//See https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl02.html

#include <memory>

#include "core.hpp"
#include "lexer.hpp"

namespace trs::core{
    //Parser class
    class Parser{
    public:
        //Deleted constructors
        Parser(const Parser&) = delete;
        Parser(const Parser&&) = delete;

        //Constructor
        Parser(std::unique_ptr<Lexer> lexer):
            m_Lexer{std::move(lexer)}
        {}

        //Returns next expression
        std::unique_ptr<AST> next();
    private:
        Token m_CurrentToken;
        std::unique_ptr<Lexer> m_Lexer;

        //Moving lexer and current token
        void step();

        //Returns static expression or nullptr
        std::unique_ptr<AST> parse_number();

        // paren ::= '(' expression ')'
        std::unique_ptr<AST> parse_paren();

        // idexp ::= identifier | identifier '(' expression* ')'
        std::unique_ptr<AST> parse_identifier();

        // primary ::= idexp | value | paren
        std::unique_ptr<AST> parse_primary();

        // binRHS ::= ( op idexp )*
        std::unique_ptr<AST> parse_binaryRHS(std::unique_ptr<AST>);
        std::unique_ptr<AST> parse_expresion();
        std::unique_ptr<PrototypeAST> parse_prototype();
        std::unique_ptr<FunctionAST> parse_definition();
        std::unique_ptr<FunctionAST> parse_top_level();
        std::unique_ptr<PrototypeAST> parse_extern();
    };
}