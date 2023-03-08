#include <stdbool.h>

#ifndef SOLVER_OPTIONS
#define SOLVER_OPTIONS

#define PROGRAM_VERSION "C-DFS-maze-solver 1.0"
#define ARGS_DOC         "MAZE_FILE HEIGHT WIDTH"
#define PROGRAM_DOC     "documentation for your cool application :)"

#define DEFAULT_WIDTH   7
#define DEFAULT_HEIGHT  7

#define NEW_LINE 1
#define NULL_BYTE 1

enum args_errors {NO_ERROR, BAD_SIZE};

struct arguments
{
    char *file_path;
    char **map;
    int height;
    int width;
};


/* --- args_handler.c --- */
void args_handler(int ac, char **av, struct arguments *arguments);

#endif /* --- SOLVER_OPTIONS --- */