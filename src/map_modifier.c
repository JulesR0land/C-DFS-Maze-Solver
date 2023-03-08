#include <stdlib.h>

#include "solver.h"

void free_map(char **map, int height)
{
    int array_height = height * 2 + 1;

    for (int i = 0; i < array_height; i++) {
        free(map[i]);
    }
    free(map);
}