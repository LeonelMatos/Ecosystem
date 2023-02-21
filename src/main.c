/**
 * @file main.c
 * @author LeonelMatos [LeonelMatos's Github](https://github.com/LeonelMatos)
 * @version 0.0.4
 * @date 2023-01-30
 * @copyright Copyright (c) 2023
 */


/*INCLUDE/DEFINE*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "entity.h"
#include "warning.h"

#define R 25 ///Rows of the map
#define C 30 ///Columns of the map

#define TREE_FREQ 10 ///Spawn tree frequency (DEFAULT:20)

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


/*ENTITIES*/

#include "entities/rabbit.h"


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


/*ENTITY*/

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
	int entity_found = 0;

	for (unsigned int i = 0; i < m->num_entities; i++) {
		if (m->entities[i].pos.x == x)
			if (m->entities[i].pos.y == y){
				entity_found = 1;
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
int get_index (Entity *entity, Map *m) {
	printf("num_entities: %d\n", m->num_entities);
	for (unsigned int i = 0; i < m->num_entities; i++) {
		printf("\nSearching entity %d at (%d, %d)", i, m->entities[i].pos.x, m->entities[i].pos.y);
		printf(" [x: %d vs. %d] ", m->entities[i].pos.x, entity->pos.x);
		if (m->entities[i].pos.x == entity->pos.x) {
			printf("<-x");
			printf(" %d vs. %d", m->entities[i].pos.y, entity[i].pos.y);
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
void move_entity (Entity *entity, unsigned int x, unsigned int y, Map *m) {
	int index = get_index(entity, m);
	if (index == -1) { warning(ENTITY_NOT_FOUND); return; }

	m->map[entity->pos.x][entity->pos.y] = ' ';

	m->entities[index].pos.x = x;
	m->entities[index].pos.y = y;

	m->map[x][y] = entity->type;

}

void move_direction (Entity *entity, Direction dir, Map *m) {
	switch (dir) {
		case UP:
			move_entity (entity, entity->pos.x + 1, entity->pos.y, m);
			break;
		case DOWN:
			move_entity (entity, entity->pos.x - 1, entity->pos.y, m);
			break;
		case LEFT:
			move_entity(entity, entity->pos.x, entity->pos.y - 1, m);
			break;
		case RIGHT:
			move_entity(entity, entity->pos.x, entity->pos.y + 1, m);
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


/*ENTITY_BEHAVIOUR*/

///@brief Nearby surrounding of current entity
char near[8];

///@brief Initiates the near array
///@param array
void init_near(char array[]) {
	for (int i = 0; i < 8; i++)
		array[i] = ' ';
}

///@brief Saves to the near array all entities near the given one
///@param entity current entity to check near
///@param map 
void check_near (Entity *entity, Map *map) {
	///All positions near the entity

	if (entity->pos.x != 0) {
		if (entity->pos.y != 0)
    		near[0] = map->map[entity->pos.x-1][entity->pos.y-1];   //<^
    	near[1] = map->map[entity->pos.x-1][entity->pos.y];     //^
		if (entity->pos.y != C)
    		near[2] = map->map[entity->pos.x-1][entity->pos.y+1];   //^>
	}
	if (entity->pos.y != 0)
    	near[3] = map->map[entity->pos.x][entity->pos.y-1];     //<
	if (entity->pos.y != C)
    	near[4] = map->map[entity->pos.x][entity->pos.y+1];     //>

	if (entity->pos.x != R) {
		if (entity->pos.y != 0)
			near[5] = map->map[entity->pos.x+1][entity->pos.y-1];   //<v
		near[6] = map->map[entity->pos.x+1][entity->pos.y];     //v
		if (entity->pos.y != C)
			near[7] = map->map[entity->pos.x+1][entity->pos.y+1];   //v>
	}
}

///@brief prints a small map of nearby entities
///@param entity current entity
///@param map 
void print_near_entities(Entity *entity, Map *map) {
	check_near(entity, map);
	printf(B_GRN "Entities near %c[%d, %d]\n", entity->type, entity->pos.x, entity->pos.y);
	reset_color();
	for (int i = 0; i < 3; i++) 
		printf("[%c]", near[i]);
	printf("\n[%c]", near[3]);
	printf(B_GRN"[%c]", entity->type);
	reset_color();
	printf("[%c]\n", near[4]);
	for (int i = 5; i < 8; i++)
		printf("[%c]", near[i]);
	printf("\n\n");

}


/*INIT*/
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

void generate_trees (const int freq, Map *map) {
	srand(time(0));
	Entity entity;
	int r = rand() % freq;
	for (unsigned int x = 0; x < R; x++)
		for (unsigned int y = 0; y < C; y++) {
			if (map->map[x][y] == ' ') {
				r = rand() % freq;
				if (r == 1) {
					entity = init_entity(Tree, x, y);
					place_entity(&entity, map);
				}
				else if (r == 2) {
					entity = init_entity(Grass, x, y);
					place_entity(&entity, map);
				}
			}
		}
}

void draw_map(int r, int c, char map[r][c], int repr) {
	
	printf(".");
	for (int i = 0; i < c; i++) {
		printf("_.");
	}
	printf("\n");

	for (int i = 0; i < r; i++) {
		printf("|");
		for (int j = 0; j < c; j++) {
			if (repr == 1) {
				printf("%s", entity_image(map[i][j]));
			} 
			else {
			printf("%s", entity_color(map[i][j]));
			printf("%c", map[i][j]);
			reset_color();
			}
		printf(" ");
		}
		if (repr == 0)
			printf("|");
		printf("\n");
	}
	printf(".");
	for (int i = 0; i < c; i++) {
		printf("_.");
	}
	printf("\n\n");
}


/*MAIN*/

int main (int argc, char *argv[]) {

	int activeRun = 1;
	int repr = 0;

	if (argc > 1){
		switch (argv[1][0]) {
			case '0':
				repr = 0;
				break;
			case '1':
				repr = 1;
				break;
			default:
				warning(INVALID_ARGUMENT);
		}
	}

	Map map;
	Entity ent1 = init_entity(Rabbit, 1, 1);
	Entity ent2 = init_entity(Fox, 0, 0);
	Entity ent3 = init_entity(Fox, 1, 0);
	
	init_map(R, C, &map);
	init_near(near);
	place_entity(&ent1, &map);
	place_entity(&ent2, &map);
	place_entity(&ent3, &map);

	generate_trees(TREE_FREQ, &map);

	draw_map(R, C, map.map, repr);

	///\bug Last implementation broke the output of draw_map
	print_near_entities(&ent2, &map);

	//print_entities(&map);

/*
	for (int i = 0; i < 5; i++) {
		print_entities(&map);
		move_direction(&map, &ent2, RIGHT);
		draw_map(R, C, map.map);
	}


*/
	while(activeRun) {
		
		if (read_key() == 'q'){
			printf("Exiting...");
			break;
		}
		

	}

	printf("\n");
	return 0;
}
