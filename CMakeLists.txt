cmake_minimum_required(VERSION 3.22)

project(Taurus VERSION 0.8.2 LANGUAGES C CXX)

include(CTest)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(trsap STATIC
	trsap/src/trsap.c
)

target_include_directories(trsap PUBLIC trsap/headers)

add_library(trscli STATIC
	trscli/src/trscli.c
)

target_include_directories(trscli PUBLIC trscli/headers)

add_library(trsre STATIC
	trsre/src/find.c
	trsre/src/get_token.c
	trsre/src/match.c
	trsre/src/match_char.c
	trsre/src/match_group.c
)

target_include_directories(trsre PUBLIC trsre/headers)

add_library(trsre-ext STATIC
	trsre/ext/string.c
)

target_include_directories(trsre-ext PUBLIC trsre/headers)

add_executable(trsrec
	trsrec/src/c.cpp
	trsrec/src/log_token.cpp
	trsrec/src/main.cpp
	trsrec/src/program_generate_c_cpp.cpp
	trsrec/src/program_get_lit.cpp
	trsrec/src/program_init.cpp
	trsrec/src/program_load.cpp
	trsrec/src/program_terminate.cpp
)

target_include_directories(trsrec PRIVATE trsrec/headers)
target_link_libraries(trsrec PUBLIC trsap)
target_link_libraries(trsrec PUBLIC trscli)
target_link_libraries(trsrec PUBLIC trsre)
target_link_libraries(trsrec PUBLIC trsre-ext)

add_executable(trsre_match_char.test
	testware/trsre_match_char/main.c
)

target_link_libraries(trsre_match_char.test PUBLIC trsre)

add_executable(trsre_match_group.test
	testware/trsre_match_group/main.c
)

target_link_libraries(trsre_match_group.test PUBLIC trsre)

add_executable(trsre_get_token.test
	testware/trsre_get_token/main.c
)

target_link_libraries(trsre_get_token.test PUBLIC trsre)
target_link_libraries(trsre_get_token.test PUBLIC trsre-ext)

add_executable(trsrec.test
	testware/trsrec/main.c
)


add_test(NAME trsre_match_char1
	COMMAND trsre_match_char.test trsre_match_char1
	"a"
	"a"
	"+"
)

add_test(NAME trsre_match_char2
	COMMAND trsre_match_char.test trsre_match_char2
	"a"
	"b"
	"-"
)

add_test(NAME trsre_match_char3
	COMMAND trsre_match_char.test trsre_match_char3
	"[ab]"
	"a"
	"+"
)

add_test(NAME trsre_match_char4
	COMMAND trsre_match_char.test trsre_match_char4
	"[ab]"
	"b"
	"+"
)

add_test(NAME trsre_match_char5
	COMMAND trsre_match_char.test trsre_match_char5
	"[ab]"
	"c"
	"-"
)

add_test(NAME trsre_match_char6
	COMMAND trsre_match_char.test trsre_match_char6
	"."
	"a"
	"+"
)

add_test(NAME trsre_match_char7
	COMMAND trsre_match_char.test trsre_match_char7
	"\\."
	"."
	"+"
)

add_test(NAME trsre_match_char8
	COMMAND trsre_match_char.test trsre_match_char8
	"\\."
	"a"
	"-"
)

add_test(NAME trsre_match_char9
	COMMAND trsre_match_char.test trsre_match_char9
	"a-z"
	"a"
	"+"
)

add_test(NAME trsre_match_char10
	COMMAND trsre_match_char.test trsre_match_char10
	"a-z"
	"f"
	"+"
)

add_test(NAME trsre_match_char11
	COMMAND trsre_match_char.test trsre_match_char11
	"a-z"
	"z"
	"+"
)

add_test(NAME trsre_match_char12
	COMMAND trsre_match_char.test trsre_match_char12
	"a-z"
	"A"
	"-"
)

add_test(NAME trsre_match_group1
	COMMAND trsre_match_group.test trsre_match_group1
	"(abc)"
	"abc"
	"3"
	"+"
)

