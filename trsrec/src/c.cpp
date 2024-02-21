#include "c.hpp"

#include "program.hpp"

#include <sstream>

namespace trsrec{
    namespace c{
        /*
         * if($input[$iter] ?= '$c'){
         *     $iter++;
         * } ?expect? else{
         *     goto $label;
         * }
         */
        std::string get_char(char c, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            std::stringstream ss;

            ss << tabs << "if(" << state.m_Input << "[" << state.m_Iter << "] " << (neg?'!':'=') << "= \'" << c << "\'){" << std::endl;
            ss << tabs << "\t" << state.m_Iter << "++;" << std::endl;
            ss << tabs << "}";
            
            if(expect){
                ss << " else{" << std::endl;
                ss << tabs << "\tgoto " << state.m_Label << ";" << std::endl;
                ss << tabs << "}";
            }

            ss << std::endl;
            ss << std::endl;

            return ss.str();
        }

        /*
         * {
         *     ?expect? size_t $my_label = 0;
         *     while($?input[$iter] && $input[$iter] ?= '$c'){
         *         ?expect? $my_label++;
         *         $iter++;
         *     }
         *
         *     ?expect? if(!$my_label){
         *         goto $label;
         *     }
         * }
         */
        std::string get_chars(char c, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            std::stringstream ss;
            ss << tabs << "{" << std::endl;

            if(expect)
                ss << tabs << "\tsize_t " << state.m_Prefix << "_" << state.m_ID << " = 0;" << std::endl;
            
            ss << tabs << "\twhile(" << state.m_Input << "[" << state.m_Iter << "] && " << state.m_Input << "[" << state.m_Iter << "] " << (neg?'!':'=') << "= \'" << c << "\'){" << std::endl;
            
            if(expect)
                ss << tabs << "\t\t" << state.m_Prefix << "_" << state.m_ID << "++;" << std::endl;
            
            ss << tabs << "\t\t" << state.m_Iter << "++;" << std::endl;
            ss << tabs << "\t}" << std::endl;
            ss << std::endl; 

            if(expect){
                ss << tabs << "\tif(!" << state.m_Prefix << "_" << state.m_ID << "){" << std::endl;
                ss << tabs << "\t\tgoto " << state.m_Label << ";" << std::endl;
                ss << tabs << "\t}" << std::endl;
            }
            
            ss << tabs << "}" << std::endl;
            ss << std::endl;

            if(expect)
                state.m_ID++;

            return ss.str();
        }

        /*
         * if(?($my_exp)){
         *     $iter++;
         * } ?expect? else{
         *     goto $label;
         * }
         */
        std::string get_specjal(char c, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            if(neg){
                switch(c){
                    case '.':
                        c = '$';
                        break;
                    case '$':
                        c = '.';
                        break;
                }
            }

            std::stringstream ss;
            ss << tabs << "if(";

            // my_exp
            switch(c){
                case '.':
                    ss << state.m_Input << "[" << state.m_Iter << "]";
                    break;
                case '$':
                    ss << state.m_Input << "[" << state.m_Iter << "] == 0";
                    state.m_Label = state.m_Prefix; // There is no sense continue parsing
                                                    // TODO !!! smthing like matches = $iter;
                    break;
                case 'w':
                    // TODO Not implemented yet...
                    break;
                default:
                    ss << state.m_Input << "[" << state.m_Iter << "] " << (neg?'!':'=') << "= \'\\" << std::to_string(c) << "\'";
            }

            ss << "){" << std::endl;
            ss << tabs << "\t" << state.m_Iter << "++;" << std::endl;
            ss << tabs << "}";

            if(expect){
                ss << " else{" << std::endl;
                ss << tabs << "\tgoto " << state.m_Label << ";" << std::endl;
                ss << tabs << "}";
            }

            ss << std::endl;
            ss << std::endl;

            return ss.str();
        }

