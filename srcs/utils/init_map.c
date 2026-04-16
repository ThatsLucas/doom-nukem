#include "Raycasting/Types.h"
#include "Game.h"
#include <stdlib.h>
#include <string.h>

/*
**  Map de test — vue du dessus (0,0 = haut gauche, Y vers le bas)
**
**   (0,0)────────(6,0)────────(12,0)
**     │            │              │
**     │  Secteur 0 │  Secteur 1   │
**     │  sol z=0   │  sol z=0     │
**     │  plaf z=4  │  plaf z=4    │
**     │            │              │
**   (0,4)────────(6,4)────────(12,4)
**                  │              │
**                  │  Secteur 2   │
**                  │  sol z=1     │
**                  │  plaf z=3    │
**                  │              │
**                (6,8)────────(12,8)
**
**  Portails :
**    Secteur 0 ←→ Secteur 1  (murs 1 et 7, vertices 1-4)
**    Secteur 1 ←→ Secteur 2  (murs 6 et 8, vertices 4-5)
**
**  Le secteur 2 a un sol plus haut et un plafond plus bas,
**  donc les portails vers lui montrent des steps (tex_upper + tex_lower).
*/

static int	init_vertices(t_map *map)
{
	map->num_vertices = 8;
	map->cap_vertices = 8;
	map->vertices = malloc(sizeof(t_vect2) * map->num_vertices);
	if (!map->vertices)
		return (-1);
	map->vertices[0] = (t_vect2){  0.0f,  0.0f };
	map->vertices[1] = (t_vect2){  6.0f,  0.0f };
	map->vertices[2] = (t_vect2){ 12.0f,  0.0f };
	map->vertices[3] = (t_vect2){  0.0f,  4.0f };
	map->vertices[4] = (t_vect2){  6.0f,  4.0f };
	map->vertices[5] = (t_vect2){ 12.0f,  4.0f };
	map->vertices[6] = (t_vect2){  6.0f,  8.0f };
	map->vertices[7] = (t_vect2){ 12.0f,  8.0f };
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
	map->num_walls = 12;
	map->cap_walls = 12;
	map->walls = malloc(sizeof(t_wall) * map->num_walls);
	if (!map->walls)
		return (-1);

	/* ── Secteur 0 : polygone fermé [0→1→4→3→0] ── */
	/*          v1  v2  next  mid  upper  lower       */
	set_wall(&map->walls[0],  0, 1,  -1,   0,   -1,  -1, 1.0f);  /* nord  (solide) */
	set_wall(&map->walls[1],  1, 4,   1,   0,   -1,  -1, 0.5f);  /* est   (portail → sec 1) */
	set_wall(&map->walls[2],  4, 3,  -1,   0,   -1,  -1, 1.0f);  /* sud   (solide) */
	set_wall(&map->walls[3],  3, 0,  -1,   0,   -1,  -1, 1.0f);  /* ouest (solide) */

	/* ── Secteur 1 : polygone fermé [1→2→5→4→1] ── */
	set_wall(&map->walls[4],  1, 2,  -1,   1,   -1,  -1, 1.0f);  /* nord  (solide) */
	set_wall(&map->walls[5],  2, 5,  -1,   1,   -1,  -1, 1.0f);  /* est   (solide) */
	set_wall(&map->walls[6],  5, 4,   2,   1,    2,   2, 1.0f);   /* sud   (portail → sec 2) */
	set_wall(&map->walls[7],  4, 1,   0,   1,   -1,  -1, 0.9f);  /* ouest (portail → sec 0) */

	/* ── Secteur 2 : polygone fermé [4→5→7→6→4] ── */
	set_wall(&map->walls[8],  4, 5,   1,   3,    2,   2, 1.0f);   /* nord  (portail → sec 1) */
	set_wall(&map->walls[9],  5, 7,  -1,   3,   -1,  -1, 1.0f);  /* est   (solide) */
	set_wall(&map->walls[10], 7, 6,  -1,   3,   -1,  -1, 1.0f);  /* sud   (solide) */
	set_wall(&map->walls[11], 6, 4,  -1,   3,   -1,  -1, 1.0f);  /* ouest (solide) */

	for(int i = 0; i < map->num_walls; ++i)
		map->walls[i].length = dist_vect(map->vertices[map->walls[i].v1], map->vertices[map->walls[i].v2]);

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
	map->num_sectors = 3;
	map->cap_sectors = 3;
	map->sectors = malloc(sizeof(t_sector) * map->num_sectors);
	if (!map->sectors)
		return (-1);

	/* Secteur 0 : sol z=0, plafond z=4 */
	if (init_one_sector(&map->sectors[0],
		(int[]){0, 1, 2, 3}, 4,
		(t_plane){0, 0, 1,  0},       /* sol plat z=0   */
		(t_plane){0, 0, 1, -4},       /* plaf plat z=4  */
		0, 1, 200) == -1)
		return (-1);

	/* Secteur 1 : sol z=0, plafond z=4 (même niveau que secteur 0) */
	if (init_one_sector(&map->sectors[1],
		(int[]){4, 5, 6, 7}, 4,
		(t_plane){-0.2f, 0, 1, 0.6f},   /* sol : z=0 à x=6, monte de 0.1 par unité de x */
		(t_plane){0, 0, 1, -4},       /* plaf plat z=4  */
		0, 1, 100) == -1)
		return (-1);

	/* Secteur 2 : sol z=1, plafond z=3 (plus étroit → steps visibles) */
	if (init_one_sector(&map->sectors[2],
		(int[]){8, 9, 10, 11}, 4,
		(t_plane){0, 0, 1, -1},       /* sol plat z=1   */
		(t_plane){0.2f, 0, 1, -3.5f},   /* z = -0.1*x + 3.5 */
		2, 3, 25) == -1)
		return (-1);

	return (0);
}

/*
** Crée et remplit une map de test complète.
** Retourne NULL en cas d'erreur d'allocation.
**
** Textures utilisées :
**   0 = murs secteur 0 + sol secteurs 0 et 1
**   1 = murs secteur 1 + plafond secteurs 0 et 1
**   2 = steps des portails + sol et plafond secteur 2
**   3 = murs secteur 2
**
** Les SDL_Surface et text_colors doivent être
** chargées séparément avant le rendu.
*/
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
