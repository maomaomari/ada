#ifndef _BUFFER
#define _BUFFER

#include <stdio.h>

#ifndef STD_LINE_SIZE
#define STD_LINE_SIZE 512
#endif

typedef struct line_s {
	char* line;
	struct line_s *p, *n;
	int len;
} line_t;

typedef struct buff_state_s {
	line_t *head, *tail, *current;
	int size, pos;
} buff_state_t;

void buffer_print_all(const buff_state_t *const state);
void buffer_print_all_ln(const buff_state_t* const state);
void buffer_load(buff_state_t *state, FILE* file);

line_t* list_init(void);
line_t* list_insert(buff_state_t* state, char* str);
line_t* list_append(buff_state_t* state, char* str);



#endif