        /*
         * {
         *     ?expect? size_t $my_label = 0;
         *     while($?input[$iter] && ?($my_exp)){
         *         ?expect? $my_label++;
         *         $iter++;
         *     }
         *
         *     ?expect? if(!$my_label){
         *         goto $label;
         *     }
         * }
         */
        std::string get_specjals(char c, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            if(neg){
                switch(c){
                    case '.':
                        c = '$';
                        break;
                    case '$':
                        c = '.';
                        break;
                }
            }

            if(c == '$')
                return get_specjal('$', false, expect, state);

            std::stringstream ss;
            ss << tabs << "{" << std::endl;

            if(expect)
                ss << tabs << "\tsize_t " << state.m_Prefix << "_" << state.m_ID << " = 0;" << std::endl;
            
            ss << tabs << "\twhile(" << state.m_Input << "[" << state.m_Iter << "] && ";

            // my_exp
            switch(c){
                case '.':
                    ss << state.m_Input << "[" << state.m_Iter << "]";
                    break;
                case 'w':
                    // TODO Not implemented yet...
                    break;
                default:
                    ss << state.m_Input << "[" << state.m_Iter << "] " << (neg?'!':'=') << "= \'\\" << std::to_string(c) << "\'";
            }

            ss << "){" << std::endl;
            
            if(expect)
                ss << tabs << "\t\t" << state.m_Prefix << "_" << state.m_ID << "++;" << std::endl;
            
            ss << tabs << "\t\t" << state.m_Iter << "++;" << std::endl;
            ss << tabs << "\t}" << std::endl;
            ss << std::endl; 

            if(expect){
                ss << tabs << "\tif(!" << state.m_Prefix << "_" << state.m_ID << "){" << std::endl;
                ss << tabs << "\t\tgoto " << state.m_Label << ";" << std::endl;
                ss << tabs << "\t}" << std::endl;
            }
            
            ss << tabs << "}" << std::endl;
            ss << std::endl;

            if(expect)
                state.m_ID++;

            return ss.str();
        }

        /*
         * if(?($input[$iter] >= '$a' && $input[$iter] <= '$b')){ // !(a >= b && a <= c) = a < b || a > c
         *     $iter++;
         * } ?expect? else{
         *     goto $label;
         * }
         */
        std::string get_range(char a, char b, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            std::stringstream ss;

            ss << tabs << "if(" << state.m_Input << "[" << state.m_Iter << "] " << (neg?"<":">=") << " \'" << a << "\' " << (neg?"|| ":"&& ") << state.m_Input << "[" << state.m_Iter << "] " << (neg?">":"<=") << " \'" << b << "\'){" << std::endl;
            ss << tabs << "\t" << state.m_Iter << "++;" << std::endl;
            ss << tabs << "}";

            if(expect){
                ss << " else{" << std::endl;
                ss << tabs << "\tgoto " << state.m_Label << ";" << std::endl;
                ss << tabs << "}";
            }

            ss << std::endl;
            ss << std::endl;

            return ss.str();
        }

        /*
         * {
         *     ?expect? size_t $my_label = 0;
         *     while($?input[$iter] && ?($input[$iter] >= '$a' && $input[$iter] <= '$b')){
         *         ?expect? $my_label++;
         *         $iter++;
         *     }
         *
         *     ?expect? if(!$my_label){
         *         goto $label;
         *     }
         * }
         */
        std::string get_ranges(char a, char b, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            std::stringstream ss;
            ss << tabs << "{" << std::endl;

            if(expect)
                ss << tabs << "\tsize_t " << state.m_Prefix << "_" << state.m_ID << " = 0;" << std::endl;
            
            ss << tabs << "\twhile(" << state.m_Input << "[" << state.m_Iter << "] && " << (neg?"!":"") << "(" << state.m_Input << "[" << state.m_Iter << "] >= \'" << a << "\' && " << state.m_Input << "[" << state.m_Iter << "] <= \'" << b << "\')){" << std::endl;
            
            if(expect)
                ss << tabs << "\t\t" << state.m_Prefix << "_" << state.m_ID << "++;" << std::endl;
            
            ss << tabs << "\t\t" << state.m_Iter << "++;" << std::endl;
            ss << tabs << "\t}" << std::endl;
            ss << std::endl;

            if(expect){
                ss << tabs << "\tif(!" << state.m_Prefix << "_" << state.m_ID << "){" << std::endl;
                ss << tabs << "\t\tgoto " << state.m_Label << ";" << std::endl;
                ss << tabs << "\t}" << std::endl;
            }

            ss << tabs << "}" << std::endl;
            ss << std::endl;

            if(expect)
                state.m_ID++;

            return ss.str();
        }

