#include <trsap.hpp>
#include <trscli.hpp>

#include "program.hpp"

#include <cstdio>

namespace trsrec {
    int Program::init(int argc, const char** argv){
        this->m_Program = trsap::chop(&argc, &argv);

        trsap::ArgDesc descriptions[] = {
            {'i', "input", trsap::TRSAP_ARG_VALUE_TYPE_EXPECT},
            {'o', "output", trsap::TRSAP_ARG_VALUE_TYPE_EXPECT},
            {'l', "language", trsap::TRSAP_ARG_VALUE_TYPE_EXPECT},
            {'e', "label", trsap::TRSAP_ARG_VALUE_TYPE_EXPECT},
            {0, 0, trsap::TRSAP_ARG_VALUE_TYPE_ERROR}
        };

        auto args = trsap::getAll(argc, argv, descriptions);
        for(auto &arg : args){
            if(arg.m_Error){
                switch(arg.m_Error){
                    case 1:
                        trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, std::string("Excepted ") + descriptions[arg.m_ID - 1].m_Long + " after \'" + arg.m_Tag + "\'");
                    break;
                    case 2:
                        trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, std::string("Unknown argument \'") + arg.m_Tag + "\'");
                    break;
                    default:
                        trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, "Unknown error while validating argument's list.");
                        trscli::log(trscli::TRSCLI_LOG_TYPE_INF, std::string("With NO ") + std::to_string(arg.m_Error));
                        trscli::log(trscli::TRSCLI_LOG_TYPE_INF, std::string("With tag \'") + arg.m_Tag + "\'");
                        trscli::log(trscli::TRSCLI_LOG_TYPE_INF, std::string("With ID ") + std::to_string(arg.m_ID));
                }

                return arg.m_Error;
            }

            if(arg.m_ID == 0){
                trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, "This program does not support bare arguments.");
                trscli::log(trscli::TRSCLI_LOG_TYPE_INF, std::string("On \'") + arg.m_Value + "\'");
                return 22; // EINVAL
            }

            switch(descriptions[arg.m_ID - 1].m_Short){
                case 'i': {
                    if(!this->m_Regex.empty()){
                        trscli::log(trscli::TRSCLI_LOG_TYPE_WAR, "Input already provided. Ignored.");
                        break;
                    }

                    this->m_Regex = arg.m_Value;
                } break;
                case 'o': {
                    if(this->m_Output != stdout){
                        trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, "Multiple output streams are not supported.");
                        return 22; // EINVAL 
                    }

                    FILE* out = std::fopen(arg.m_Value, "w");
                    if(!out){
                        trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, "Failed to open output file.");
                        trscli::log(trscli::TRSCLI_LOG_TYPE_INF, std::string("Path: \'") + arg.m_Value + "\'");
                        return errno;
                    }
                    this->m_Output = out;
                } break;
                case 'l': {
                    if(std::strcmp("C", arg.m_Value) == 0){
                        this->m_Language = Language::C;
                    } else if(std::strcmp("CXX", arg.m_Value) == 0){
                        this->m_Language = Language::CXX;
                    } else{
                        trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, std::string("Unsupported language \'") + arg.m_Value + "\'.");
                        return 22; // EINVAL
                    }
                } break;
                case 'e': {
                    this->m_Label = arg.m_Value;
                } break;
                default:
                    trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, "Unknown error while validating argument's list.");
                    trscli::log(trscli::TRSCLI_LOG_TYPE_INF, std::string("With tag \'") + arg.m_Tag + "\'");
                    trscli::log(trscli::TRSCLI_LOG_TYPE_INF, std::string("With ID ") + std::to_string(arg.m_ID));
                    return 22; // EINVAL
            }
        }

        return 0;
    }
} // namespace trsrec
