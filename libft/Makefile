NAME = libft.a
OBJDIR = obj
FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isspace.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstadd_front_bonus.c \
		ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
		ft_put_pointer.c ft_putnbr_unsigned.c ft_hexa.c ft_printf.c get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c ft_freeall.c ft_strcmp.c ft_arrlen.c ft_printable.c ft_lstget.c \
		ft_intlen.c ft_maxf.c ft_dprintf.c ft_strcat.c

CC = cc
AR = ar rcs
CFLAGS = -Wall -Werror -Wextra -g3
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(FILES))
INCLUDES = include/libft.h

RESET = \033[0m
GRAY = \033[1;90m

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $@ $^

$(OBJDIR)/%.o: %.c $(INCLUDES)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I include -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all re # evite la confusion entre regles et fichiers
