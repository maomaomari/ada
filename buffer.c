#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

void buffer_print_all(const buff_state_t* const state) {
	line_t* tmp = malloc(sizeof(*tmp));
	tmp = state->head;
	while(tmp != NULL) {
		printf("%s", tmp->line);
		tmp = tmp->n;
	}
	//	printf("\x1b[31mEOF\x1b[39m\n");
}

void buffer_print_all_ln(const buff_state_t* const state) {
	line_t* tmp = malloc(sizeof(*tmp));
	tmp = state->head;
	int i = 0;
	while(tmp != NULL) {
		printf("%d\t%s",++i, tmp->line);
		tmp = tmp->n;
	}

}

void buffer_load(buff_state_t* state, FILE* file) {

	char buf[STD_LINE_SIZE];
	
	state->head = list_init();
	state->current = state->head;

	fgets(buf, STD_LINE_SIZE, file);
	strcpy(state->current->line, buf);
	state->current->len = strlen(state->current->line);
	state->size++;


	fgets(buf, STD_LINE_SIZE, file);
	while(!feof(file)) {
		state->current = list_append(state, buf);
		fgets(buf, STD_LINE_SIZE, file);
	}
	state->tail = state->current;
	state->pos = state->size;
	//	state->current = state->head;
}

int buffer_write_to_file(buff_state_t* state){

	return 0;
}

line_t* list_init() {
	line_t* list = malloc(sizeof(*list));
	list->p = NULL;
	list->n = NULL;
	list->len = 0;
	list->line = malloc(STD_LINE_SIZE);
	return list;
}

line_t* list_append(buff_state_t* state, char* str) {
	line_t* tmp = malloc(sizeof(*tmp));

	/* check for head/tail */
	if(state->current == state->tail)
		state->tail = tmp;

	if(state->current->n != NULL) {
		tmp->n = state->current->n;
		tmp->n->p = tmp;
	} else {
		tmp->n = NULL;
	}
	state->current->n = tmp;
	tmp->p = state->current;
	
	/* inserts data */
	tmp->line = malloc(STD_LINE_SIZE);
	//	fgets(tmp->line, STD_LINE_SIZE, file);
	strcpy(tmp->line, str);
	tmp->len = strlen(tmp->line);
	state->size++;
	state->pos++;
	
	return tmp;
}
