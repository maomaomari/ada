#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

#define STD_LINE_SIZE 512

buff_state_t state = { };


int main(int argc, char** argv) {

	if(argc < 2) {
		printf("[ERROR] Incorrect usage, please enter 'ada <filename>' to use it.\n");
		exit(-1);
	}
	
	FILE* file = fopen(argv[1], "r");

	if(file == NULL) {
		printf("[ERROR] File does not exist or could not read it, please check if the file exists or there's proper access to it.\n");
		exit(-2);
	}
	
	char buf[STD_LINE_SIZE];

	buffer_load(&state, file);

	size_t fsize =  ftell(file);
	
	fclose(file);

	printf("%zu\n", fsize);
	/*
	  TODO: IMPLEMENT
	  - a : append line
	  - i : insert line
	  - c : change line with new
	  - d : delete
	  - p : print line DONE (no range)
	  - n : move to line where n is a positive integer
	  - w : write buffer to file
	  - +/- : increment decrement line;
	  - add $ for tail.

	  TODO: THINGS TO CONSIDER LATER!
	  - , : operator for ranges
	  - s : operator for replacing text eg. s/old/new
	  - g : global modifier
	  - n : line number modifier
	  - regex........ deus me ajude..
	*/
	
	while(strcmp(buf, "q\n")){
		fflush(stdin);
		fgets(buf, STD_LINE_SIZE, stdin);
		if(!strcmp(buf, ",p\n"))
			buffer_print_all(&state);
		if(!strcmp(buf, "p\n"))
			printf("%s", state.current->line);
		if(!strcmp(buf, "i\n"))
			state.current = list_insert(&state, "teste\n");
		if(!strcmp(buf, "+\n")){
			if(state.current->n != NULL) {
				state.current = state.current->n;
				state.pos++;
				printf("%s", state.current->line);
			} else
				printf("\x1b[31m?\x1b[39m\n");
		}
		if(!strcmp(buf, "-\n")){
			if(state.current->p != NULL) {
				state.current = state.current->p;
				state.pos--;
				printf("%s", state.current->line);
			} else
				printf("\x1b[31m?\x1b[39m\n");
		}
		if(!strcmp(buf, "$\n")) {
			state.current = state.tail;
			state.pos = state.size;
		}
		if(!strcmp(buf, "n\n"))
			printf("%d\t%s",state.pos, state.current->line);
		if(!strcmp(buf, ",n\n"))
			buffer_print_all_ln(&state);
	}

	return 0;
}

