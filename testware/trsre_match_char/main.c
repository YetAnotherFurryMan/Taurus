#include <stdio.h>
#include <stdlib.h>

#include <trsre.h>

int main(int argc, const char** argv){
	argc--; argv++; // Program
	argc--; argv++; // Name
	
	if(argc < 3) 
		return 1;
	
	const char* rule = argv[0];
	char c = argv[1][0];
	char rc = argv[2][0];

	printf("Rule: '%s'\nCharacter: '%c'\nExcepting return to be %c\n", rule, c, rc);

	long r = 0;
	r = trsre_match_char(rule, c);
	
	if(rc == '-')
		r *= -1;

	if(r < 0){
		if(rc == '-')
			r *= -1;
		printf("\tr = %ld\n\tFAILED\n\n", r);
		return 1;
	}

	printf("\tPASSED\n\n");
	
	return 0;
}

