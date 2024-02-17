#define TRSRE_EXT
#include <trsre.h>

#include <stdbool.h>

size_t trsre_token_to_string_ext(trsre_Token token, char* buffer, size_t size){
	bool neg = token.m_Mode & TRSRE_TOKEN_MODE_NOT;
	char mod = '\0';
	switch(token.m_Mode & (~TRSRE_TOKEN_MODE_NOT)){
		case TRSRE_TOKEN_MODE_PLUS:
			mod = '+';
			break;
		case TRSRE_TOKEN_MODE_STAR:
			mod = '*';
			break;
		case TRSRE_TOKEN_MODE_QUESTION:
			mod = '?';
			break;
	}

	if(buffer == 0){
		size_t len = token.m_Length;
		
		if(neg)
			len++;

		if(mod)
			len++;

		return len;
	}

	if(neg){
		buffer[0] = '^';
		buffer++;
		size--;
	}

	size_t i = 0;	
	while(i < size && token.m_Length - i > 0 && token.m_Value[i]){
		buffer[i] = token.m_Value[i];
		i++;
	}

	if(i < size && mod){
		buffer[i] = mod;
		i++;
	}

	if(neg)
		i++;

	return i;
}

const char* trsre_token_type_to_string_ext(trsre_TokenType type){
	switch(type){
#define CASE_TYPE(t) case TRSRE_TOKEN_TYPE_##t: return #t;
		CASE_TYPE(EMPTY)
		CASE_TYPE(LITERAL)
		CASE_TYPE(ANY)
		CASE_TYPE(EOE)
		CASE_TYPE(RANGE)
		CASE_TYPE(CHOOSE)
		CASE_TYPE(GROUP)
#undef CASE_TYPE
	}

	return 0;
}

const char* trsre_token_mode_to_string_ext(trsre_TokenMode mode){
	switch(mode){
#define CASE_MODE(m) case TRSRE_TOKEN_MODE_##m: return #m;
		CASE_MODE(SINGLE)
		CASE_MODE(NOT)
		CASE_MODE(PLUS)
		CASE_MODE(STAR)
		CASE_MODE(QUESTION)
		CASE_MODE(NOT_PLUS)
		CASE_MODE(NOT_STAR)
		CASE_MODE(NOT_QUESTION)
#undef CASE_MODE
	}

	return 0;
}

const char* trsre_token_type_to_string3_ext(trsre_TokenType type){
	switch(type){
		case TRSRE_TOKEN_TYPE_EMPTY:
			return "EMP";
		case TRSRE_TOKEN_TYPE_LITERAL:
			return "LIT";
		case TRSRE_TOKEN_TYPE_ANY:
			return "ANY";
		case TRSRE_TOKEN_TYPE_EOE:
			return "EOE";
		case TRSRE_TOKEN_TYPE_RANGE:
			return "RNG";
		case TRSRE_TOKEN_TYPE_CHOOSE:
			return "CHS";
		case TRSRE_TOKEN_TYPE_GROUP:
			return "GRP";
	}

	return 0;
}

const char* trsre_token_mode_to_string3_ext(trsre_TokenMode mode){
	switch(mode){
		case TRSRE_TOKEN_MODE_SINGLE:
			return "SNG";
		case TRSRE_TOKEN_MODE_NOT:
			return "NOT";
		case TRSRE_TOKEN_MODE_PLUS:
			return "PLS";
		case TRSRE_TOKEN_MODE_STAR:
			return "STR";
		case TRSRE_TOKEN_MODE_QUESTION:
			return "QST";
		case TRSRE_TOKEN_MODE_NOT_PLUS:
			return "NPL";
		case TRSRE_TOKEN_MODE_NOT_STAR:
			return "NST";
		case TRSRE_TOKEN_MODE_NOT_QUESTION:
			return "NQS";
	}

	return 0;
}