add_test(NAME trsre_match_group2
	COMMAND trsre_match_group.test trsre_match_group2
	"(abc)"
	"cba"
	"0"
	"-"
)

add_test(NAME trsre_match_group3
	COMMAND trsre_match_group.test trsre_match_group3
	"(ab+)"
	"ab"
	"2"
	"+"
)

add_test(NAME trsre_match_group4
	COMMAND trsre_match_group.test trsre_match_group4
	"(ab+)"
	"a"
	"1"
	"-"
)

add_test(NAME trsre_match_group5
	COMMAND trsre_match_group.test trsre_match_group5
	"(ab*)"
	"a"
	"1"
	"+"
)

add_test(NAME trsre_match_group6
	COMMAND trsre_match_group.test trsre_match_group6
	"(ab*)"
	"ab"
	"2"
	"+"
)

add_test(NAME trsre_match_group7
	COMMAND trsre_match_group.test trsre_match_group7
	"([abc])"
	"a"
	"1"
	"+"
)

add_test(NAME trsre_match_group8
	COMMAND trsre_match_group.test trsre_match_group8
	"([abc])"
	"d"
	"0"
	"-"
)

add_test(NAME trsre_match_group9
	COMMAND trsre_match_group.test trsre_match_group9
	"(a[ab]+)"
	"aaba"
	"4"
	"+"
)

add_test(NAME trsre_match_group10
	COMMAND trsre_match_group.test trsre_match_group10
	"(a[ab]+)"
	"a"
	"1"
	"-"
)

add_test(NAME trsre_match_group11
	COMMAND trsre_match_group.test trsre_match_group11
	"(a[ab]*)"
	"a"
	"1"
	"+"
)

add_test(NAME trsre_match_group12
	COMMAND trsre_match_group.test trsre_match_group12
	"(a[ab]*)"
	"aaba"
	"4"
	"+"
)

add_test(NAME trsre_match_group13
	COMMAND trsre_match_group.test trsre_match_group13
	"(a[ab]*[cd]*)"
	"a"
	"1"
	"+"
)

add_test(NAME trsre_match_group14
	COMMAND trsre_match_group.test trsre_match_group14
	"(a[ab]?)"
	"a"
	"1"
	"+"
)

add_test(NAME trsre_match_group15
	COMMAND trsre_match_group.test trsre_match_group15
	"(a[ab]?)"
	"aaba"
	"2"
	"+"
)

add_test(NAME trsre_match_group16
	COMMAND trsre_match_group.test trsre_match_group16
	"(a\\*\\+\\?)"
	"a*+?"
	"4"
	"+"
)

add_test(NAME trsre_match_group17
	COMMAND trsre_match_group.test trsre_match_group17
	"(a\\*\\+\\?)"
	"aaaa"
	"1"
	"-"
)

add_test(NAME trsre_match_group18
	COMMAND trsre_match_group.test trsre_match_group18
	"(aA-Z)"
	"aA"
	"2"
	"+"
)

add_test(NAME trsre_match_group19
	COMMAND trsre_match_group.test trsre_match_group19
	"(aA-Z)"
	"aZ"
	"2"
	"+"
)

add_test(NAME trsre_match_group20
	COMMAND trsre_match_group.test trsre_match_group20
	"(aA-Z)"
	"aa"
	"1"
	"-"
)

add_test(NAME trsre_match_group21
	COMMAND trsre_match_group.test trsre_match_group21
	"(a$)"
	"a"
	"1"
	"+"
)

add_test(NAME trsre_match_group22
	COMMAND trsre_match_group.test trsre_match_group22
	"(a$)"
	"aa"
	"1"
	"-"
)

add_test(NAME trsre_match_group23
	COMMAND trsre_match_group.test trsre_match_group23
	"(a^b)"
	"aa"
	"2"
	"+"
)

add_test(NAME trsre_match_group24
	COMMAND trsre_match_group.test trsre_match_group24
	"(a^b)"
	"ab"
	"1"
	"-"
)

add_test(NAME trsre_match_group25
	COMMAND trsre_match_group.test trsre_match_group25
	"(a^[ab])"
	"ac"
	"2"
	"+"
)

