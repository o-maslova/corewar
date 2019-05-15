NAME = corewar
NAME_ASM = asm
SRC_DIR = ./vm/
INC_DIR = ./include/
LIB_DIR = ./libft/
ASM_DIR = ./asm_src/
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

ASM_SRC = asm_parser.c            \
			lexer/lexer.c           \
			lexer/tools_lexer_1.c   \
			lexer/tools_lexer_2.c   \
			lexer/get_line.c        \
			lexer/get_token.c       \
			lexer/create_token.c    \
			lexer/types.c           \
			syntax/syntax.c         \
			syntax/operation_1.c    \
			syntax/operation_2.c    \
			syntax/tools_syntax.c   \
			codegen/codegen.c       \
			codegen/code_get.c      \
			codegen/create.c        \
			codegen/tools.c         \
			itoa_16.c               \
			utils.c                 \
			write_tree.c            \
			op.c

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
ASMD = $(addprefix $(ASM_DIR), $(ASM_SRC))

BIN = $(SRCD:.c=.o)
BINV = $(VISD:.c=.o)
BINASM = $(ASMD:.c=.o)

all: lib $(NAME) $(NAME_ASM)

lib: 
	@make -C $(LIB_DIR)

$(NAME_ASM): $(BINASM) $(LIBD)
	gcc -o  $(NAME_ASM) $(LIBD) $(BINASM) $(CUR_FLAG)

$(NAME): $(BIN) $(BINV) $(LIBD)
	gcc -o  $(NAME) $(LIBD) $(BIN) $(BINV) $(CUR_FLAG)

%.o: %.c $(INCD)
	gcc $(ERRFL) -o $@ -c $< -I $(LIB_DIR) -I $(INC_DIR)

clean:
	@make clean -C $(LIB_DIR)
	@/bin/rm -f $(BIN) $(BINV) $(BINASM)
	@/bin/rm -f *~

fclean: clean
	@make fclean -C $(LIB_DIR)
	@/bin/rm -f $(NAME) $(NAME_ASM)

re: fclean all