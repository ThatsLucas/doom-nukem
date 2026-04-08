/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PNG.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:12:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/08 22:55:06 by lucas            ###   ########.fr       */
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
    int fd;
    char *buf;
    __uint32_t w;
    __uint32_t h;
    __uint8_t bit_depth; 
    __uint8_t color_type; 
    __uint8_t compression_method; 
    __uint8_t filter_method; 
    __uint8_t interlace_method; 
}				t_png;

typedef struct s_IHDR
{
    __uint32_t chunklen;
    __uint32_t chunktype;
    __uint32_t w;
    __uint32_t h;
    __uint8_t bit_depth; 
    __uint8_t color_type; 
    __uint8_t compression_method; 
    __uint8_t filter_method; 
    __uint8_t interlace_method; 
    __uint32_t crc;
    int bytes_per_pixel;
}               t_IHDR;

typedef struct s_IDAT t_IDAT;

typedef struct s_IDAT
{
    __uint32_t chunklen;
    __uint8_t *datas;
    __uint32_t crc;
    t_IDAT      *next;
}              t_IDAT;

typedef struct s_readPNG
{
    ssize_t nbytes;
    char buf[1024];
}				t_readPNG;


/*HEADER*/
int find_png_header(t_png *pngFile);

/*IHDR*/
int find_png_IHDR(t_png *pngFile);

/*IDAT*/
t_IDAT * find_all_IDAT(t_png *pngFile);

/*PROCESS*/
int process_png(char *path);
t_readPNG read_nbytes(int pngFile, int nbytes);

/*UTILS*/
__uint32_t big_endian_to_little_endian(__uint32_t n);

#endif