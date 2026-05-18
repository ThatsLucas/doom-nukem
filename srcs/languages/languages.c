/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   languages.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:40:35 by lle-duc           #+#    #+#             */
/*   Updated: 2026/05/18 17:27:28 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "languages/language.h"
#include "Game.h"

void free_languages(t_game *game)
{
    if (!game->languages)
        return;
    free(game->languages->loading);
    free(game->languages->play);
    free(game->languages->settings);
    free(game->languages->level_editor);
    free(game->languages->pick_a_key);
    free(game->languages->move_forward);
    free(game->languages->move_backward);
    free(game->languages->move_left);
    free(game->languages->move_right);
    free(game->languages->fov);
    free(game->languages->languages);
    free(game->languages->resolution);
    free(game->languages->display_mode);
    free(game->languages->fullscreen);
    free(game->languages->borderless);
    free(game->languages->windowed);
    free(game->languages->mouse_sensi);
    free(game->languages->main_menu);
    free(game->languages->lobby_solo);
    free(game->languages->level_one);
    free(game->languages->level_two);
    free(game->languages->level_three);
    free(game->languages->multiplayer);
    free(game->languages->lobby_multi);
    free(game->languages->solo);

    game->languages->loading = NULL;
    game->languages->play = NULL;
    game->languages->settings = NULL;
    game->languages->level_editor = NULL;
    game->languages->pick_a_key = NULL;
    game->languages->move_forward = NULL;
    game->languages->move_backward = NULL;
    game->languages->move_left = NULL;
    game->languages->move_right = NULL;
    game->languages->fov = NULL;
    game->languages->languages = NULL;
    game->languages->resolution = NULL;
    game->languages->display_mode = NULL;
    game->languages->fullscreen = NULL;
    game->languages->borderless = NULL;
    game->languages->windowed = NULL;
    game->languages->mouse_sensi = NULL;
    game->languages->main_menu = NULL;
    game->languages->lobby_solo = NULL;
    game->languages->level_one = NULL;
    game->languages->level_two = NULL;
    game->languages->level_three = NULL;
    game->languages->multiplayer = NULL;
    game->languages->lobby_multi = NULL;
    game->languages->solo = NULL;
    free(game->languages);
    game->languages = NULL;
}

static void fill_language_texts(t_game *game, int index, char *str)
{
    char **tab[25] = {
        &game->languages->loading,
        &game->languages->play,
        &game->languages->settings,
        &game->languages->level_editor,
        &game->languages->pick_a_key,
        &game->languages->move_forward,
        &game->languages->move_backward,
        &game->languages->move_left,
        &game->languages->move_right,
        &game->languages->fov,
        &game->languages->languages,
        &game->languages->resolution,
        &game->languages->display_mode,
        &game->languages->fullscreen,
        &game->languages->borderless,
        &game->languages->windowed,
        &game->languages->mouse_sensi,
        &game->languages->main_menu,
        &game->languages->lobby_solo,
        &game->languages->level_one,
        &game->languages->level_two,
        &game->languages->level_three,
        &game->languages->multiplayer,
        &game->languages->lobby_multi,
        &game->languages->solo,
    };

    if (index > 25)
    {
        ft_dprintf(STDERR_FILENO, "Error in language file (miss configuration)\n");
        return;
    }
    *tab[index] = ft_strdup(str + 1);
}

static int split_buffer(t_game *game, char *str)
{
    char **splitted = ft_split(str, '\n');
    for (int i = 0; splitted[i]; i++)
    {
        fill_language_texts(game, i, ft_strrchr(splitted[i], '='));
    }
    ft_freeall(splitted);
    return (1);
}

static int open_language_file(int language)
{
    int fd = -1;
    if (language == 0)
        fd = open("srcs/languages/dict/english.txt", O_RDONLY);
    if (language == 1)
        fd = open("srcs/languages/dict/french.txt", O_RDONLY);
    if (language == 2)
        fd = open("srcs/languages/dict/arabic.txt", O_RDONLY);
    if (language == 3)
        fd = open("srcs/languages/dict/serbian.txt", O_RDONLY);
    return (fd);
}

void parse_languages(t_game *game, int language)
{
    int fd = open_language_file(language);

    if (fd < 0)
        exit_game(game, "Could not Open language File\n");
    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char *buf = malloc(size + 1);
    int bytes_read = read(fd, buf, size);
    buf[size] = '\0';
    close(fd);
    if (bytes_read != size)
    {
        free(buf);
        exit_game(game, "Invalid Language File (bytes read != real size)\n");
    }

    game->languages = malloc(sizeof(t_languages));
    if (!game->languages)
    {
        free(buf);
        exit_game(game, "Invalid Language File\n");
    }
    split_buffer(game, buf);
}
