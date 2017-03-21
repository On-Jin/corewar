#ifndef COMPILER_H
# define COMPILER_H


#include "../includes/corewar.h"
#include "../includes/libft/libft.h"

typedef struct			s_instruct
{
	char				*label_name; //*
	size_t              size;
	int                 opcode; //*
	int                 argcode; //*
	int 				arg_nbrs; //*
	/*[arg_type, content_len, octet1, octet2, octet3, octet4]*/
	int                 args[3][3];
	char				*args_labels[3];
	struct s_instruct	*next;
}						t_instruct;

void	write_exec_magic(int fd, header_t *header);
void	write_comment(int fdin, header_t *header);
void error(char *str);
t_instruct *compiler_compile(int fdin);
size_t		get_instruct_size(t_instruct *current);
void	invert_byte(unsigned int *val);
#endif