        /*
         * switch($input[$iter]){
         *     case '$c':
         *     case '$a' ... '$b':
         *         $iter++;        // <-+
         *         break;          //   |
         *     default:            //   +- swap ?
         *         goto $labal;    // <-+  -- ?expect?
         * }
         */
        std::string get_choose(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            std::stringstream ss;

            ss << tabs << "switch(" << state.m_Input << "[" << state.m_Iter << "]){" << std::endl;
            
            for(auto& tok: body){
                const char* val = tok.m_Value.c_str();
                if(tok.m_Type == trsre::TRSRE_TOKEN_TYPE_LITERAL){
                    ss << tabs << "\tcase \'" << Program::get_lit(&val) << "\':" << std::endl;
                } else if(tok.m_Type == trsre::TRSRE_TOKEN_TYPE_RANGE){
                    char a = Program::get_lit(&val);
                    val++;
                    char b = Program::get_lit(&val);
                    ss << tabs << "\tcase \'" << a << "\' ... \'" << b << "\':" << std::endl;
                }
            }

            if(neg && expect){
                ss << tabs << "\t\tgoto " << state.m_Label << ";" << std::endl;
            } else if(!neg){ 
                ss << tabs << "\t\t" << state.m_Iter << "++;" << std::endl;
            }

            ss << tabs << "\t\tbreak;" << std::endl;

            if(neg){
                ss << tabs << "\tdefault:" << std::endl;
                ss << tabs << "\t\t" << state.m_Iter << "++;" << std::endl;
            } else if(expect){
                ss << tabs << "\tdefault:" << std::endl;
                ss << tabs << "\t\tgoto " << state.m_Label << ";" << std::endl;
            }
            
            ss << tabs << "}" << std::endl;
            ss << std::endl;

            return ss.str();
        }

        /*
         * {
         *     size_t $my_label1 = $iter;
         *     $my_label2:
         *     switch($input[$iter]){
         *         case '$c':
         *         case '$a' ... '$b':
         *             $iter++;         // <-+
         *             $my_label1++;    // <-+
         *             goto $my_label2; // <-+
         *             break;           //   |
         *         default:             //   +- swap ?
         *             if(!$my_label1)  // <-+  -- ?expect?
         *                 goto $labal; // <-+  -- ?expect?
         *     }
         * }
         */
        std::string get_chooses(const std::vector<trsre::Token>& body, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            auto id1 = state.m_ID++;
            auto id2 = state.m_ID++;

            std::stringstream ss;

            ss << tabs << "{" << std::endl;
            ss << tabs << "\tsize_t " << state.m_Prefix << "_" << id1 << " = 0;" << std::endl;
            ss << tabs << "\t" << state.m_Prefix << "_" << id2 << ":" << std::endl;
            ss << tabs << "\tswitch(" << state.m_Input << "[" << state.m_Iter << "]){" << std::endl;
            
            for(auto& tok: body){
                const char* val = tok.m_Value.c_str();
                if(tok.m_Type == trsre::TRSRE_TOKEN_TYPE_LITERAL){
                    ss << tabs << "\t\tcase \'" << Program::get_lit(&val) << "\':" << std::endl;
                } else if(tok.m_Type == trsre::TRSRE_TOKEN_TYPE_RANGE){
                    char a = Program::get_lit(&val);
                    val++;
                    char b = Program::get_lit(&val);
                    ss << tabs << "\t\tcase \'" << a << "\' ... \'" << b << "\':" << std::endl;
                }
            }

            if(neg && expect){
                ss << tabs << "\t\t\tif(!" << state.m_Prefix << "_" << id1 << ")" << std::endl;
                ss << tabs << "\t\t\t\tgoto " << state.m_Label << ";" << std::endl;
            } else if(!neg){
                ss << tabs << "\t\t\t" << state.m_Iter << "++;" << std::endl;
                ss << tabs << "\t\t\t" << state.m_Prefix << "_" << id1 << "++;" << std::endl;
                ss << tabs << "\t\t\tgoto " << state.m_Prefix << "_" << id2 << ";" << std::endl;
            }

            ss << tabs << "\t\t\tbreak;" << std::endl;

            if(neg){
                ss << tabs << "\t\tdefault:" << std::endl;
                ss << tabs << "\t\t\t" << state.m_Iter << "++;" << std::endl;
                ss << tabs << "\t\t\t" << state.m_Prefix << "_" << id1 << "++;" << std::endl;
                ss << tabs << "\t\t\tgoto " << state.m_Prefix << "_" << id2 << ";" << std::endl;
            } else if(expect){
                ss << tabs << "\t\tdefault:" << std::endl;
                ss << tabs << "\t\t\tif(!" << state.m_Prefix << "_" << id1 << ")" << std::endl;
                ss << tabs << "\t\t\t\tgoto " << state.m_Label << ";" << std::endl;
            }
            
            ss << tabs << "\t}" << std::endl;
            ss << tabs << "}" << std::endl;
            ss << std::endl;

            return ss.str();
        }

