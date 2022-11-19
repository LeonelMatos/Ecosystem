/**
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
#include "warning.h"

#define R 25 ///Rows of the map
#define C 30 ///Columns of the map

/// Boolean type definition
typedef enum {
	false = 0,
	true
} bool;

/*DATA*/

/** \bug Deprecated (the first lines of code)
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

/// @brief Error handling that may break the program
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

	/// @todo check if I can change this to avoid pressing ENTER every time 
	while ((nread = read(STDIN_FILENO, &input, 1)) != 1) {
		if (nread == -1 && errno != EAGAIN)
			kill("read");
	}

	while ((c = getchar()) != '\n' && c != '\0' && c != EOF) { }

	return input;
}

void warning(const Warning w) {
	printf("\033[0;31m");
	printf("\n%s\n", warning_to_string(w));
	printf("\033[0m");
	if (read_key() == 'q') kill ("Forced kill program after warning");
}

/*INIT*/

/// @brief Initiates an entity
/// @param type entity type enum
/// @param x position at x
/// @param y position at y
/// @return a returns the created entity
Entity init_entity (Type type, unsigned int x, unsigned int y) {
	Entity a;
	Position pos;
	pos.x = x;
	pos.y = y;

	a.pos = pos;
	a.type = type;

	return a;
}

void place_entity (Entity *a, Map *m) {
	if (m->num_entities == R*C/2) { warning(ENTITIES_LIMIT); return;}
	if (a->pos.x > R || a->pos.y > C) { warning(OUT_OF_BOUNDS); return; }
	
	m->num_entities++;
	m->entities[m->num_entities-1] = *a;
	m->map[a->pos.x][a->pos.y] = a->type;
}

void kill_entity (unsigned int x, unsigned int y, Map *m) {
	bool entity_found = false;

	for (unsigned int i = 0; i < m->num_entities; i++) {
		if (m->entities[i].pos.x == x)
			if (m->entities[i].pos.y == y){
				entity_found = true;
				//for loop moving the next entity
				//to the current index
				for (unsigned int j = i; j < (m->num_entities-1); j++) {
					m->entities[j] = m->entities[j+1];
				}
				m->map[x][y] = ' ';
				m->num_entities--;

			}
	}
	if (!entity_found) { warning(ENTITY_NOT_FOUND); return; }
	
	m->num_entities--;
}

void print_entities (Map *m) {
	printf("Entities: [");
	for (unsigned int i = 0; i < m->num_entities; i++) {
		printf(" %c", m->entities[i].type);
	}
	printf(" ]\n");
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
			printf("%c.", map[i][j]);
		}
		printf("|\n");
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
	Entity ent1 = init_entity(Rabbit, 1, 1);
	Entity ent2 = init_entity(Fox, 4, 4);
	Entity ent3 = init_entity(Grass, 5, 4);
	Entity ent4 = init_entity(Fox, 10, 5);
	Entity ent5 = init_entity(Grass, 2, 6);
	init_map(R, C, &map);
	place_entity(&ent1, &map);
	place_entity(&ent2, &map);
	place_entity(&ent3, &map);
	place_entity(&ent4, &map);
	place_entity(&ent5, &map);
	draw_map(R, C, map.map);
	printf("\n");
	
	print_entities(&map);

	kill_entity(1, 1, &map);


	print_entities(&map);

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