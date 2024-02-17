#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRSRE_EXT
#include <trsre.h>

char* stpcat(char* s1, const char* s2){
	size_t len = strlen(s2);
	return strcpy(s1 + strlen(s1), s2) + len;
}

void parse(const char* rule, char* buffer, size_t len){
	if(len <= 10)
		return;

	size_t i = 0;
	buffer[i++] = '{';
	buffer[i] = 0;

	do{
		trsre_Token tok = trsre_get_token(rule);
		rule += tok.m_Length;
		
		if(tok.m_Mode & TRSRE_TOKEN_MODE_NOT)
			rule++;

		if(tok.m_Mode & ~TRSRE_TOKEN_MODE_NOT)
			rule++;

		char* p = stpcat(buffer, trsre_token_type_to_string3_ext(tok.m_Type));
		p = stpcat(p, "-");
		p = stpcat(p, trsre_token_mode_to_string3_ext(tok.m_Mode));
		p = stpcat(p, ":");
		i += 8;

		switch(tok.m_Type){
			case TRSRE_TOKEN_TYPE_EMPTY:
				break;
			case TRSRE_TOKEN_TYPE_LITERAL:
			case TRSRE_TOKEN_TYPE_RANGE: {
				char* b = malloc(tok.m_Length);
				if(!b)
					return;

				memcpy(b, tok.m_Value, tok.m_Length);
				b[tok.m_Length] = 0;

				strcat(p, b);

				free(b);
			} break;
			case TRSRE_TOKEN_TYPE_ANY:
				strcat(p, ".");
				break;
			case TRSRE_TOKEN_TYPE_EOE:
				strcat(p, "$");
				break;
			case TRSRE_TOKEN_TYPE_CHOOSE: 
			case TRSRE_TOKEN_TYPE_GROUP: {
				if(++i >= len)
					return;
			
				char* b = malloc(tok.m_Length);
				if(!b)
					return;
			
				memcpy(b, tok.m_Value, tok.m_Length - 1);
				b[tok.m_Length - 1] = 0;

				parse(b + 1, p, len);

				free(b);
			} break;
		}
		i = strlen(buffer);
	} while(len - i > 8 && *rule);

	if(i >= len)
		return;

	strcat(&buffer[i], "}");
}

int main(int argc, const char** argv){
	if(argc < 3)
		return -1;

	const char* rule = argv[1];
	const char* except = argv[2];

	printf("Rule: \"%s\"\nExcept: \"%s\"\n", rule, except);

	size_t len = strlen(except) + 10;
	char* tokens_str = (char*) malloc(len + 1);
	if(!tokens_str)
		return -2;
	
	tokens_str[0] = 0;

	parse(rule, tokens_str, len);

	if(strcmp(except, tokens_str) != 0){
		printf("Got: \"%s\"\n\tFAILED\n\n", tokens_str);

		free(tokens_str);
		return 1;
	}

	printf("\tPASSED\n\n");

	free(tokens_str);
	return 0;
}