add_test(NAME trsre_match_group26
	COMMAND trsre_match_group.test trsre_match_group26
	"(a^[ab])"
	"aa"
	"1"
	"-"
)

add_test(NAME trsre_match_group27
	COMMAND trsre_match_group.test trsre_match_group27
	"(a^[ab])"
	"ab"
	"1"
	"-"
)

add_test(NAME trsre_match_group28
	COMMAND trsre_match_group.test trsre_match_group28
	"(a^b+)"
	"aaa"
	"3"
	"+"
)

add_test(NAME trsre_match_group29
	COMMAND trsre_match_group.test trsre_match_group29
	"(a^b+)"
	"aab"
	"2"
	"+"
)

add_test(NAME trsre_match_group30
	COMMAND trsre_match_group.test trsre_match_group30
	"(a^b+)"
	"abb"
	"1"
	"-"
)

add_test(NAME trsre_match_group31
	COMMAND trsre_match_group.test trsre_match_group31
	"(a(b))"
	"ab"
	"2"
	"+"
)

add_test(NAME trsre_match_group32
	COMMAND trsre_match_group.test trsre_match_group32
	"(a(b))"
	"aa"
	"1"
	"-"
)

add_test(NAME trsre_match_group33
	COMMAND trsre_match_group.test trsre_match_group33
	"(a(b))"
	"a"
	"1"
	"-"
)

add_test(NAME trsre_match_group34
	COMMAND trsre_match_group.test trsre_match_group34
	"(a(b[bc]*))"
	"abbc"
	"4"
	"+"
)

add_test(NAME trsre_match_group35
	COMMAND trsre_match_group.test trsre_match_group35
	"(a(b[bc]*))"
	"ab"
	"2"
	"+"
)

add_test(NAME trsre_match_group36
	COMMAND trsre_match_group.test trsre_match_group36
	"(a(bc*)+)"
	"ab"
	"2"
	"+"
)

add_test(NAME trsre_match_group37
	COMMAND trsre_match_group.test trsre_match_group37
	"(a(bc*)+)"
	"abbcbcc"
	"7"
	"+"
)

add_test(NAME trsre_match_group38
	COMMAND trsre_match_group.test trsre_match_group38
	"(a(bc*)+)"
	"a"
	"1"
	"-"
)

add_test(NAME trsre_match_group39
	COMMAND trsre_match_group.test trsre_match_group39
	"(a^(bb)c)"
	"abc"
	"3"
	"+"
)

add_test(NAME trsre_match_group40
	COMMAND trsre_match_group.test trsre_match_group40
	"(a^(bb))"
	"abb"
	"1"
	"-"
)

add_test(NAME trsre_get_token1
	COMMAND trsre_get_token.test trsre_get_token1
	"(abc)"
	"{GRP-SNG:{LIT-SNG:aLIT-SNG:bLIT-SNG:c}}"
)

add_test(NAME trsre_get_token2
	COMMAND trsre_get_token.test trsre_get_token2
	"(ab+)"
	"{GRP-SNG:{LIT-SNG:aLIT-PLS:b}}"
)

add_test(NAME trsre_get_token3
	COMMAND trsre_get_token.test trsre_get_token3
	"(ab*)"
	"{GRP-SNG:{LIT-SNG:aLIT-STR:b}}"
)

add_test(NAME trsre_get_token4
	COMMAND trsre_get_token.test trsre_get_token4
	"([abc])"
	"{GRP-SNG:{CHS-SNG:{LIT-SNG:aLIT-SNG:bLIT-SNG:c}}}"
)

add_test(NAME trsre_get_token5
	COMMAND trsre_get_token.test trsre_get_token5
	"(a[ab]+)"
	"{GRP-SNG:{LIT-SNG:aCHS-PLS:{LIT-SNG:aLIT-SNG:b}}}"
)

add_test(NAME trsre_get_token6
	COMMAND trsre_get_token.test trsre_get_token6
	"(a[ab]*)"
	"{GRP-SNG:{LIT-SNG:aCHS-STR:{LIT-SNG:aLIT-SNG:b}}}"
)

