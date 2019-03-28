NAME = corewar
SRC_DIR = ./src/
INC_DIR = ./include/
LIB_DIR = ./libft/
VIS_DIR = ./src/visualization/
# BIN_DIR = ./objects/
ERRFL = -Wall -Wextra -Werror

CUR_FLAG =  -lncurses

LIB = libft.a
SRC = op.c \
		main_2.c \
		f1_f5.c \
		f6_f10.c \
		f11_f16.c \
		fight.c

VIS_SRC = initialization.c \
			print.c \
			colors.c \
			rainbow_bonus.c

INCLUDES = ./op.h ./corelib.h ./visualization.h

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
	gcc -o $(NAME) $(BIN) $(BINV) $(LIBD) $(CUR_FLAG)

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