#pragma once

#include <string_view>

namespace trsrec{
    struct State{
        std::string_view m_Input;
        std::string_view m_Iter;
        std::string_view m_Prefix;
        std::string_view m_Label;
        std::size_t m_ID = 0;
        std::size_t m_Depth;
    };
}

