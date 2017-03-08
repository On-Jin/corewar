/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 06:32:43 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/08 15:23:54 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** Includes
*/

# include "op.h"
# include "libft.h"

/*
** Define
*/

# define OP_LIVE 1
# define OP_LD 2 
# define OP_ST 3
# define OP_ADD 4
# define OP_SUB 5
# define OP_AND 6
# define OP_OR 7
# define OP_XOR 8
# define OP_ZJMP 9
# define OP_LDI 10
# define OP_STI 11
# define OP_FORK 12
# define OP_LLD 13
# define OP_LLDI 14
# define OP_LFORK 15
# define OP_AFF 16

/*
** MACROS
*/

/*
** Structures
*/

typedef struct		s_op
{
	char			*str_op_code;
	int				nb_arg;
	int				tab_arg[7];
	int				op_code;
	int				cycle;
	char			*doc;
	int				mod_carry;
	int				nbr_octet_dir;
}					t_op;

typedef struct		s_champ
{
	char			champ[CHAMP_MAX_SIZE];
	char			champ_name[PROG_NAME_LENGTH + 1];
	int				champ_nbr;
	int				champ_size;
}					t_champ;

typedef struct		s_vm
{
	char			arene[MEM_SIZE];
}					t_vm;

typedef struct		s_process
{
	char			reg[REG_NUMBER * REG_SIZE];
	char			PC[REG_SIZE];
	int				cycle;
	char			carry;
	char			live;
	char			instruction;
	char			champion;
}					t_process;

typedef struct		s_datas
{
	t_vm			*arene;
	t_process		*begin_process;
	t_champ			*begin_champ;
	int				player_nbr;
	int				nbr_cycles;
	int				flag;
}					t_datas;

/*
 ** Prototypes
 */

int					vm_create_flags(char **argv, int argc, int *flag);
void				vm_show_arene(t_vm *arene);
int					vm_init_champ(t_champ *champs, int argc,
		char **argv, t_datas *datas);

int					vm_ocp_size(char ocp, int nb_arg, int op_flag);
int					vm_havent_ocp(int op_code);
int					vm_have_ocp(int op_code);

/*
 ** Libft_Prototypes
 */

int					ft_int_error(char *line);
void				ft_void_error(char *line);
char				*ft_itoa_base_unsigned_max(uintmax_t n, int base, char a);


#endif
