#include <stdbool.h>

#ifndef DFS_SOLVER
#define DFS_SOLVER

enum cards {NORTH, EAST, SOUTH, WEST};

typedef struct pos_s pos_t;
typedef struct intersection_s intersection_t;

struct pos_s {
    int x;
    int y;
};

struct intersection_s {
    pos_t pos;
    int steps_nb;
    int direction;
    intersection_t *next;
};

static const pos_t CARDS_POS[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};


/* --- solver.c --- */
char **solver(char **map, pos_t size);
bool next_depth(char **map, pos_t size, intersection_t *inter);
bool straight_line(char **map, pos_t size, intersection_t *inter);

/* --- maze_printer.c --- */
void print_maze(char **map, pos_t size);

/* --- map_modifier.c --- */
void free_map(char **map, int height);


#endif /* --- DFS_SOLVER --- */