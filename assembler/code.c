#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short bin_dest(char *d){
	unsigned short bin = 0;

	if (d == (char) 0){
		return 0;
	}

	if (strcmp(d, "M") == 0){
		bin = 0b001;
	}
	else if (strcmp(d, "D") == 0){
		bin = 0b010;
	}
	else if (strcmp(d, "MD") == 0){
		bin = 0b011;
	}
	else if (strcmp(d, "A") == 0){
		bin = 0b100;
	}
	else if (strcmp(d, "AM") == 0){
		bin = 0b101;
	}
	else if (strcmp(d, "AD") == 0){
		bin = 0b110;
	}
	else if (strcmp(d, "AMD") == 0){
		bin = 0b111;
	}

	return bin;
}

unsigned short bin_comp(char *c){
	unsigned short bin = 0;

	if (strcmp(c, "0") == 0){
		bin = 0b0101010;
	}
	else if (strcmp(c, "1") == 0){
		bin = 0b0111111;
	}
	else if (strcmp(c, "-1") == 0){
		bin = 0b0111010;
	}
	else if (strcmp(c, "D") == 0){
		bin = 0b0001100;
	}
	else if (strcmp(c, "A") == 0){
		bin = 0b0110000;
	}
	else if (strcmp(c, "!D") == 0){
		bin = 0b0001101;
	}
	else if (strcmp(c, "!A") == 0){
		bin = 0b0110001;
	}
	else if (strcmp(c, "-D") == 0){
		bin = 0b0001111;
	}
	else if (strcmp(c, "-A") == 0){
		bin = 0b0110011;
	}
	else if (strcmp(c, "D+1") == 0){
		bin = 0b0011111;
	}
	else if (strcmp(c, "A+1") == 0){
		bin = 0b0110111;
	}
	else if (strcmp(c, "D-1") == 0){
		bin = 0b0001110;
	}
	else if (strcmp(c, "A-1") == 0){
		bin = 0b0110010;
	}
	else if (strcmp(c, "D+A") == 0){
		bin = 0b0000010;
	}
	else if (strcmp(c, "D-A") == 0){
		bin = 0b0010011;
	}
	else if (strcmp(c, "A-D") == 0){
		bin = 0b0000111;
	}
	else if (strcmp(c, "D&A") == 0){
		bin = 0b0000000;
	}
	else if (strcmp(c, "D|A") == 0){
		bin = 0b0010101;
	}
	else if (strcmp(c, "M") == 0){
		bin = 0b1110000;
	}
	else if (strcmp(c, "!M") == 0){
		bin = 0b1110001;
	}
	else if (strcmp(c, "-M") == 0){
		bin = 0b1110011;
	}
	else if (strcmp(c, "M+1") == 0){
		bin = 0b1110111;
	}
	else if (strcmp(c, "M-1") == 0){
		bin = 0b1110010;
	}
	else if (strcmp(c, "D+M") == 0){
		bin = 0b1000010;
	}
	else if (strcmp(c, "D-M") == 0){
		bin = 0b1010011;
	}
	else if (strcmp(c, "M-D") == 0){
		bin = 0b1000111;
	}
	else if (strcmp(c, "D&M") == 0){
		bin = 0b1000000;
	}
	else if (strcmp(c, "D|M") == 0){
		bin = 0b1010101;
	}
}

unsigned short bin_jump(char *j){
	unsigned short bin = 0;

	if (j == (char) 0){
		return 0;
	}

	if (strcmp(j, "JGT")){
		bin = 0b001;
	}
	else if (strcmp(j, "JEQ") == 0){
		bin = 0b010;
	}
	else if (strcmp(j, "JGE") == 0){
		bin = 0b011;
	}
	else if (strcmp(j, "JLT") == 0){
		bin = 0b100;
	}
	else if (strcmp(j, "JNE") == 0){
		bin = 0b101;
	}
	else if (strcmp(j, "JLE") == 0){
		bin = 0b110;
	}
	else if (strcmp(j, "JMP") == 0){
		bin = 0b111;
	}

	return bin;
}