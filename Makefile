NAME = doom-nukem

LIBFT_DIR = libft
OBJDIR = obj
DEPS_DIR = deps

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

# -------- SDL2 --------
SDL2_VERSION = 2.32.4
SDL2_DIR = $(DEPS_DIR)/sdl2
SDL2_LIB = $(SDL2_DIR)/lib/libSDL2.a
SDL2_INC = $(SDL2_DIR)/include/SDL2

# -------- SDL2_TTF --------
SDL2_TTF_VERSION = 2.22.0
SDL2_TTF_DIR = $(DEPS_DIR)/sdl2_ttf
SDL2_TTF_LIB = $(SDL2_TTF_DIR)/lib/libSDL2_ttf.a
SDL2_TTF_INC = $(SDL2_TTF_DIR)/include/SDL2

# -------- FLAGS --------
GL_LIB = -lGL
LDFLAGS = $(SDL2_LIB) $(SDL2_TTF_LIB) $(GL_LIB) -ldl -lpthread -lm
INCLUDE_FLAGS = -Iincludes -I$(SDL2_INC) -I$(SDL2_TTF_INC)

FILES = $(shell find srcs -name "*.c")
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(FILES))

# -------- BUILD --------

all: deps libft $(NAME)

# construit UNIQUEMENT si absent
deps: $(SDL2_LIB) $(SDL2_TTF_LIB)

# -------- SDL2 --------

$(SDL2_LIB):
	@echo "📦 Installing SDL2..."
	@mkdir -p $(DEPS_DIR)/tmp
	@curl -L https://github.com/libsdl-org/SDL/releases/download/release-$(SDL2_VERSION)/SDL2-$(SDL2_VERSION).tar.gz -o $(DEPS_DIR)/tmp/sdl2.tar.gz
	@tar -xzf $(DEPS_DIR)/tmp/sdl2.tar.gz -C $(DEPS_DIR)/tmp
	@cd $(DEPS_DIR)/tmp/SDL2-$(SDL2_VERSION) && \
	./configure --prefix=$(PWD)/$(SDL2_DIR) --disable-shared --enable-static && \
	make -j$(shell nproc) && make install
	@echo "✅ SDL2 ready"

# -------- SDL2_TTF --------

$(SDL2_TTF_LIB):
	@echo "📦 Installing SDL2_ttf..."
	@mkdir -p $(DEPS_DIR)/tmp
	@curl -L https://github.com/libsdl-org/SDL_ttf/releases/download/release-$(SDL2_TTF_VERSION)/SDL2_ttf-$(SDL2_TTF_VERSION).tar.gz -o $(DEPS_DIR)/tmp/sdl2_ttf.tar.gz
	@tar -xzf $(DEPS_DIR)/tmp/sdl2_ttf.tar.gz -C $(DEPS_DIR)/tmp
	@cd $(DEPS_DIR)/tmp/SDL2_ttf-$(SDL2_TTF_VERSION) && \
	./configure --prefix=$(PWD)/$(SDL2_TTF_DIR) \
	--disable-shared --enable-static \
	--with-sdl-prefix=$(PWD)/$(SDL2_DIR) && \
	make -j$(shell nproc) && make install
	@echo "✅ SDL2_ttf ready"

# -------- LIBFT --------

libft:
	@$(MAKE) -C $(LIBFT_DIR)

# -------- LINK --------

$(NAME): $(OBJ)
	@echo "🔗 Linking..."
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $@
	@echo "✅ $(NAME) built"

# -------- OBJ --------

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# -------- CLEAN --------

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(DEPS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re deps libft