        /*
         * {
         *    size_t $my_label1 = $iter;
         *    ...
         *    $iter = $my_label1;
         *    ?expect? $my_label2:
         * }
         */
        std::string get_group(const std::vector<trsre::Token>& body, bool n, bool e, State& s){
            std::string tabs = std::string(s.m_Depth, '\t');
            
            size_t id1 = s.m_ID++;

            std::string iter_label = s.m_Prefix.data();
            iter_label += "_";
            iter_label += std::to_string(id1);

            std::string end_label = s.m_Label.data();
            if(!e){
                size_t id2 = s.m_ID++;
                end_label = s.m_Prefix;
                end_label += "_";
                end_label += std::to_string(id2);
            }

            std::stringstream ss;

            ss << tabs << "{" << std::endl;
            ss << tabs << "\tsize_t " << iter_label << " = " << s.m_Iter << ";" << std::endl;

            // ...
            State state = {
                s.m_Input,
                iter_label,
                s.m_Prefix,
                end_label,
                s.m_ID,
                s.m_Depth + 1
            };
            
            for(auto& tok: body){
                ss << tabs << "\t// " << tok.m_Value << std::endl;
                trsre::TokenMode mod = (trsre::TokenMode)(tok.m_Mode);
                
                bool neg = (mod & trsre::TRSRE_TOKEN_MODE_NOT);
                
                if(n)
                    neg = !neg;
                
                mod = trsre::TokenMode(mod & ~trsre::TRSRE_TOKEN_MODE_NOT);
                
                bool expect = mod == trsre::TRSRE_TOKEN_MODE_SINGLE || mod == trsre::TRSRE_TOKEN_MODE_PLUS;
                bool loop = mod == trsre::TRSRE_TOKEN_MODE_STAR || mod == trsre::TRSRE_TOKEN_MODE_PLUS;
                
                switch(tok.m_Type){
                    case trsre::TRSRE_TOKEN_TYPE_EMPTY:
                        return ""; // Should be unreachable 
                    case trsre::TRSRE_TOKEN_TYPE_LITERAL: {
                        const char* value = tok.m_Value.c_str();
                        char c = Program::get_lit(&value);
                        
                        if(loop)
                            ss << c::get_chars(c, neg, expect, state);
                        else
                            ss << c::get_char(c, neg, expect, state);
                    } break;
                    case trsre::TRSRE_TOKEN_TYPE_ANY:
                    case trsre::TRSRE_TOKEN_TYPE_EOE: {
                        if(loop)
                            ss << c::get_specjals(tok.m_Value[0], neg, expect, state);
                        else
                            ss << c::get_specjal(tok.m_Value[0], neg, expect, state);
                    } break;
                    case trsre::TRSRE_TOKEN_TYPE_RANGE: {
                        const char* value = tok.m_Value.c_str();
                        char a = Program::get_lit(&value);
                        value++;
                        char b = Program::get_lit(&value);

                        if(loop)
                            ss << c::get_ranges(a, b, neg, expect, state);
                        else
                            ss << c::get_range(a, b, neg, expect, state);
                    } break;
                    case trsre::TRSRE_TOKEN_TYPE_CHOOSE: {
                        if(loop)
                            ss << c::get_chooses(tok.m_Body, neg, expect, state);
                        else
                            ss << c::get_choose(tok.m_Body, neg, expect, state);
                    } break;
                    case trsre::TRSRE_TOKEN_TYPE_GROUP: {
                        if(loop)
                            ss << c::get_groups(tok.m_Body, neg, expect, state);
                        else
                            ss << c::get_group(tok.m_Body, neg, expect, state);
                    } break;
                }
            }

            s.m_ID = state.m_ID;

            ss << tabs << "\t" << s.m_Iter << " = " << iter_label << ";" << std::endl;

            if(!e){
                ss << tabs << "\t" << end_label << ":" << std::endl;
            }

            ss << tabs << "}" << std::endl;
            ss << std::endl;

            return ss.str();
        }

