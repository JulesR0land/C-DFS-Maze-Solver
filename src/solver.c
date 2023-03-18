#include <stdlib.h>
#include <stdbool.h>

#include "solver.h"

#include <stdio.h>

static bool check_pos(pos_t pos, pos_t size)
{
    if (pos.y < 0 || pos.y >= size.y)
        return false;
    if (pos.x < 0 || pos.x >= size.x)
        return false;
    return true;
}

static bool check_straight(char **map, pos_t size, intersection_t *inter)
{
    pos_t new_pos = inter->pos;

    new_pos.x += CARDS_POS[inter->direction].x;
    new_pos.y += CARDS_POS[inter->direction].y;
    if (!check_pos(new_pos, size) || map[new_pos.y][new_pos.x] != ' ')
        return false;

    new_pos = inter->pos;
    new_pos.x += CARDS_POS[(inter->direction + 1) % 4].x;
    new_pos.y += CARDS_POS[(inter->direction + 1) % 4].y;
    if (!check_pos(new_pos, size) || map[new_pos.y][new_pos.x] != 'X')
        return false;

    new_pos = inter->pos;
    new_pos.x += CARDS_POS[(inter->direction + 3) % 4].x;
    new_pos.y += CARDS_POS[(inter->direction + 3) % 4].y;
    if (!check_pos(new_pos, size) || map[new_pos.y][new_pos.x] != 'X')
        return false;

    return true;
}

bool straight_line(char **map, pos_t size, intersection_t *inter)
{
    while (check_straight(map, size, inter)) {
        map[inter->pos.y][inter->pos.x] = '*';
        inter->pos.x += CARDS_POS[inter->direction].x;
        inter->pos.y += CARDS_POS[inter->direction].y;
    }

    return next_depth(map, size, inter);
}

bool next_depth(char **map, pos_t size, intersection_t *inter)
{
    pos_t new_pos = inter->pos;

    map[inter->pos.y][inter->pos.x] = '*';
    for (int i = 0; i < 4; i++) {
        new_pos.x += CARDS_POS[i].x;
        new_pos.y += CARDS_POS[i].y;
        if (check_pos(new_pos, size)) {
            if (map[new_pos.y][new_pos.x] == 'F')
                return true;
            if (map[new_pos.y][new_pos.x] == ' ') {
                inter->next = malloc(sizeof(intersection_t));
                inter->next->pos = new_pos;
                inter->next->steps_nb = 0;
                inter->next->direction = i;
                inter->next->next = NULL;
                if (straight_line(map, size, inter->next))
                    return true;
                free(inter->next);
                inter->next = NULL;
            }
        }
        new_pos = inter->pos;
    }

    return false;
}

static void draw_path(char **map, intersection_t *inter) {
    pos_t curr_pos = inter->pos;

    for (; inter->next; inter = inter->next) {
        while (curr_pos.x != inter->next->pos.x || curr_pos.y != inter->next->pos.y) {
            map[curr_pos.y][curr_pos.x] = '.';
            curr_pos.x += CARDS_POS[inter->next->direction].x;
            curr_pos.y += CARDS_POS[inter->next->direction].y;
        }
    }
    map[inter->pos.y][inter->pos.x] = '.';
}

static void free_inter(intersection_t *inter)
{
    intersection_t *past = NULL;

    while (inter) {
        past = inter;
        inter = inter->next;
        free(past);
    }
}

static pos_t get_start(char **map, pos_t size)
{
    for (int i = 0; i < size.y; i++)
        for (int j = 0; j < size.x; j++)
            if (map[i][j] == 'S')
                return (pos_t){j, i};
    return (pos_t){-1, -1};
}

char **solver(char **map, pos_t size)
{
    pos_t start;
    intersection_t *inter = malloc(sizeof(intersection_t));

    size.x = size.x * 2 + 1;
    size.y = size.y * 2 + 1;

    start = get_start(map, size);
    if (start.x < 0)
        return NULL;

    inter->pos = start;

    if (next_depth(map, size, inter)) {
        draw_path(map, inter);
        free_inter(inter);
        map[start.y][start.x] = 'S';
        return map;
    }
    free_inter(inter);
    free_map(map, size.y);
    return NULL;
}