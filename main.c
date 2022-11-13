/*
* @author LeonelMatos [LeonelMatos's Github](https://github.com/LeonelMatos)
* 
* Ecosystem - @version 0.0.1
*
*/

/*INCLUDE/DEFINE*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "entity.h"

#define R 10 ///Rows of the map
#define C 10 ///Columns of the map

/*DATA*/

/** \bug Deprecated
* unsigned short int rabbits = 10;
* unsigned short int foxes = 2;
*/

/// @brief Ecosystem map area of size \def R rows
/// and \def C columns
typedef struct {
	unsigned int num_entities;
	Entity entities[R*C/2];
	char map[R][C];
} Map;


/*SETTINGS*/

unsigned short int time_scale = 1;
unsigned short int ticks = 10;

/*AUX FUNCTIONS*/

/// @brief Error handling function using unistd.h
/// @param s Error message
void kill(const char *s) {
	perror(s);
	exit(1);
}

/// @brief Reads a key from STDIN_FILENO
/// @return Char pressed key
int read_key() {
	int nread;
	char input;
	int c;

	while ((nread = read(STDIN_FILENO, &input, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN)
			kill("read");
	}

	while ((c = getchar()) != '\n' && c != '\0' && c != EOF) { }

	return input;
}

/*INIT*/

/// @brief Initiates an animal
/// @param a animal pointer
/// @param type animal type enum
/// @param pos position struct with x,y
void init_entity (Entity *a, Type type, Position pos) {
	a->pos = pos;
	a->type = type;
	a->pos = pos;
}

/// @brief Initiates the map area
/// @param m map area pointer
/// @param r rows
/// @param c columns
void init_map (int r, int c, Map *m) {
	m->num_entities = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			m->map[i][j] = ' ';
}

void update_map () {
	
}

/*ECOSYSTEM*/

void draw_map(int r, int c, char map[r][c]) {

	printf(".");
	for (int i = 0; i < c; i++) {
		printf("_.");
	}
	printf("\n");

	for (int i = 0; i < r; i++) {
		printf("|");
		for (int j = 0; j < c; j++) {
			printf("%c|", map[i][j]);
		}
		printf("\n");
	}
	printf(".");
	for (int i = 0; i < c; i++) {
		printf("_.");
	}
	printf("\n");
}

void simulate() {
	

	sleep(time_scale);
}

/*MAIN*/

int main () {

	int activeRun = 1;

	Map map;
	Entity ent1;
	Position pos;
	pos.x = 1;
	pos.y = 1;

	init_map(R, C, &map);
	init_entity(&ent1, Rabbit, pos);

	draw_map(R, C, map.map);

	while(activeRun) {
		
		simulate();

		if (read_key() == 'q'){
			printf("Exiting...");
			break;
		}

	}

	printf("\n");
	return 0;
}
