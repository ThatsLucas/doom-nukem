/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PNG.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:12:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/06 17:30:31 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PNG_H
# define PNG_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../libft/include/libft.h"

typedef struct s_png
{
    int w;
    int h;
    int fd;
    char *buf;
}				t_png;

typedef struct s_readPNG
{
    ssize_t nbytes;
    char buf[1024];
}				t_readPNG;


/*HEADER*/
int find_png_header(t_png pngFile);

/*PROCESS*/
int process_png(char *path);
t_readPNG read_nbytes(int pngFile, int nbytes);

#endif