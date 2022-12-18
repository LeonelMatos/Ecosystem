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

typedef enum {
	UP = 100,
	DOWN,
	LEFT,
	RIGHT
} Direction;

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
		if (nread == -1 && errno != EAGAIN) kill("read");
	}

	while ((c = getchar()) != '\n' && c != '\0' && c != EOF) { }

	return input;
}

void warning(const Warning w) {
	printf(B_RED "\nWarning: %s\n", warning_to_string(w));
	reset_color();
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

void kill_entity (Map *m, unsigned int x, unsigned int y) {
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
}

/// @brief Returns the index of a given entity at the map array
/// @param m map pointer
/// @param entity entity pointer
/// @return index of the entity. -1 if not found
int get_index (Map *m, Entity *entity) {
	printf("num_entities: %d\n", m->num_entities);
	for (unsigned int i = 0; i < m->num_entities; i++) {
		printf("\nSearching entity %d at (%d, %d)", i, m->entities[i].pos.x, m->entities[i].pos.y);
		if (m->entities[i].pos.x == entity->pos.x) {
			printf("<-x");
			if (m->entities[i].pos.y == entity->pos.y) {
				printf("+y\n");
				return i;
			}

		}
	}
	warning(ENTITY_NOT_FOUND); return -1; 
	/// @todo Still broken. Figure it out idk.
}

/// @brief Receives an entity in the map and moves it to a given position
/// @param m map pointer
/// @param entity entity pointer
/// @param x position x
/// @param y position y
void move_entity (Map *m, Entity *entity, unsigned int x, unsigned int y) {
	int index = get_index(m, entity);
	if (index == -1) { warning(ENTITY_NOT_FOUND); return; }

	m->map[entity->pos.x][entity->pos.y] = ' ';

	m->entities[index].pos.x = x;
	m->entities[index].pos.y = y;

	m->map[x][y] = entity->type;

}

void move_direction (Map *m, Entity *entity, Direction dir) {
	switch (dir) {
		case UP:
			move_entity (m, entity, entity->pos.x + 1, entity->pos.y);
			break;
		case DOWN:
			move_entity (m, entity, entity->pos.x - 1, entity->pos.y);
			break;
		case LEFT:
			move_entity(m, entity, entity->pos.x, entity->pos.y - 1);
			break;
		case RIGHT:
			move_entity(m, entity, entity->pos.x, entity->pos.y + 1);
			break;
		default:
			warning(WRONG_DIRECTION);
	}

	/// @bug ENTITY_NOT_FOUND warning at get_index. Check if it gets the correct position.
}

void print_entities (Map *m) {
	printf(BLU "Entities: [");
	for (unsigned int i = 0; i < m->num_entities; i++) {
		printf(" %c@(%d, %d);", m->entities[i].type, m->entities[i].pos.x, m->entities[i].pos.y);
	}
	printf(" ]\n");
	reset_color();
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
	
	for (int i = 0; i < ticks; i++) {
		
		sleep(time_scale);
	}

}

/*MAIN*/

int main () {

	int activeRun = 1;

	Map map;
	Entity ent1 = init_entity(Rabbit, 1, 1);
	Entity ent2 = init_entity(Fox, 4, 4);
	
	init_map(R, C, &map);
	place_entity(&ent1, &map);
	place_entity(&ent2, &map);

	draw_map(R, C, map.map);


	for (int i = 0; i < 5; i++) {
		print_entities(&map);
		move_direction(&map, &ent2, RIGHT);
		draw_map(R, C, map.map);
	}



	while(activeRun) {
		
		//simulate();
		print_entities(&map);

		if (read_key() == 'q'){
			printf("Exiting...");
			break;
		}
		

	}

	printf("\n");
	return 0;
}