add_test(NAME trsre_get_token7
	COMMAND trsre_get_token.test trsre_get_token7
	"(a[ab]*[cd]*)"
	"{GRP-SNG:{LIT-SNG:aCHS-STR:{LIT-SNG:aLIT-SNG:b}CHS-STR:{LIT-SNG:cLIT-SNG:d}}}"
)

add_test(NAME trsre_get_token8
	COMMAND trsre_get_token.test trsre_get_token8
	"(a[ab]?)"
	"{GRP-SNG:{LIT-SNG:aCHS-QST:{LIT-SNG:aLIT-SNG:b}}}"
)

add_test(NAME trsre_get_token9
	COMMAND trsre_get_token.test trsre_get_token9
	"(a\\*\\+\\?)"
	"{GRP-SNG:{LIT-SNG:aLIT-SNG:\\*LIT-SNG:\\+LIT-SNG:\\?}}"
)

add_test(NAME trsre_get_token10
	COMMAND trsre_get_token.test trsre_get_token10
	"(aA-Z)"
	"{GRP-SNG:{LIT-SNG:aRNG-SNG:A-Z}}"
)

add_test(NAME trsre_get_token11
	COMMAND trsre_get_token.test trsre_get_token11
	"(a$)"
	"{GRP-SNG:{LIT-SNG:aEOE-SNG:$}}"
)

add_test(NAME trsre_get_token12
	COMMAND trsre_get_token.test trsre_get_token12
	"(a^b)"
	"{GRP-SNG:{LIT-SNG:aLIT-NOT:b}}"
)

add_test(NAME trsre_get_token13
	COMMAND trsre_get_token.test trsre_get_token13
	"(a^[ab])"
	"{GRP-SNG:{LIT-SNG:aCHS-NOT:{LIT-SNG:aLIT-SNG:b}}}"
)

add_test(NAME trsre_get_token14
	COMMAND trsre_get_token.test trsre_get_token14
	"(a^b+)"
	"{GRP-SNG:{LIT-SNG:aLIT-NPL:b}}"
)

add_test(NAME trsre_get_token15
	COMMAND trsre_get_token.test trsre_get_token15
	"(a(b))"
	"{GRP-SNG:{LIT-SNG:aGRP-SNG:{LIT-SNG:b}}}"
)

add_test(NAME trsre_get_token16
	COMMAND trsre_get_token.test trsre_get_token16
	"(a(b[bc]*))"
	"{GRP-SNG:{LIT-SNG:aGRP-SNG:{LIT-SNG:bCHS-STR:{LIT-SNG:bLIT-SNG:c}}}}"
)

add_test(NAME trsre_get_token17
	COMMAND trsre_get_token.test trsre_get_token17
	"(a(bc*)+)"
	"{GRP-SNG:{LIT-SNG:aGRP-PLS:{LIT-SNG:bLIT-STR:c}}}"
)

add_test(NAME trsre_get_token18
	COMMAND trsre_get_token.test trsre_get_token18
	"(a^(bb)c)"
	"{GRP-SNG:{LIT-SNG:aGRP-NOT:{LIT-SNG:bLIT-SNG:b}LIT-SNG:c}}"
)

add_test(NAME trsre_get_token19
	COMMAND trsre_get_token.test trsre_get_token19
	"(a^(bb))"
	"{GRP-SNG:{LIT-SNG:aGRP-NOT:{LIT-SNG:bLIT-SNG:b}}}"
)

add_test(NAME trsrec1
	COMMAND trsrec.test trsrec1
	"./build/trsrec"
	"a"
	"a"
	"1"
	"b"
	"0"
)

add_test(NAME trsrec2
	COMMAND trsrec.test trsrec2
	"./build/trsrec"
	"[ab]"
	"a"
	"1"
	"b"
	"1"
	"c"
	"0"
)

add_test(NAME trsrec3
	COMMAND trsrec.test trsrec3
	"./build/trsrec"
	"."
	"a"
	"1"
)

