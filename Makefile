NAME = corewar
SRC_DIR = ./src/
INC_DIR = ./include/
LIB_DIR = ./libft/
# BIN_DIR = ./objects/
ERRFL = -Wall -Wextra -Werror

CUR_FLAG =  -lncurses

LIB = libft.a
SRC = op.c \
		main.c \
		visual.c \
		functions.c \
		fight.c

INCLUDES = ./op.h ./corelib.h ./visualization.h

SRCD = $(addprefix $(SRC_DIR), $(SRC))
INCD = $(addprefix $(INC_DIR), $(INCLUDES))
LIBD = $(addprefix $(LIB_DIR), $(LIB))
# BIND = $(addprefix $(BIN_DIR), $(BIN))

BIN = $(SRCD:.c=.o)

all: lib $(NAME)

lib: 
	@make -C $(LIB_DIR)

$(NAME): $(BIN) $(LIBD)
	gcc -o $(NAME) $(BIN) $(LIBD) $(CUR_FLAG)

%.o: %.c $(INCD)
	gcc -o $@ -c $< -I $(LIB_DIR) -I $(INC_DIR)

clean:
	@make clean -C $(LIB_DIR)
	@/bin/rm -f $(BIN)
	@/bin/rm -f *~

fclean: clean
	@make fclean -C $(LIB_DIR)
	@/bin/rm -f $(NAME)

re: fclean all