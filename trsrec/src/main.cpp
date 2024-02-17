#include <cstdio>

#include <trscli.hpp>
#include <trsap.hpp>

#include "program.hpp"

int main(int argc, const char** argv){
    trsrec::Program program;

    int status = program.init(argc, argv);
    if(status){
        program.terminate();
        return status;
    }

    if(program.m_Regex.empty()){
        trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, "No input given.");
        trscli::log(trscli::TRSCLI_LOG_TYPE_INF, "Use -i option.");
        return 1; // TODO: !!! Real errno
    }

    trscli::log(trscli::TRSCLI_LOG_TYPE_INF, std::string("REGEX: ") + std::string(program.m_Regex));
    trscli::log(trscli::TRSCLI_LOG_TYPE_INF, "LANGUAGE: " + std::to_string((int)program.m_Language));

    status = program.load();
    if(status != 0){
        trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, "Bad regex.");
        trscli::log(trscli::TRSCLI_LOG_TYPE_INF, std::string("Got: \'") + program.m_Regex.data() + "\'.");
        program.terminate();
        return status;
    }

    program.m_Token.m_Type = trsre::TRSRE_TOKEN_TYPE_GROUP;
    trsrec::log_token(program.m_Token);

    switch(program.m_Language){
        case trsrec::Language::C:
            status = program.generate_c();
            break;
        case trsrec::Language::CXX:
            status = program.generate_cxx();
            break;
    }

    if(status){
        trscli::log(trscli::TRSCLI_LOG_TYPE_ERR, "Failed to generate the output.");
        program.terminate();
        return status;
    }

    std::string code = program.m_SS.str();

    std::fprintf(program.m_Output, "%s", code.c_str());

    program.terminate();

    return 0;
}

