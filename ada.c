#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STD_SIZE 10000
#define STD_LINE_SIZE 512

typedef struct line_s {
	char* line;
	struct line_s *pline, *nline;
	int len;
}line_t;

line_t* head;
line_t* tail;
line_t *current_line;
int size = 0;
int pos = 0;

line_t* init_list(void);
line_t* add_list_f(FILE* file);
line_t* add_list_b(FILE* file);

int main(int argc, char** argv) {

	FILE* file = fopen(argv[1], "r");

	char buf[STD_LINE_SIZE];
	
	head = init_list();
	current_line = head;

	fgets(current_line->line, 512, file);
	current_line->len = strlen(current_line->line);
	size++;
	
	while(!feof(file)) {
		current_line = add_list_f(file);
	}

	fclose(file);
	
	tail = current_line;
	current_line = head;

	while(strcmp(buf, "q\n")){
		fflush(stdin);
		fgets(buf, STD_LINE_SIZE, stdin);
	}
	return 0;
}

line_t* init_list() {
	line_t* list = malloc(sizeof(*list));
	list->pline = NULL;
	list->nline = NULL;
	list->len = 0;
	list->line = malloc(STD_LINE_SIZE);
	return list;
}

line_t* add_list_f(FILE* file) {
	line_t* tmp = malloc(sizeof(*tmp));
	current_line->nline = tmp;
	tmp->pline = current_line;
	tmp->nline = NULL;
	tmp->line = malloc(STD_LINE_SIZE);
	fgets(tmp->line, STD_LINE_SIZE, file);
	tmp->len= strlen(tmp->line);

	size++;
	
	return tmp;
}
