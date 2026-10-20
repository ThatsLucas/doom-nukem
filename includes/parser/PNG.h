/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PNG.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:12:34 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/20 18:30:13 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PNG_H
# define PNG_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../libft/include/libft.h"
#include <SDL.h>

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

typedef struct s_png
{
    int fd;
    __uint8_t **buf;
    char        *path;
    SDL_Texture *texture;
    __uint32_t w;
    __uint32_t h;
    int32_t x;
    int32_t y;
    __uint8_t bit_depth; 
    __uint8_t color_type; 
    __uint8_t compression_method; 
    __uint8_t filter_method; 
    __uint8_t interlace_method; 
    t_IHDR    IHDR;
}				t_png;


typedef struct s_IDAT t_IDAT;

typedef struct s_IDAT
{
    __uint32_t chunklen;
    __uint8_t *datas;
    __uint32_t crc;
    t_IDAT      *next;
}              t_IDAT;

typedef struct  s_bitreader
{
    __uint8_t *buffer;
    int bit_index;
    __uint64_t byte_index;
    __uint64_t buffer_len;
}               t_bitreader;

typedef struct s_inflate
{
    __uint8_t BTYPE;
    __uint8_t BFINAL;
}              t_inflate;

typedef struct s_readPNG
{
    ssize_t nbytes;
    char buf[1024];
}				t_readPNG;


/*HEADER*/
int         find_png_header(t_png *pngFile);

/*IHDR*/
int find_png_IHDR(t_IHDR *headerIHDR, t_png *pngFile);

/*IDAT*/
void        free_idat_list(t_IDAT *lst);
t_IDAT      *find_all_IDAT(t_png *pngFile);
__uint64_t get_total_compressed_size(t_IDAT *lst);
__uint8_t   *merge_all_buffers(t_IDAT *lst);

/*ZLIB*/
void skip_zlib_header(int fd);

/*DEFLATE*/
int parse_deflate_blocs(t_png *pngFile, __uint8_t *buff, __uint64_t buffer_len);
__uint32_t read_bits(t_bitreader *bitReader, int bitsToRead);
int read_symbol(t_bitreader *bitReader, int *table_symbol, int *table_len, int maxbits);
void build_code_table(int *lengths, __uint32_t count, int *table_symbol, int *table_len);
void build_meta_tree(__uint32_t HLIT, __uint32_t HDIST, __uint32_t HCLEN, t_bitreader *bitReader, int *lit_symbol, int *lit_len, int *dist_symbol, int *dist_len);
void read_compressed_datas(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader, int *lit_symbol, int *lit_len, int *dist_symbol, int *dist_len);
int huffman_fixed(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader);
int huffman_dynamic(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader);
int huffman_uncompressed(__uint8_t *buf, __uint32_t *buf_len, t_bitreader *bitReader);

/*LZ77*/
void lz77(__uint8_t *buf, __uint32_t *buf_len, size_t max_len, t_bitreader *bitReader, int sym, int *dist_symbol, int *dist_len);

/*FILTER*/
void fill_img_buffer(t_png *pngFile, __uint8_t *buff, __uint32_t len);

/*PROCESS*/
void        *process_png(void *pngStruct);
t_readPNG   read_nbytes(int pngFile, int nbytes);

/*UTILS*/
__uint32_t big_endian_to_little_endian(__uint32_t n);

#endif