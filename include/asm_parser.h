/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abulakh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:43:26 by abulakh           #+#    #+#             */
/*   Updated: 2017/10/25 20:43:27 by abulakh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_PARSER_H
# define ASM_PARSER_H
# include "corelib.h"
# define OP	"live ld st add sub and or xor zjmp ldi sti fork lld lldi lfork aff"
# define SEPARATORS			"%:,- \t"

/*
**	ERRORS
*/

# define ERR_LEX			"Lexical error at "
# define ERR_TOKEN			"Syntax error at token [TOKEN]"
# define ERR_FILE_NAME		"Can't read sourse file "
# define ERR_USAGE			"Usage: ./asm <file.s> || ./asm -a <file.s>"
# define ERR_LABEL			"No such lable"
# define ERR_NULL			"Invalid instruction at token [TOKEN]"

# define MES_OUTPUT			"\033[092mWriting output program to ."

typedef struct		s_token
{
	char			*name_token;
	int				posx;
	int				posy;
	int				dexpos;
	int				codage;
	int				index;
	int				size;
	struct s_token	*next;
}					t_token;

typedef struct		s_codegen
{
	int				cur_dep;
	int				n_args;
	int				lable;
	int				oper;
	int				have_cd;
	int				codage;
	int				ar[3];
	char			*arg[3];
	int				arg_ind[3];
}					t_codegen;

typedef struct		s_lexer
{
	char			**names_oper;
	char			**names_regs;
	t_token			*b_tok;
	char			*file_name;
	int				fd;
	t_header		*header;
	t_token			*l_tok;
	t_op			g_op_tab[17];
	int				dexpos;
	int				posy;
	int				lbl;
	int				dir_lab;
	int				ind_lab;
	int				dir_num;
	int				error;
	char			*error_str;
	int				ind_num;
	char			*name_token;
}					t_lexer;

/*
**	Main
*/

t_lexer				*lexer(int fd, char *file_name);
int					syntax(t_lexer *lex);
int					codegen(t_lexer *lex);

void				get_functions(t_lexer *lex);

/*
**	Codegen
*/

int					create_codage(t_codegen *code);
void				create_file(t_lexer *lex);
void				get_argument(t_codegen *code, t_lexer *lex, int i);
void				rotate_num(char *str, int size);

/*
**	Syntax
*/

void				current_init(t_lexer *lex, t_token *current, int size,
									int codage);
int					check_arguments(t_lexer *lex, t_token *current, int type,
									int dir_size);

t_token				*operation_ld_lld(t_lexer *lex, t_token *current);
t_token				*operation_st(t_lexer *lex, t_token *current);
t_token				*operation_add_sub(t_lexer *lex, t_token *current);
t_token				*operation_and_or_xor(t_lexer *lex, t_token *cur);
t_token				*operation_zjmp_fork_lfork(t_lexer *lex, t_token *current);
t_token				*operation_ldi_lldi(t_lexer *lex, t_token *cur);
t_token				*operation_sti(t_lexer *lex, t_token *cur);
t_token				*operation_aff(t_lexer *lex, t_token *current);

/*
**	Lexer
*/

int					get_line_of_tokens(int fd, t_lexer *lex);
int					get_token_dir(char *line, int i, t_lexer *l);
int					get_token_ind_lable(char *line, int i, t_lexer *lex);
int					get_header_comment(t_header *header, int *posy,
										char *line);
int					get_token_lorn(char *line, int i, t_lexer *lex);
int					get_token_chars(char *line, int i, t_lexer *lex);
int					get_header_name(t_header *header, int *posy, char *line);

void				create_first_token(t_lexer *lx, int posx, int type);
void				create_new_token(t_lexer *lx, int posx, int type);

int					type_1(t_lexer *lex, t_token *current);
int					type_4(t_lexer *lex, t_token *current);
int					type_5(t_lexer *lex, t_token *current);
int					type_6(t_lexer *lex, t_token *current);
int					type_7(t_lexer *lex, t_token *current);

char				*no_comments(int fd, int *posy);
int					no_whitespace(char *line, int i);
void				free_lexer(t_lexer *lex);
int					find_str_in_spl(char **spl, char *str);
int					is_number(char *name);
void				lexer_error(t_lexer *lex, int i);

/*
**	Utils
*/

char				*itoa_16(uintmax_t num, int xx);
char				*join_with_free(char *str1, char *str2);
void				ft_error_asm(char *txt);
void				ft_test_error(t_token *token);
void				write_tree_struct(t_lexer *lex);
int					length_of_int(int num);

#endif
