all: ada

ada:
	gcc -std=c23 -ggdb ada.c -o ada