        /*
         * {
         *    size_t $my_label1 = $iter;
         *    $my_label3:
         *    ...
         *    $iter = $my_label1;
         *    goto $my_label3;
         *    $my_label2:
         *    ?expect? if($my_label1 - $iter <= 0){
         *        goto $label;
         *    }
         * }
         */
        std::string get_groups(const std::vector<trsre::Token>& body, bool n, bool e, State& s){
            std::string tabs = std::string(s.m_Depth, '\t');
            
            size_t id1 = s.m_ID++;
            size_t id2 = s.m_ID++;
            size_t id3 = s.m_ID++;

            std::string iter_label = s.m_Prefix.data();
            iter_label += "_";
            iter_label += std::to_string(id1);

            std::string end_label = s.m_Prefix.data();
            end_label += "_";
            end_label += std::to_string(id2);

            std::stringstream ss;

            ss << tabs << "{" << std::endl;
            ss << tabs << "\tsize_t " << iter_label << " = " << s.m_Iter << ";" << std::endl;
            ss << tabs << "\t" << s.m_Prefix << "_" << id3 << ":" << std::endl;

            // ...
            State state = {
                s.m_Input,
                iter_label,
                s.m_Prefix,
                end_label,
                s.m_ID,
                s.m_Depth + 1
            };
            
            for(auto& tok: body){
                ss << tabs << "\t// " << tok.m_Value << std::endl;
                trsre::TokenMode mod = (trsre::TokenMode)(tok.m_Mode);

                bool neg = (mod & trsre::TRSRE_TOKEN_MODE_NOT);

                if(n)
                    neg = !neg;

                mod = trsre::TokenMode(mod & ~trsre::TRSRE_TOKEN_MODE_NOT);
                bool expect = mod == trsre::TRSRE_TOKEN_MODE_SINGLE || mod == trsre::TRSRE_TOKEN_MODE_PLUS;
                bool loop = mod == trsre::TRSRE_TOKEN_MODE_STAR || mod == trsre::TRSRE_TOKEN_MODE_PLUS;
                
                switch(tok.m_Type){
                    case trsre::TRSRE_TOKEN_TYPE_EMPTY:
                        return ""; // Should be unreachable 
                    case trsre::TRSRE_TOKEN_TYPE_LITERAL: {
                        const char* value = tok.m_Value.c_str();
                        char c = Program::get_lit(&value);
                         
                        if(loop)
                            ss << c::get_chars(c, neg, expect, state);
                        else
                            ss << c::get_char(c, neg, expect, state);
                    } break;
                    case trsre::TRSRE_TOKEN_TYPE_ANY:
                    case trsre::TRSRE_TOKEN_TYPE_EOE: {
                        if(loop)
                            ss << c::get_specjals(tok.m_Value[0], neg, expect, state);
                        else
                            ss << c::get_specjal(tok.m_Value[0], neg, expect, state);
                    } break;
                    case trsre::TRSRE_TOKEN_TYPE_RANGE: {
                        const char* value = tok.m_Value.c_str();
                        char a = Program::get_lit(&value);
                        value++;
                        char b = Program::get_lit(&value);

                        if(loop)
                            ss << c::get_ranges(a, b, neg, expect, state);
                        else
                            ss << c::get_range(a, b, neg, expect, state);
                    } break;
                    case trsre::TRSRE_TOKEN_TYPE_CHOOSE: {
                        if(loop)
                            ss << c::get_chooses(tok.m_Body, neg, expect, state);
                        else
                            ss << c::get_choose(tok.m_Body, neg, expect, state);
                    } break;
                    case trsre::TRSRE_TOKEN_TYPE_GROUP: {
                        if(loop)
                            ss << c::get_groups(tok.m_Body, neg, expect, state);
                        else
                            ss << c::get_group(tok.m_Body, neg, expect, state);
                    } break;
                }
            }
            s.m_ID = state.m_ID;

            ss << tabs << "\t" << s.m_Iter << " = " << iter_label << ";" << std::endl;
            ss << tabs << "\tgoto " << s.m_Prefix << "_" << id3 << ";" << std::endl; 
            ss << tabs << "\t" << end_label << ":" << std::endl;

            if(e){
                ss << tabs << "\tif(" << iter_label << " - " << s.m_Iter << " <= 0){" << std::endl;
                ss << tabs << "\t\tgoto " << s.m_Label << ";" << std::endl;
                ss << tabs << "\t}" << std::endl;
            }
            ss << tabs << "}" << std::endl;
            ss << std::endl;

            return ss.str();
        }
    }
}

