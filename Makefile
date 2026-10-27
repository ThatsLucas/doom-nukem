NAME = doom-nukem

LIBFT_DIR = libft
OBJDIR = obj
DEPS_DIR = deps

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

# -------- ALSA (headers pour l'audio de SDL2, sans sudo) --------
ALSA_VERSION = 1.2.12
ALSA_DIR = $(DEPS_DIR)/alsa
ALSA_LIB = $(ALSA_DIR)/lib/libasound.so

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

# -------- SDL2_MIXER --------
SDL2_MIXER_VERSION = 2.8.1
SDL2_MIXER_DIR = $(DEPS_DIR)/sdl2_mixer
SDL2_MIXER_LIB = $(SDL2_MIXER_DIR)/lib/libSDL2_mixer.a
SDL2_MIXER_INC = $(SDL2_MIXER_DIR)/include/SDL2

# -------- FLAGS --------
GL_LIB = -lGL
LDFLAGS = $(SDL2_MIXER_LIB) $(SDL2_LIB) $(SDL2_TTF_LIB) $(GL_LIB) -ldl -lpthread -lm
INCLUDE_FLAGS = -Iincludes -I$(SDL2_INC) -I$(SDL2_TTF_INC) -I$(SDL2_MIXER_INC)

INCLUDES = $(shell find includes -name "*.h")

FILES = $(shell find srcs -name "*.c")
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(FILES))

# -------- BUILD --------

all: deps libft $(NAME)

# construit UNIQUEMENT si absent
deps: $(ALSA_LIB) $(SDL2_LIB) $(SDL2_TTF_LIB) $(SDL2_MIXER_LIB)

# -------- ALSA --------

$(ALSA_LIB):
	@echo "📦 Installing ALSA headers..."
	@mkdir -p $(DEPS_DIR)/tmp
	@curl -L https://www.alsa-project.org/files/pub/lib/alsa-lib-$(ALSA_VERSION).tar.bz2 -o $(DEPS_DIR)/tmp/alsa.tar.bz2
	@tar -xjf $(DEPS_DIR)/tmp/alsa.tar.bz2 -C $(DEPS_DIR)/tmp
	@cd $(DEPS_DIR)/tmp/alsa-lib-$(ALSA_VERSION) && \
	./configure --prefix=$(PWD)/$(ALSA_DIR) \
	--disable-python --disable-aload --disable-alisp \
	--disable-topology --disable-ucm && \
	make -j$(shell nproc) && make install
	@echo "✅ ALSA ready"

# -------- SDL2 --------

$(SDL2_LIB): $(ALSA_LIB)
	@echo "📦 Installing SDL2..."
	@mkdir -p $(DEPS_DIR)/tmp
	@curl -L https://github.com/libsdl-org/SDL/releases/download/release-$(SDL2_VERSION)/SDL2-$(SDL2_VERSION).tar.gz -o $(DEPS_DIR)/tmp/sdl2.tar.gz
	@tar -xzf $(DEPS_DIR)/tmp/sdl2.tar.gz -C $(DEPS_DIR)/tmp
	@cd $(DEPS_DIR)/tmp/SDL2-$(SDL2_VERSION) && \
	./configure --prefix=$(PWD)/$(SDL2_DIR) --disable-shared --enable-static \
	--enable-alsa --enable-alsa-shared \
	--with-alsa-prefix=$(PWD)/$(ALSA_DIR)/lib \
	--with-alsa-inc-prefix=$(PWD)/$(ALSA_DIR)/include && \
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

# -------- SDL2_MIXER --------

$(SDL2_MIXER_LIB):
	@echo "📦 Installing SDL2_mixer..."
	@mkdir -p $(DEPS_DIR)/tmp
	@curl -L https://github.com/libsdl-org/SDL_mixer/releases/download/release-$(SDL2_MIXER_VERSION)/SDL2_mixer-$(SDL2_MIXER_VERSION).tar.gz -o $(DEPS_DIR)/tmp/sdl2_mixer.tar.gz
	@tar -xzf $(DEPS_DIR)/tmp/sdl2_mixer.tar.gz -C $(DEPS_DIR)/tmp
	@cd $(DEPS_DIR)/tmp/SDL2_mixer-$(SDL2_MIXER_VERSION) && \
	./configure --prefix=$(PWD)/$(SDL2_MIXER_DIR) \
	--disable-shared --enable-static \
	--with-sdl-prefix=$(PWD)/$(SDL2_DIR) \
	--disable-music-mod --disable-music-midi \
	--disable-music-opus --disable-music-flac-libflac \
	--disable-music-wavpack --disable-music-mp3-mpg123 && \
	make -j$(shell nproc) && make install
	@echo "✅ SDL2_mixer ready"

# -------- LIBFT --------

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

# -------- LINK --------

$(NAME): $(OBJ)
	@echo "🔗 Linking..."
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $@
	@echo "✅ $(NAME) built"

# -------- OBJ --------

$(OBJDIR)/%.o: %.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# -------- CLEAN --------

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

dclean:
	@rm -rf $(DEPS_DIR)
	@echo "🦧 deps cleaned"

re: fclean all

.PHONY: all clean fclean dclean re deps libft
