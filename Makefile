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
DEPS_DIR = deps
SDL2_INC = $(DEPS_DIR)/sdl2/include
SDL2_SO = /usr/lib64/libSDL2-2.0.so.0
GL_SO = /usr/lib64/libGL.so.1

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = $(SDL2_SO) $(GL_SO) -ldl -lpthread

OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(FILES))
FILES = main.c
INCLUDES = includes
INCLUDE_FLAGS = -I$(INCLUDES) -I$(SDL2_INC)

RESET = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;90m
LIGHTBLUE = \033[1;94m

all: deps $(LIBFT) $(NAME)

# --- Téléchargement des headers SDL2 si absents ---
deps:
	@if [ ! -f $(SDL2_INC)/SDL.h ]; then \
		echo "$(LIGHTBLUE)Téléchargement des headers SDL2...$(RESET)"; \
		mkdir -p $(SDL2_INC); \
		curl -L https://github.com/libsdl-org/SDL/releases/download/release-2.32.4/SDL2-2.32.4.tar.gz -o /tmp/sdl2.tar.gz && \
		tar -xzf /tmp/sdl2.tar.gz -C /tmp/ && \
		cp -r /tmp/SDL2-2.32.4/include/. $(SDL2_INC)/; \
		echo "$(GREEN)Headers SDL2 prêts !$(RESET)"; \
	else \
		echo "$(GREEN)Headers SDL2 déjà présents.$(RESET)"; \
	fi
	@if [ ! -f $(SDL2_SO) ]; then \
		echo "$(RED)ERREUR: $(SDL2_SO) introuvable. Demandez à quelqu'un d'installer libSDL2.$(RESET)"; \
		exit 1; \
	fi
	@if [ ! -f $(GL_SO) ]; then \
		echo "$(RED)ERREUR: $(GL_SO) introuvable. Demandez à quelqu'un d'installer mesa-libGL.$(RESET)"; \
		exit 1; \
	fi

# --- libft ---
$(LIBFT): $(LIBFT_SRCS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

# --- Binaire principal ---
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

fclean: clean dfclean
	rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: fclean clean all re dfclean deps