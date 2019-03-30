NAME = corewar
SRC_DIR = ./vm/
INC_DIR = ./include/
LIB_DIR = ./libft/
VIS_DIR = ./vm/visualization/
ERRFL = -Wall -Wextra -Werror

CUR_FLAG =  -lncurses

LIB = libft.a
SRC = args_functions.c \
		carriege_functions.c \
		f1_f5.c \
		f6_f10.c \
		f11_f16.c \
		fight.c \
		free.c \
		fun_for_fun.c \
		get_args.c \
		main.c \
		nechto.c \
		op.c \
		player_functions.c \
		stuff.c


VIS_SRC = colors.c \
			end_of_game.c \
			initialization.c \
			musica.c \
			print_side_frame.c \
			rainbow_bonus.c \
			visual_fight.c

INCLUDES = ./corelib.h ./op.h ./visualization.h

SRCD = $(addprefix $(SRC_DIR), $(SRC))
INCD = $(addprefix $(INC_DIR), $(INCLUDES))
LIBD = $(addprefix $(LIB_DIR), $(LIB))
VISD = $(addprefix $(VIS_DIR), $(VIS_SRC))
# BIND = $(addprefix $(BIN_DIR), $(BIN))

BIN = $(SRCD:.c=.o)
BINV = $(VISD:.c=.o)

all: lib $(NAME)

lib: 
	@make -C $(LIB_DIR)

$(NAME): $(BIN) $(BINV) $(LIBD)
	gcc -o $(NAME) $(LIBD) $(BIN) $(BINV) $(CUR_FLAG)

%.o: %.c $(INCD)
	gcc -o $@ -c $< -I $(LIB_DIR) -I $(INC_DIR)

clean:
	@make clean -C $(LIB_DIR)
	@/bin/rm -f $(BIN) $(BINV)
	@/bin/rm -f *~

fclean: clean
	@make fclean -C $(LIB_DIR)
	@/bin/rm -f $(NAME)

re: fclean all