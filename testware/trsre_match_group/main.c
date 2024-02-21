#include <stdio.h>
#include <stdlib.h>

#include <trsre.h>

int main(int argc, const char** argv){
	argc--; argv++; // Program
	argc--; argv++; // Name
	
	if(argc < 4) 
		return 1;
	
	const char* rule = argv[0];
	const char* text = argv[1];
	size_t ti = atoi(argv[2]);
	char rc = argv[3][0];

	printf("Rule: '%s'\nText: '%s'\nExcepting %ld charactes pass\nExcepting return to be %c\n", rule, text, ti, rc);

	long r = 0;
	size_t t = 0;
	r = trsre_match_group(rule, text, &t);
	
	if(rc == '-')
		r *= -1;

	if(ti != t || r < 0){
		if(rc == '-')
			r *= -1;
		printf("\tr = %ld\n\tt = %ld\n\tFAILED\n\n", r, t);
		return 1;
	}

	printf("\tPASSED\n\n");
	
	return 0;
}

