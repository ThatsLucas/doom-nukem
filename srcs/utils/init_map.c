#include "Raycasting/Types.h"
#include "Game.h"
#include <stdlib.h>
#include <string.h>

/*
** Labyrinthe de test en serpentin.
** Le joueur part dans la salle 0 en haut a gauche et suit un long couloir.
*/

static int init_vertices(t_map *map)
{
    map->num_vertices = 16;
    map->cap_vertices = 16;
    map->vertices = malloc(sizeof(t_vect2) * map->num_vertices);
    if (!map->vertices)
        return (-1);
    map->vertices[0] = (t_vect2){0.0f, 0.0f};
    map->vertices[1] = (t_vect2){8.0f, 0.0f};
    map->vertices[2] = (t_vect2){16.0f, 0.0f};
    map->vertices[3] = (t_vect2){24.0f, 0.0f};
    map->vertices[4] = (t_vect2){0.0f, 8.0f};
    map->vertices[5] = (t_vect2){8.0f, 8.0f};
    map->vertices[6] = (t_vect2){16.0f, 8.0f};
    map->vertices[7] = (t_vect2){24.0f, 8.0f};
    map->vertices[8] = (t_vect2){0.0f, 16.0f};
    map->vertices[9] = (t_vect2){8.0f, 16.0f};
    map->vertices[10] = (t_vect2){16.0f, 16.0f};
    map->vertices[11] = (t_vect2){24.0f, 16.0f};
    map->vertices[12] = (t_vect2){0.0f, 24.0f};
    map->vertices[13] = (t_vect2){8.0f, 24.0f};
    map->vertices[14] = (t_vect2){16.0f, 24.0f};
    map->vertices[15] = (t_vect2){24.0f, 24.0f};
    return (0);
}

static void set_wall(t_wall *w, int v1, int v2, int next_sector,
                     int tex_mid, int tex_upper, int tex_lower, float alpha)
{
    w->v1 = v1;
    w->v2 = v2;
    w->next_sector = next_sector;
    w->tex_mid = tex_mid;
    w->tex_upper = tex_upper;
    w->tex_lower = tex_lower;
    w->alpha = alpha;
}

static int init_walls(t_map *map)
{
    map->num_walls = 36;
    map->cap_walls = 36;
    map->walls = malloc(sizeof(t_wall) * map->num_walls);
    if (!map->walls)
        return (-1);

    set_wall(&map->walls[0], 0, 1, -1, 0, -1, -1, 1.0f);
    set_wall(&map->walls[1], 1, 5, 1, 0, -1, -1, 0.5f);
    set_wall(&map->walls[2], 5, 4, -1, 0, -1, -1, 1.0f);
    set_wall(&map->walls[3], 4, 0, -1, 0, -1, -1, 1.0f);

    set_wall(&map->walls[4], 1, 2, -1, 1, -1, -1, 1.0f);
    set_wall(&map->walls[5], 2, 6, 2, 1, 1, 1, 1.0f);
    set_wall(&map->walls[6], 6, 5, -1, 1, -1, -1, 1.0f);
    set_wall(&map->walls[7], 5, 1, 0, 1, -1, -1, 0.9f);

    set_wall(&map->walls[8], 2, 3, -1, 2, -1, -1, 1.0f);
    set_wall(&map->walls[9], 3, 7, -1, 2, -1, -1, 1.0f);
    set_wall(&map->walls[10], 7, 6, 3, 2, 2, 2, 1.0f);
    set_wall(&map->walls[11], 6, 2, 1, 2, 1, 1, 0.9f);

    set_wall(&map->walls[12], 6, 7, 2, 3, 2, 2, 0.9f);
    set_wall(&map->walls[13], 7, 11, -1, 3, -1, -1, 1.0f);
    set_wall(&map->walls[14], 11, 10, -1, 3, -1, -1, 1.0f);
    set_wall(&map->walls[15], 10, 6, 4, 3, 3, 3, 1.0f);

    set_wall(&map->walls[16], 5, 6, -1, 0, -1, -1, 1.0f);
    set_wall(&map->walls[17], 6, 10, 3, 0, 0, 0, 1.0f);
    set_wall(&map->walls[18], 10, 9, -1, 0, -1, -1, 1.0f);
    set_wall(&map->walls[19], 9, 5, 5, 0, 0, 0, 1.0f);

    set_wall(&map->walls[20], 4, 5, -1, 1, -1, -1, 1.0f);
    set_wall(&map->walls[21], 5, 9, 4, 1, 1, 1, 1.0f);
    set_wall(&map->walls[22], 9, 8, 6, 1, 1, 1, 1.0f);
    set_wall(&map->walls[23], 8, 4, -1, 1, -1, -1, 1.0f);

    set_wall(&map->walls[24], 8, 9, 5, 2, 2, 2, 1.0f);
    set_wall(&map->walls[25], 9, 13, 7, 2, 2, 2, 1.0f);
    set_wall(&map->walls[26], 13, 12, -1, 2, -1, -1, 1.0f);
    set_wall(&map->walls[27], 12, 8, -1, 2, -1, -1, 1.0f);

    set_wall(&map->walls[28], 9, 10, -1, 3, -1, -1, 1.0f);
    set_wall(&map->walls[29], 10, 14, 8, 3, 3, 3, 1.0f);
    set_wall(&map->walls[30], 14, 13, -1, 3, -1, -1, 1.0f);
    set_wall(&map->walls[31], 13, 9, 6, 3, 3, 3, 0.9f);

    set_wall(&map->walls[32], 10, 11, -1, 0, -1, -1, 1.0f);
    set_wall(&map->walls[33], 11, 15, -1, 0, -1, -1, 1.0f);
    set_wall(&map->walls[34], 15, 14, -1, 0, -1, -1, 1.0f);
    set_wall(&map->walls[35], 14, 10, 7, 0, 0, 0, 0.9f);

    for (int i = 0; i < map->num_walls; i++)
        map->walls[i].length = dist_vect(map->vertices[map->walls[i].v1], map->vertices[map->walls[i].v2]);
    return (0);
}

