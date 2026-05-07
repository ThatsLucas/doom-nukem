/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor_cache.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:08:53 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/05/07 12:35:22 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Editor.h"
#include "parser/PNG.h"
#include "Game.h"

static void	realloc_png(t_game *game, t_editor_textures *textures)
{
	if (textures->cap_textures == 0)
	{
		textures->png = calloc(8, sizeof(t_png));
		if (!textures->png)
			exit_game(game, "realloc_png: failed to realloc 1");
		textures->cap_textures = 8;
		return ;
	}
	textures->png = realloc(textures->png, textures->cap_textures * 2 * sizeof(t_png));
	if (!textures->png)
			exit_game(game, "realloc_png: failed to realloc 2");
	textures->cap_textures *= 2;

	return ;
}

static void	create_png_list(t_game *game, t_editor *editor, int fd)
{
	char	*line = NULL;
	int		i = 0;

	while ((line = get_next_line(fd)))
	{
		if (editor->textures->num_textures == editor->textures->cap_textures)
			realloc_png(game, editor->textures);

		if (ft_strncmp(&line[ft_strlen(line) - 5], ".png", 4))
			continue ;

		line[ft_strlen(line) - 1] = 0;

		editor->textures->png[i].path = ft_strjoin("assets/textures/", line);
		free(line);
		if (process_png(&editor->textures->png[i]))
		{
			editor->textures->num_textures += 1;
			i++;
		}
	}

	return ;
}

static void	init_buttons(t_game *game)
{
	t_png	s_png[3];
	char	*s_name[3] = {"button_up.png", "button_down.png", "red_cross.png"};
	t_png	png[6];
	char	*name[6] = {"cursor.png", "wall.png", "slope.png", "cursor_sel.png", "wall_sel.png", "slope_sel.png"};

	for (int i = 0; i < 3; i++)
	{
		s_png[i].path = ft_strjoin("assets/png/editor/", s_name[i]);
		if (process_png(&s_png[i]))
			game->editor->texture_selector.buttons[i] = create_image(&s_png[i], game->window->renderPTR);
		else
			exit_game(game, "editor: Can't init buttons");
		if (!game->editor->texture_selector.buttons[i])
			exit_game(game, "editor: Can't init buttons");
	}

	for (int i = 0; i < 6; i++)
	{
		png[i].path = ft_strjoin("assets/png/editor/", name[i]);
		if (process_png(&png[i]))
			game->editor->buttons_textures[i] = create_image(&png[i], game->window->renderPTR);
		else
			exit_game(game, "editor: Can't init buttons");
		if (!game->editor->buttons_textures[i])
			exit_game(game, "editor: Can't init buttons");
	}

	return ;
}

void	init_editor_cache(t_game *game)
{
	t_editor	*editor = game->editor;
	int			fd;

	fd = open("assets/textures/texture_list.txt", O_RDONLY);
	if (fd < 0)
		exit_game(game, "init_editor_cache: cant find assets/textures/texture_list.txt");
	editor->textures = calloc(1, sizeof(t_editor_textures));
	if (!editor->textures)
		exit_game(game, "Editor Cache: calloc editor textures failed");

	create_png_list(game, editor, fd);
	close(fd);

	editor->textures->textures = calloc(editor->textures->num_textures, sizeof(SDL_Texture *));
	if (!editor->textures->textures)
		exit_game(game, "Editor Cache: calloc editor textures failed 2");
	for (int i = 0; i < editor->textures->num_textures; i++)
		editor->textures->textures[i] = create_image(&editor->textures->png[i], game->window->renderPTR);

	init_buttons(game);

	ft_printf("Editor: %d textures initialized\n", editor->textures->num_textures);
	editor->texture_selector.num_page = editor->textures->num_textures / 15;
	if (editor->textures->num_textures % 15)
		editor->texture_selector.num_page++;

	return ;
}
