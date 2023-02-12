NAME	:=	cub3d

CC		:=	gcc
CFLAGS	:= 	-O3 -g -Wall -Wextra -Werror

PATH_SRC		:=	./src
PATH_INCLUDES	:=	./incs
PATH_BUILD		:= ./build
PATH_OBJS		:= $(PATH_BUILD)/objs

SRCS			:=	$(PATH_SRC)/main.c \
					$(PATH_SRC)/mlx_stuff.c \
					$(PATH_SRC)/map.c \
					$(PATH_SRC)/movement.c \
					$(PATH_SRC)/rays.c \
					$(PATH_SRC)/rayutils.c \
					$(PATH_SRC)/horizontal_inter.c \
					$(PATH_SRC)/vertical_inter.c \


OBJ				:= $(subst .c,.o,$(subst $(PATH_SRC), $(PATH_OBJS), $(SRCS)))

all:$(NAME)

$(NAME): $(MLX_L) $(OBJ)
		@$(CC) -D DO_GPU $(CFLAGS) $(LIBS) -o $(@) $^ -I$(PATH_INCLUDES)  $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
		@printf "\033[44m[$(NAME) BUILT!]\033[0m\n"

$(PATH_OBJS)/%.o: $(PATH_SRC)/%.c | $(PATH_BUILD)
		@$(CC) $(CFLAGS)  -c $(^) -o $@
		@printf "\033[36m[Building ${@F}]\033[0m\n"


$(PATH_BUILD):
		@mkdir -p $(PATH_BUILD)
		@mkdir -p $(PATH_OBJS) 

clean:
		@printf "\033[38;5;1m[Cleaning objects!]\033[0m\n"
		@rm -rf $(PATH_OBJS)

$(MLX_L):
	@printf "\033[4;32m[Building MLX]\033[0m\n"
	@$(MAKE) -C ./mlx_linux 

fclean: clean
		@printf "\033[38;5;1m[Cleaning Bin!]\033[0m\n"
		@rm -rf $(PATH_BUILD) $(NAME)

re: fclean all
