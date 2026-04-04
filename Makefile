NAME = doom-nukem
LIBFT_DIR = libft
OBJDIR = obj
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_SRCS := libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c \
            libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c \
            libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
            libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c \
            libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c \
            libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_lstadd_front_bonus.c \
            libft/ft_lstnew_bonus.c libft/ft_lstsize_bonus.c libft/ft_lstlast_bonus.c libft/ft_lstadd_back_bonus.c \
            libft/ft_lstdelone_bonus.c libft/ft_lstclear_bonus.c libft/ft_lstiter_bonus.c libft/ft_lstmap_bonus.c \
            libft/ft_putnbr_unsigned.c libft/ft_printf.c libft/get_next_line/get_next_line.c \
            libft/get_next_line/get_next_line_utils.c libft/ft_freeall.c libft/ft_lstget.c libft/ft_maxf.c

CC = cc
CFLAGS = -Wall -Werror -Wextra
DEPS_DIR = deps
SDL2_VERSION = 2.32.4
SDL2_SYSTEM = /usr/lib64/libSDL2-2.0.so.0
SDL2_LIB = $(DEPS_DIR)/sdl2/lib/libSDL2.a
SDL2_HEADERS = /usr/include/SDL2/SDL.h

ifeq ($(shell test -f $(SDL2_SYSTEM) && test -f $(SDL2_HEADERS) && echo yes),yes)
    SDL2_LINK = $(SDL2_SYSTEM)
    SDL2_INC = /usr/include/SDL2
else
    SDL2_LINK = $(SDL2_LIB)
    SDL2_INC = $(DEPS_DIR)/sdl2/include/SDL2
endif

INCLUDES = includes

GL_SYSTEM_PATHS = /usr/lib64/libGL.so.1 /usr/lib/x86_64-linux-gnu/libGL.so.1 /usr/lib/libGL.so.1

GL_LIB := $(firstword $(foreach path, $(GL_SYSTEM_PATHS), $(if $(wildcard $(path)), $(path),)))

ifeq ($(GL_LIB),)
    GL_LIB = -lGL
endif

LDFLAGS = $(SDL2_LINK) $(GL_LIB) -ldl -lpthread -lm

INCLUDE_FLAGS = -I$(INCLUDES) -I$(SDL2_INC)
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(FILES))
FILES = $(shell find srcs -name "*.c")

RESET = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;90m
LIGHTBLUE = \033[1;94m

all: deps $(LIBFT) $(NAME)

deps:
	@if [ -f $(SDL2_SYSTEM) ] && [ -f $(SDL2_HEADERS) ]; then \
		echo "$(GREEN)SDL2 système trouvé.$(RESET)"; \
	elif [ -f $(SDL2_LIB) ]; then \
		echo "$(GREEN)SDL2 local trouvé.$(RESET)"; \
	else \
		$(MAKE) --no-print-directory $(SDL2_LIB); \
	fi

$(SDL2_LIB):
	@echo "$(LIGHTBLUE)Compilation de SDL2 depuis les sources...$(RESET)"
	@mkdir -p $(DEPS_DIR)/sdl2
	@curl --fail -L \
		https://github.com/libsdl-org/SDL/releases/download/release-$(SDL2_VERSION)/SDL2-$(SDL2_VERSION).tar.gz \
		-o /tmp/sdl2.tar.gz || (echo "$(RED)Échec du téléchargement SDL2.$(RESET)"; exit 1)
	@tar -xzf /tmp/sdl2.tar.gz -C /tmp/
	@cd /tmp/SDL2-$(SDL2_VERSION) && \
		./configure --prefix=$(shell pwd)/$(DEPS_DIR)/sdl2 --disable-shared --enable-static && \
		make -j$(shell nproc) && \
		make install
	@echo "$(GREEN)SDL2 compilé et installé !$(RESET)"

$(LIBFT): $(LIBFT_SRCS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(LIGHTBLUE)Linking $(NAME)...$(RESET)"
	$(CC) $(OBJ) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $@
	@echo "$(GREEN)$(NAME) compilé avec succès !$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

dfclean:
	rm -rf $(DEPS_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: fclean clean all re dfclean deps
