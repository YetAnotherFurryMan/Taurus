#pragma once

#include <string_view>
#include <vector>
#include <memory>

namespace trs::core{
    //This enum represents the predefined base-types
    enum class StaticType{
        ST_ERROR = -1,
        ST_U8, ST_U16, ST_U32, ST_U64, ST_U128
    };

    //This enum represents the information abound basic (static) operations (e.g. arythmetic etc.)
    enum class StaticOperation{
        SO_ADD, SO_SUB, SO_MUL, SO_DIV, SO_MOD
    };

    //Base structure for all Abstract Syntax Tree structures
    struct AST{
        virtual ~AST() = default;
    };

    //Expression structure for literals like "1"
    struct StaticAST: public AST{
        std::string_view m_Value;
        StaticType m_Type = StaticType::ST_ERROR;
    };

    //Expression structure for referencing a variable, like "var a" or "const a"
    struct VariableAST: public AST{
        std::string_view m_Label;
        std::unique_ptr<StaticAST> m_Value;
        StaticType m_Type = StaticType::ST_ERROR;
        bool m_Mutable = true;

        VariableAST(std::string_view label, std::unique_ptr<StaticAST> value, StaticType type = StaticType::ST_ERROR, bool mutability = true):
            m_Label{label}, 
            m_Value{std::move(value)}, 
            m_Type{type},
            m_Mutable{mutability}
        {}
    };

    //Expression structure for a binary operator, like "a + b"
    struct BinaryAST: public AST{
        StaticOperation m_Operation;
        std::unique_ptr<AST> m_LHS;
        std::unique_ptr<AST> m_RHS;

        BinaryAST(StaticOperation operation, std::unique_ptr<AST> LHS, std::unique_ptr<AST> RHS):
            m_Operation{operation}, 
            m_LHS{std::move(LHS)}, 
            m_RHS{std::move(RHS)}
        {}
    };

    //Expression structure for function calls, like "f()"
    struct CallAST: public AST{
        std::string_view m_Callee;
        std::vector<std::unique_ptr<AST>> m_Arguments;

        CallAST(std::string_view callee, const std::vector<std::unique_ptr<AST>>& arguments):
            m_Callee{callee},
            m_Arguments{std::move(arguments)}
        {}
    };

    //This structure represents the "prototype" for a functions' argument
    struct ArgumentPrototypeAST{
        StaticType m_Type;
        std::optional<std::string_view> m_Label;
        std::optional<std::string_view> m_Value;
    };

    //This structure represents the "prototype" for a function,
    //which captures its label, and its arguments
    struct PrototypeAST{
        std::string_view m_Label;
        std::vector<std::unique_ptr<ArgumentPrototypeAST>> m_Arguments;

        PrototypeAST(std::string_view label, const std::vector<std::unique_ptr<ArgumentPrototypeAST>>& arguments):
            m_Label{label},
            m_Arguments{std::move(arguments)}
        {}
    };

    //This structure represents a function definition itself
    struct FunctionAST{
        std::unique_ptr<PrototypeAST> m_Prototype;
        std::unique_ptr<AST> m_Body;

        FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<AST> body):
            m_Prototype{std::move(prototype)},
            m_Body{std::move(body)}
        {}
    };
}