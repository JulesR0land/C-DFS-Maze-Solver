#include <stddef.h>
#include <stdio.h>

#include "options.h"
#include "solver.h"

int main(int ac, char **av)
{
    struct arguments args;
    char **map = NULL;

    args_handler(ac, av, &args);
    map = solver(args.map, (pos_t){args.height, args.width});

    if (!map) {
        printf("Map can't be solved.\n");
    } else {
        print_maze(map, (pos_t){args.height, args.width});
        free_map(map, args.height);
    }

    return 0;
}