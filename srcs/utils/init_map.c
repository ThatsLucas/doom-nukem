#include "Raycasting/Types.h"
#include "Game.h"
#include <stdlib.h>
#include <string.h>

/*
**  Map de test — une seule grande salle plate
**
**   (0,0)──────────────(50,0)
**     │                   │
**     │                   │
**     │   Secteur 0       │
**     │   sol z=0         │
**     │   plaf z=4        │
**     │                   │
**     │                   │
**   (0,50)─────────────(50,50)
*/

static int	init_vertices(t_map *map)
{
	map->num_vertices = 4;
	map->cap_vertices = 4;
	map->vertices = malloc(sizeof(t_vect2) * map->num_vertices);
	if (!map->vertices)
		return (-1);
	map->vertices[0] = (t_vect2){  0.0f,   0.0f };
	map->vertices[1] = (t_vect2){ 50.0f,   0.0f };
	map->vertices[2] = (t_vect2){ 50.0f,  50.0f };
	map->vertices[3] = (t_vect2){  0.0f,  50.0f };
	return (0);
}

static void	set_wall(t_wall *w, int v1, int v2, int next_sector,
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

static int	init_walls(t_map *map)
{
	map->num_walls = 4;
	map->cap_walls = 4;
	map->walls = malloc(sizeof(t_wall) * map->num_walls);
	if (!map->walls)
		return (-1);

	/* ── Secteur 0 : polygone fermé [0→1→2→3→0] ── */
	/*          v1  v2  next  mid  upper  lower       */
	set_wall(&map->walls[0], 0, 1, -1, 0, -1, -1, 1.0f);  /* nord  */
	set_wall(&map->walls[1], 1, 2, -1, 0, -1, -1, 1.0f);  /* est   */
	set_wall(&map->walls[2], 2, 3, -1, 0, -1, -1, 1.0f);  /* sud   */
	set_wall(&map->walls[3], 3, 0, -1, 0, -1, -1, 1.0f);  /* ouest */

	for (int i = 0; i < map->num_walls; ++i)
		map->walls[i].length = dist_vect(
			map->vertices[map->walls[i].v1],
			map->vertices[map->walls[i].v2]);

	return (0);
}

static int	init_one_sector(t_sector *sec, int *wall_ids, int num_walls,
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

static int	init_sectors(t_map *map)
{
	map->num_sectors = 1;
	map->cap_sectors = 1;
	map->sectors = malloc(sizeof(t_sector) * map->num_sectors);
	if (!map->sectors)
		return (-1);

	/* Secteur 0 : sol z=0, plafond z=4, plats */
	if (init_one_sector(&map->sectors[0],
		(int[]){0, 1, 2, 3}, 4,
		(t_plane){0, 0, 1,  0},   /* sol plat z=0  */
		(t_plane){0, 0, 1, -4},   /* plaf plat z=4 */
		0, 1, 200) == -1)
		return (-1);

	return (0);
}

t_map	*init_test_map(void)
{
	t_map	*map;

	map = calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	if (init_vertices(map) == -1
		|| init_walls(map) == -1
		|| init_sectors(map) == -1)
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
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
