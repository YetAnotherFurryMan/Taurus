#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* out = 0;
char* cmd = 0;

void e(int s){
	free(out);
	free(cmd);
	printf("\tFAILED\n\n");
	exit(s);
}

int main(int argc, const char** argv){
	const char* program = argv[0]; argc--; argv++;
	const char* name = argv[0]; argc--; argv++;

	if(argc < 2)
		return 0;

	const char* trsrec = argv[0];
	const char* rule = argv[1];

	argc -= 2;
	argv += 2;

	printf("Program: %s\nName: %s\nTRSREC: %s\nRule: %s\n", program, name, trsrec, rule);

	size_t out_s = strlen(program) + strlen(name) + 4;
	out = malloc(out_s);
	if(!out){
		fprintf(stderr, "Malloc is dumper.\n");
		e(-1);
	}
	
	size_t cmd_s = strlen(trsrec) + strlen(rule) + out_s * 2 + 14;
	cmd = malloc(cmd_s);
	if(!cmd){
		fprintf(stderr, "Malloc is dump.\n");
		e(-1);
	}

	*out = 0;
	strcat(out, program);
	*(out + strlen(program) - 4) = 0; // Delete "test"
	strcat(out, "dir/");
	strcat(out, name);

	int r = -2;

	*cmd = 0;
	strcat(cmd, trsrec);
	strcat(cmd, " -i \"");
	strcat(cmd, rule);
	strcat(cmd, "\" -o \"");
	strcat(cmd, out);
	strcat(cmd, ".t\"");
	
	FILE* prog = popen(cmd, "r");
	if(!prog){
		fprintf(stderr, "Failed to popen \'%s\'.\n", cmd);
		e(-2);
	}


	r = pclose(prog);
	if(r){
		printf("FAILED - \'%s\' returned %d status.\n\n", cmd, r);
		e(r);
	}

	*cmd = 0;
	strcat(cmd, out);
	strcat(cmd, ".c");

	FILE* f = fopen(cmd, "w");
	fprintf(f, "#include <stddef.h>\n#include <stdio.h>\n\nint main(int argc, const char** argv){\n\nconst char* input = argv[1];\n#include \"%s.t\"\nprintf(\"%%d\", matches);\nreturn 0;\n}", name);
	fclose(f);

	*cmd = 0;
	strcat(cmd, "gcc \"");
	strcat(cmd, out);
	strcat(cmd, ".c\" -o \"");
	strcat(cmd, out);
	strcat(cmd, "\"");

	prog = popen(cmd, "r");
	if(!prog){
		fprintf(stderr, "failed to popen \'%s\'.\n", cmd);
		e(-2);
	}

	r = pclose(prog);
	if(r){
		printf("FAILED - \'%s\' returned %d status.\n\n", cmd, r);
		e(r);
	}

	*cmd = 0;
	strcat(cmd, "./");
	strcat(cmd, out);
	strcat(cmd, " \"");

	char* p = cmd + strlen(cmd);

	while(argc){
		const char* text = argv[0]; argc--;
		const char* so = argv[1]; argc--;
		argv += 2;

		int o = atoi(so);

		*p = 0;
		strcat(cmd, text);
		strcat(cmd, "\"");

		printf("Executing \'%s\', expecting %d status.\n", cmd, o);

		prog = popen(cmd, "r");
		if(!prog){
			fprintf(stderr, "failed to popen \'%s\'.\n", cmd);
			e(-2);
		}

		fscanf(prog, "%d", &r);

		pclose(prog);
		if(r != o){
			printf("GOT %d.\n", r);
			e(1);
		}
	}

	printf("\tPASSED\n\n");

	free(out);
	free(cmd);

	return 0;
}
