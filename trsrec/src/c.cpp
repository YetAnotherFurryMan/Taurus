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
         *     size_t $my_label = 0;
         *     while($?input[$iter] && $input[$iter] ?= '$c'){
         *         $my_label++;
         *         $iter++;
         *     }
         *
         * ?expect? if(!$my_label){
         *         goto $label;
         *     }
         * }
         */
        std::string get_chars(char c, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            std::stringstream ss;
            ss << tabs << "{" << std::endl;
            ss << tabs << "\tsize_t " << state.m_Prefix << "_" << state.m_ID << " = 0;" << std::endl;
            ss << tabs << "\twhile(" << state.m_Input << "[" << state.m_Iter << "] && " << state.m_Input << "[" << state.m_Iter << "] " << (neg?'!':'=') << "= \'" << c << "\'){" << std::endl;
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

            state.m_ID++;

            return ss.str();
        }

        /*
         * if($input[$iter] ?= 0){
         *     $iter++;
         * } else{
         *     goto $label;
         * }
         */
        std::string expect_any(char c, bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth){
            std::string tabs = std::string(depth, '\t');

            std::stringstream ss;

            ss << tabs << "if(" << input << "[" << iter << "] " << (neg?'=':'!') << "= 0){" << std::endl;
            ss << tabs << "\t" << iter << "++;" << std::endl;
            ss << tabs << "} else{" << std::endl;
            ss << tabs << "\tgoto " << label << ";" << std::endl;
            ss << tabs << "}" << std::endl;
            ss << std::endl;

            return ss.str();
        }

        /*
         * {   // if(neg) expect_eoe
         *     size_t $my_label = $iter;
         *     while($input[$my_label]){
         *         $my_label++;
         *     }
         *
         *     if($my_label - $iter <= 0){
         *         goto $label;
         *     }
         * }
         */
        std::string expect_anys(char c, bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth, std::string_view prefix, size_t* id){
            return "//TODO";
        }

        /*
         * if($input[$iter] ?= 0){
         *     $iter++;
         * }
         */
        std::string get_any(char c, bool neg, std::string_view input, std::string_view iter, size_t depth){
            return "//TODO";
        }

        /*
         * // if(neg) get_eoe
         * while($input[$iter]){
         *     $iter++;
         * }
         */
        std::string get_anys(char c, bool neg, std::string_view input, std::string_view iter, size_t depth){
            return "//TODO";
        }

        /*
         * if($input[$iter] == 0){
         *     ?$iter++;
         * } else{
         *     goto $label;
         * }
         */
        std::string expect_eoe(bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth){
            return "//TODO";
        }

        /*
         * if($input[$iter] == 0){
         *     ?$iter++;
         * }
         */
        std::string get_eoe(bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth){
            return "//TODO";
        }

        /*
         * if(?($input[$iter] >= '$a' && $input[$iter] <= '$b')){ // !(a >= b && a <= c) = a < b || a > c
         *     $iter++;
         * } else{
         *     goto $label;
         * }
         */
        /*std::string expect_range(char a, char b, bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth){
            std::string tabs = std::string(depth, '\t');

            std::stringstream ss;

            ss << tabs << "if(" << input << "[" << iter << "] " << (neg?"<":">=") << " \'" << a << "\' " << (neg?"|| ":"&& ") << input << "[" << iter << "] " << (neg?">":"<=") << " \'" << b << "\'){" << std::endl;
            ss << tabs << "\t" << iter << "++;" << std::endl;
            ss << tabs << "} else{" << std::endl;
            ss << tabs << "\tgoto " << label << ";" << std::endl;
            ss << tabs << "}" << std::endl;
            ss << std::endl;

            return ss.str();
        }*/ 

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
         *     size_t $my_label = 0;
         *     while($?input[$iter] && ?($input[$iter] >= '$a' && $input[$iter] <= '$b')){
         *         $my_label++;
         *         $iter++;
         *     }
         *
         *     if(!$my_label){
         *         goto $label;
         *     }
         * }
         */
        /*std::string expect_ranges(char a, char b, bool neg, std::string_view input, std::string_view iter, std::string_view label, size_t depth, std::string_view prefix, size_t* id){
            std::string tabs = std::string(depth, '\t');

            std::stringstream ss;
            ss << tabs << "{" << std::endl;
            ss << tabs << "\tsize_t " << prefix << "_" << *id << " = 0;" << std::endl;
            ss << tabs << "\twhile(" << input << "[" << iter << "] && " << (neg?"!":"") << "(" << input << "[" << iter << "] >= \'" << a << "\' && " << input << "[" << iter << "] <= \'" << b << "\')){" << std::endl;
            ss << tabs << "\t\t" << prefix << "_" << *id << "++;" << std::endl;
            ss << tabs << "\t\t" << iter << "++;" << std::endl;
            ss << tabs << "\t}" << std::endl;
            ss << std::endl; 
            ss << tabs << "\tif(!" << prefix << "_" << *id << "){" << std::endl;
            ss << tabs << "\t\tgoto " << label << ";" << std::endl;
            ss << tabs << "\t}" << std::endl;
            ss << tabs << "}" << std::endl;
            ss << std::endl;

            (*id)++;

            return ss.str();
        }*/ 

        std::string get_ranges(char a, char b, bool neg, bool expect, State& state){
            std::string tabs = std::string(state.m_Depth, '\t');

            std::stringstream ss;
            ss << tabs << "{" << std::endl;
            ss << tabs << "\tsize_t " << state.m_Prefix << "_" << state.m_ID << " = 0;" << std::endl;
            ss << tabs << "\twhile(" << state.m_Input << "[" << state.m_Iter << "] && " << (neg?"!":"") << "(" << state.m_Input << "[" << state.m_Iter << "] >= \'" << a << "\' && " << state.m_Input << "[" << state.m_Iter << "] <= \'" << b << "\')){" << std::endl;
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

            state.m_ID++;

            return ss.str();
        }

        /*
         * if(?($input[$iter] >= '$a' && $input[$iter] <= '$b')){ // !(a >= b && a <= c) = a < b || a > c
         *     $iter++;
         * }
         */
        /*std::string get_range(char a, char b, bool neg, std::string_view input, std::string_view iter, size_t depth){
            std::string tabs = std::string(depth, '\t');

            std::stringstream ss;

            ss << tabs << "if(" << input << "[" << iter << "] " << (neg?"<":">=") << " \'" << a << "\' " << (neg?"|| ":"&& ") << input << "[" << iter << "] " << (neg?">":"<=") << " \'" << b << "\'){" << std::endl;
            ss << tabs << "\t" << iter << "++;" << std::endl;
            ss << tabs << "}" << std::endl;
            ss << std::endl;

            return ss.str();
        }*/

        /*
         * while($?input[$iter] && ?($input[$iter] >= '$a' && $input[$iter] <= '$b')){
         *     $iter++;
         * }
         */
        /*std::string get_ranges(char a, char b, bool neg, std::string_view input, std::string_view iter, size_t depth){
            std::string tabs = std::string(depth, '\t');

            std::stringstream ss;
            ss << tabs << "while(" << input << "[" << iter << "] && " << (neg?"!":"") << "(" << input << "[" << iter << "] >= \'" << a << "\' && " << input << "[" << iter << "] <= \'" << b << "\')){" << std::endl;
            ss << tabs << "\t" << iter << "++;" << std::endl;
            ss << tabs << "}" << std::endl;
            ss << std::endl; 

            return ss.str();
        }*/

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
                    case trsre::TRSRE_TOKEN_TYPE_EOE:
                    case trsre::TRSRE_TOKEN_TYPE_RANGE: {
                        const char* value = tok.m_Value.c_str();
                        char a = Program::get_lit(&value);
                        value++;
                        char b = Program::get_lit(&value);
                        /*if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                            ss << c::get_range(a, b, neg, state.m_Input, iter_label, depth);
                        else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                            ss << c::get_ranges(a, b, neg, state.m_Input, iter_label, depth);
                        else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                            ss << c::expect_ranges(a, b, neg, state.m_Input, iter_label, end_label, depth, state.m_Prefix, &state.m_ID);
                        else
                            ss << c::expect_range(a, b, neg, state.m_Input, iter_label, end_label, depth);*/
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
                    case trsre::TRSRE_TOKEN_TYPE_EOE:
                    case trsre::TRSRE_TOKEN_TYPE_RANGE: {
                        const char* value = tok.m_Value.c_str();
                        char a = Program::get_lit(&value);
                        value++;
                        char b = Program::get_lit(&value);
                        /*if(mod == trsre::TRSRE_TOKEN_MODE_QUESTION)
                            ss << c::get_range(a, b, neg, state.m_Input, iter_label, depth);
                        else if(mod == trsre::TRSRE_TOKEN_MODE_STAR)
                            ss << c::get_ranges(a, b, neg, state.m_Input, iter_label, depth);
                        else if(mod == trsre::TRSRE_TOKEN_MODE_PLUS)
                            ss << c::expect_ranges(a, b, neg, state.m_Input, iter_label, end_label, depth, state.m_Prefix, &state.m_ID);
                        else
                            ss << c::expect_range(a, b, neg, state.m_Input, iter_label, end_label, depth);*/ 
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

