/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   languages_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:40:35 by lle-duc           #+#    #+#             */
/*   Updated: 2026/07/06 12:49:55 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "languages/language.h"
#include "Game.h"

/* Remplit les textes avec les traductions de la langue. */
static void fill_language_texts(t_game *game, int index, char *str)
{
    char **tab[LANGUAGE_FIELDS];

    get_language_fields(game->languages, tab);
    if (index >= LANGUAGE_FIELDS)
    {
        ft_dprintf(STDERR_FILENO, "Error in language file (miss configuration)\n");
        return;
    }
    *tab[index] = ft_strdup(str + 1);
}

/* Découpe le tampon de texte en lignes. */
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

/* Ouvre le fichier de traduction. */
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

/* Charge les textes de la langue choisie. */
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