add_test(NAME trsrec4
	COMMAND trsrec.test trsrec4
	"./build/trsrec"
	"\\."
	"."
	"1"
	"a"
	"0"
)

add_test(NAME trsrec5
	COMMAND trsrec.test trsrec5
	"./build/trsrec"
	"a-z"
	"a"
	"1"
	"f"
	"1"
	"z"
	"1"
	"A"
	"0"
)

add_test(NAME trsrec6
	COMMAND trsrec.test trsrec6
	"./build/trsrec"
	"abc"
	"abc"
	"3"
	"abd"
	"2"
	"add"
	"1"
	"cba"
	"0"
)

add_test(NAME trsrec7
	COMMAND trsrec.test trsrec7
	"./build/trsrec"
	"ab+c"
	"abbc"
	"4"
	"abc"
	"3"
	"ab"
	"2"
	"a"
	"1"
	"ac"
	"1"
)

add_test(NAME trsrec8
	COMMAND trsrec.test trsrec8
	"./build/trsrec"
	"ab*c"
	"abbc"
	"4"
	"abc"
	"3"
	"ab"
	"2"
	"a"
	"1"
	"ac"
	"2"
)

add_test(NAME trsrec9
	COMMAND trsrec.test trsrec9
	"./build/trsrec"
	"a[ab]+c"
	"aabac"
	"5"
	"aac"
	"3"
	"abc"
	"3"
	"ac"
	"1"
	"a"
	"1"
)

add_test(NAME trsrec10
	COMMAND trsrec.test trsrec10
	"./build/trsrec"
	"a[ab]*c"
	"aabac"
	"5"
	"aac"
	"3"
	"abc"
	"3"
	"ac"
	"2"
	"a"
	"1"
)

add_test(NAME trsrec11
	COMMAND trsrec.test trsrec11
	"./build/trsrec"
	"a[ab]?c"
	"abc"
	"3"
	"aac"
	"3"
	"ac"
	"2"
	"a"
	"1"
	"aaac"
	"2"
	"ad"
	"1"
)

add_test(NAME trsrec12
	COMMAND trsrec.test trsrec12
	"./build/trsrec"
	"\\*\\+\\?"
	"*+?"
	"3"
)

add_test(NAME trsrec13
	COMMAND trsrec.test trsrec13
	"./build/trsrec"
	"aA-Z"
	"aA"
	"2"
	"aZ"
	"2"
	"aa"
	"1"
)

add_test(NAME trsrec14
	COMMAND trsrec.test trsrec14
	"./build/trsrec"
	"a$"
	"a"
	"2"
	"aa"
	"1"
)

add_test(NAME trsrec15
	COMMAND trsrec.test trsrec15
	"./build/trsrec"
	"a^b"
	"aa"
	"2"
	"ab"
	"1"
)

add_test(NAME trsrec16
	COMMAND trsrec.test trsrec16
	"./build/trsrec"
	"a^[ab]"
	"ac"
	"2"
	"aa"
	"1"
	"ab"
	"1"
)

add_test(NAME trsrec17
	COMMAND trsrec.test trsrec17
	"./build/trsrec"
	"a^b+"
	"aaa"
	"3"
	"aab"
	"2"
	"abb"
	"1"
)

add_test(NAME trsrec18
	COMMAND trsrec.test trsrec18
	"./build/trsrec"
	"a(bc)"
	"abc"
	"3"
	"acc"
	"1"
)

add_test(NAME trsrec19
	COMMAND trsrec.test trsrec19
	"./build/trsrec"
	"a(b[bc]*)"
	"abbc"
	"4"
	"ab"
	"2"
	"ac"
	"1"
)

add_test(NAME trsrec20
	COMMAND trsrec.test trsrec20
	"./build/trsrec"
	"a(bc*)+"
	"ab"
	"2"
	"abb"
	"3"
	"abbcbcc"
	"7"
)

add_test(NAME trsrec21
	COMMAND trsrec.test trsrec21
	"./build/trsrec"
	"a^(bb)c"
	"accc"
	"4"
	"abcc"
	"1"
)

