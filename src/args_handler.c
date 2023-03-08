#include <argp.h>
#include <stdlib.h>

#include "options.h"

static char **get_map(struct arguments *args)
{
    size_t array_height = args->height * 2 + 1;
    size_t array_width = args->width * 2 + 1 + NEW_LINE + NULL_BYTE;
    size_t len = array_width;
    FILE *stream = fopen(args->file_path, "r");
    char **map = malloc(sizeof(char *) * array_height);

    if (stream == NULL) {
        perror("fopen");
        return NULL;
    }

    for (size_t i = 0; i < array_height; i++) {
        map[i] = malloc(sizeof(char) * array_width);
        if (getline(&map[i], &len, stream) < 0) {
            return NULL;
        }
        if (len != array_width) {
            return NULL;
        }
    }
    return map;
}

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch(key) {
        case ARGP_KEY_ARG:
            if (state->arg_num > 3)
                argp_usage(state);
            switch (state->arg_num) {
                case 0:
                    arguments->file_path = arg;
                    break;
                case 1:
                    arguments->height = atoi(arg);
                    if (arguments->height < 3)
                        argp_usage(state);
                    break;
                case 2:
                    arguments->width = atoi(arg);
                    if (arguments->width < 3)
                        argp_usage(state);
                    break;
                default:
                    argp_usage(state);
            }
            break;
        case ARGP_KEY_END:
            arguments->map = get_map(arguments);
            if (arguments->map == NULL)
                argp_usage(state);
            if (state->arg_num < 3)
                argp_usage(state);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

void args_handler(int ac, char **av, struct arguments *arguments)
{
    struct argp argp = {
        NULL,
        parse_opt,
        ARGS_DOC,
        PROGRAM_DOC,
        NULL, NULL, NULL
    };

    argp_parse(&argp, ac, av, 0, 0, arguments);
}