static int init_one_sector(t_sector *sec, int *wall_ids, int num_walls,
                           t_plane floor_p, t_plane ceil_p,
                           int floor_tex, int ceil_tex, int light)
{
    sec->num_walls = num_walls;
    sec->walls = malloc(sizeof(int) * num_walls);
    if (!sec->walls)
        return (-1);
    for (int i = 0; i < num_walls; i++)
        sec->walls[i] = wall_ids[i];
    sec->floor_plane = floor_p;
    sec->ceil_plane = ceil_p;
    sec->floor_tex = floor_tex;
    sec->ceil_tex = ceil_tex;
    sec->sky_tex = -1;
    sec->light_level = light;
    return (0);
}

static int init_sectors(t_map *map)
{
    map->num_sectors = 9;
    map->cap_sectors = 9;
    map->sectors = malloc(sizeof(t_sector) * map->num_sectors);
    if (!map->sectors)
        return (-1);

    if (init_one_sector(&map->sectors[0], (int[]){0, 1, 2, 3}, 4,
                        (t_plane){0, 0, 1, 0}, (t_plane){0, 0, 1, -4}, 0, 1, 200) == -1)
        return (-1);
    if (init_one_sector(&map->sectors[1], (int[]){4, 5, 6, 7}, 4,
                        (t_plane){0, 0, 1, 0}, (t_plane){0, 0, 1, -4}, 0, 1, 180) == -1)
        return (-1);
    if (init_one_sector(&map->sectors[2], (int[]){8, 9, 10, 11}, 4,
                        (t_plane){0, 0, 1, 0}, (t_plane){0, 0, 1, -4}, 1, 0, 160) == -1)
        return (-1);
    if (init_one_sector(&map->sectors[3], (int[]){12, 13, 14, 15}, 4,
                        (t_plane){0, 0, 1, 0}, (t_plane){0, 0, 1, -4}, 1, 0, 140) == -1)
        return (-1);
    if (init_one_sector(&map->sectors[4], (int[]){16, 17, 18, 19}, 4,
                        (t_plane){0, 0, 1, 0}, (t_plane){0, 0, 1, -4}, 2, 3, 120) == -1)
        return (-1);
    if (init_one_sector(&map->sectors[5], (int[]){20, 21, 22, 23}, 4,
                        (t_plane){0, 0, 1, 0}, (t_plane){0, 0, 1, -4}, 2, 3, 110) == -1)
        return (-1);
    if (init_one_sector(&map->sectors[6], (int[]){24, 25, 26, 27}, 4,
                        (t_plane){0, 0, 1, 0}, (t_plane){0, 0, 1, -4}, 3, 2, 90) == -1)
        return (-1);
    if (init_one_sector(&map->sectors[7], (int[]){28, 29, 30, 31}, 4,
                        (t_plane){0, 0, 1, 0}, (t_plane){0, 0, 1, -4}, 3, 2, 80) == -1)
        return (-1);
    if (init_one_sector(&map->sectors[8], (int[]){32, 33, 34, 35}, 4,
                        (t_plane){0, 0, 1, 0}, (t_plane){0, 0, 1, -4}, 0, 1, 70) == -1)
        return (-1);
    return (0);
}

t_map *init_test_map(void)
{
    t_map *map;

    map = calloc(1, sizeof(t_map));
    if (!map)
        return (NULL);
    if (init_vertices(map) == -1 || init_walls(map) == -1 || init_sectors(map) == -1)
    {
        free_map(map);
        return (NULL);
    }
    return (map);
}

void free_map(t_map *map)
{
    if (!map)
        return;
    for (int i = 0; i < map->num_sectors; i++)
        free(map->sectors[i].walls);
    for (int y = 0; y < map->num_textures; y++)
        free(map->textures[y].colors);
    free(map->sectors);
    free(map->walls);
    free(map->vertices);
    free(map->textures);
    free(map);
}
