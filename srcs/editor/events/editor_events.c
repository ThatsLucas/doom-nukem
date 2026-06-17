/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:50:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/06/17 12:06:46 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "Game.h"

/* Add text to the selected input if there is any */
static void handle_input(t_editor *editor, char *text)
{
	if (!editor->selected)
		return ;
	if (ft_strlen(editor->selected->text) + ft_strlen(text) < sizeof(editor->selected->text))
		ft_strlcat(editor->selected->text, text, sizeof(editor->selected->text));

	return ;
}

void    print_map(t_map *map)
{
    int i;
    int j;

    printf("==========\n==== VERTICES ====\n");
    i = 0;
    while (i < map->num_vertices)
    {
        printf("v%d:    %f; %f\n", i, map->vertices[i].x, map->vertices[i].y);
        i++;
    }
    printf("==== WALLS ====\n");
    i = 0;
    while (i < map->num_walls)
    {
        printf("w%d:    v1=%d v2=%d | next_sector=%d mirror=%d length=%f alpha=%f\n",
            i, map->walls[i].v1, map->walls[i].v2,
            map->walls[i].next_sector, map->walls[i].mirror,
            map->walls[i].length, map->walls[i].alpha);
        printf("       tex_mid=%d tex_upper=%d tex_lower=%d\n",
            map->walls[i].tex_mid, map->walls[i].tex_upper,
            map->walls[i].tex_lower);
        i++;
    }
    printf("==== SECTORS ====\n");
    i = 0;
    while (i < map->num_sectors)
    {
        printf("s%d:    num_walls=%d light=%d\n",
            i, map->sectors[i].num_walls, map->sectors[i].light_level);
        printf("       floor_tex=%d ceil_tex=%d sky_tex=%d\n",
            map->sectors[i].floor_tex, map->sectors[i].ceil_tex,
            map->sectors[i].sky_tex);
        printf("       floor_plane: a=%f b=%f c=%f d=%f\n",
            map->sectors[i].floor_plane.a, map->sectors[i].floor_plane.b,
            map->sectors[i].floor_plane.c, map->sectors[i].floor_plane.d);
        printf("       ceil_plane:  a=%f b=%f c=%f d=%f\n",
            map->sectors[i].ceil_plane.a, map->sectors[i].ceil_plane.b,
            map->sectors[i].ceil_plane.c, map->sectors[i].ceil_plane.d);
        printf("       walls: [");
        j = 0;
        while (j < map->sectors[i].num_walls)
        {
            printf("%d", map->sectors[i].walls[j]);
            if (j < map->sectors[i].num_walls - 1)
                printf(", ");
            j++;
        }
        printf("]\n");
        i++;
    }
    printf("==== TEXTURES ====\n");
    i = 0;
    while (i < map->num_textures)
    {
        printf("t%d:    w=%d h=%d colors=%s\n",
            i, map->textures[i].w, map->textures[i].h,
            map->textures[i].colors ? "loaded" : "NULL");
        i++;
    }
    printf("================\n");
}

static float	get_input_float_ev(t_list *inputs, char *name)
{
	t_text_input	*inp;

	while (inputs)
	{
		inp = (t_text_input *)inputs->content;
		if (!ft_strncmp(inp->name, name, ft_strlen(name) + 1))
			return ((float)atof(inp->text));
		inputs = inputs->next;
	}
	return (0.0f);
}

static int	get_input_int_ev(t_list *inputs, char *name)
{
	t_text_input	*inp;

	while (inputs)
	{
		inp = (t_text_input *)inputs->content;
		if (!ft_strncmp(inp->name, name, ft_strlen(name) + 1))
			return (atoi(inp->text));
		inputs = inputs->next;
	}
	return (0);
}

static void	apply_sector_inputs(t_game *game)
{
	t_editor_properties	*props;
	t_sector			*sector;
	int					light;

	props = &game->editor->properties;
	if (props->selected_property != 3 || props->selected_sector < 0
		|| props->selected_sector >= game->editor->map->num_sectors)
		return ;
	sector = &game->editor->map->sectors[props->selected_sector];
	light = get_input_int_ev(game->editor->text_inputs, "sectors_light");
	if (light < 0)
		light = 0;
	if (light > 255)
		light = 255;
	sector->light_level = light;
	sector->floor_plane.d = get_input_float_ev(game->editor->text_inputs, "sectors_floor_z");
	sector->ceil_plane.d = get_input_float_ev(game->editor->text_inputs, "sectors_ceil_z");
}

static void handle_key(t_editor *editor, SDL_Keycode code, t_game *game)
{
	if (code == SDLK_ESCAPE)
		exit_game(game, NULL);

	if (code == SDLK_DELETE)
		clear_editor_plan(game);

	if (code == SDLK_o)
		print_map(game->editor->map);

	if (code == SDLK_RETURN || code == SDLK_KP_ENTER)
		apply_sector_inputs(game);

	if (!editor->selected)
		return ;
	if (code == SDLK_BACKSPACE && ft_strlen(editor->selected->text))
		editor->selected->text[ft_strlen(editor->selected->text) - 1] = 0;

	return ;
}

static void	check_slop_button(t_game *game, int x, int y)
{
	SDL_Rect	box;

	box.h = 35; box.w = 80; box.x = 1639; box.y = 495;
	to_responsive(game->window, &box);

	if (x > box.x && x < box.x + box.w && y > box.y && y < box.y + box.h)
		game->editor->properties.slope_fc = game->editor->properties.slope_fc == 0 ? 1 : 0;

	return ;
}

/* Handle editor events (mouse, keys, etc.) */
void	editor_events(t_game *game)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				exit_game(game, NULL);
				break ;

			case SDL_TEXTINPUT:
				handle_input(game->editor, e.text.text);
				break ;

			case SDL_KEYDOWN:
				handle_key(game->editor, e.key.keysym.sym, game);
				break ;

			case SDL_MOUSEBUTTONDOWN:
				get_selected_input(game, &game->editor->text_inputs, e.motion.x, e.motion.y);
				check_button_pressed(game, game->editor->buttons);
				if (!get_clicked_editor_button(game, e.motion.x, e.motion.y))
					plan_click(game, &e);
				get_clicked_texture(game, e.motion.x, e.motion.y);
				get_clicked_texture_button(game, e.motion.x, e.motion.y);
				check_slop_button(game, e.motion.x, e.motion.y);
				break ;

			case SDL_MOUSEBUTTONUP:
				plan_click(game, &e);
				break ;

			case SDL_MOUSEMOTION:
				plan_click(game, &e);
				break ;

			case SDL_MOUSEWHEEL:
				handle_zoom(game->editor, &e.wheel);
				break ;

			default:
				break ;
		}
	}

	return ;
}
