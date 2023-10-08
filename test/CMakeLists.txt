cmake_minimum_required(VERSION 3.7)

project(test)

include_directories(${CMAKE_SOURCE_DIR}/core/include)

add_executable(lexer lexer/lexer.cpp)
target_link_libraries(lexer TRSCore)
install(TARGETS lexer RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

