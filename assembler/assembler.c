#include <stdio.h>
#include "parser.h"

int main(int argc, char* argv[]){
	Parser p;
	char *file_contents = NULL;

	parser_init(&p, file_contents);

	return 0;
}