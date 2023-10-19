#include <core/parser.hpp>

namespace trs::core{
    void Parser::step(){
        this->m_CurrentToken = m_Lexer.get()->next();
    }

    std::unique_ptr<AST> Parser::parse_number(){
        if(m_CurrentToken.m_Type == TokenType::TT_NUMBER
            || m_CurrentToken.m_Type == TokenType::TT_NUMBER_BIN
            || m_CurrentToken.m_Type == TokenType::TT_NUMBER_DEC
            || m_CurrentToken.m_Type == TokenType::TT_NUMBER_HEX
            || m_CurrentToken.m_Type == TokenType::TT_NUMBER_OCT
        ){
            //!TODO:
            //Validate value
            //Precise type
            auto result = std::make_unique<StaticAST>(m_CurrentToken.m_Value, StaticType::ST_U64);
            step();
            return std::move(result);
        }

        return nullptr;
    }

    std::unique_ptr<AST> Parser::parse_paren(){
        if(m_CurrentToken != Token(TokenType::TT_OPERATOR, "("))
            return nullptr;
        
        step(); //Eat (
        
        auto result = parse_expresion();
        if(!result)
            return nullptr;
        
        step(); //Eat expression

        if(m_CurrentToken != Token(TokenType::TT_OPERATOR, ")"))
            return nullptr;
        
        step(); //Eat )

        return std::move(result);
    }

    std::unique_ptr<AST> Parser::parse_identifier(){
        if(m_CurrentToken.m_Type != TokenType::TT_IDENTIFIER)
            return nullptr;
        
        auto id = m_CurrentToken.m_Value;

        step(); //Eat identifier

        if(m_CurrentToken == Token(TokenType::TT_OPERATOR, "(")){
            step(); //Eat (
            
            std::vector<std::unique_ptr<AST>> args;
            while(m_CurrentToken != Token(TokenType::TT_OPERATOR, ")")){
                if(auto arg = parse_expresion())
                    args.push_back(arg);
                else
                    return nullptr;
                
                step(); //Eat arg

                if(m_CurrentToken == Token(TokenType::TT_OPERATOR, ","))
                    step(); //Eat ,
            }

            step(); //Eat )

            return std::make_unique<CallAST>(id, args);
        }

        return std::make_unique<VariableAST>(id);
    }

    std::unique_ptr<AST> Parser::parse_primary(){
        switch(m_CurrentToken.m_Type){
            case TokenType::TT_IDENTIFIER:
                return parse_identifier();
            case TokenType::TT_NUMBER:
            case TokenType::TT_NUMBER_BIN:
            case TokenType::TT_NUMBER_DEC:
            case TokenType::TT_NUMBER_HEX:
            case TokenType::TT_NUMBER_OCT:
                return parse_number();
            case TokenType::TT_OPERATOR:
                return parse_paren();
        }
    }

    std::unique_ptr<AST> Parser::parse_binaryRHS(std::unique_ptr<AST>){
        //
    }

    std::unique_ptr<AST> Parser::parse_expresion(){
        //
    }

    std::unique_ptr<PrototypeAST> Parser::parse_prototype(){
        //
    }

    std::unique_ptr<FunctionAST> Parser::parse_definition(){
        //
    }

    std::unique_ptr<FunctionAST> Parser::parse_top_level(){
        //
    }

    std::unique_ptr<PrototypeAST> Parser::parse_extern(){
        //
    }

}