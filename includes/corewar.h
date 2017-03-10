/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 06:32:43 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/09 23:22:13 by ntoniolo         ###   ########.fr       */
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
** Define flags
*/

# define FLAG_V 1
# define FLAG_B (1 << 1)
# define FLAG_N (1 << 2)
# define FLAG_M (1 << 3)
# define FLAG_K (1 << 4)
# define FLAG_G (1 << 5)
# define FLAG_H (1 << 6)

/*
** MACROS
*/

/*
** Structures
*/

typedef struct		s_op
{
	char			*name;
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
	int				champ_position;
}					t_champ;

typedef struct		s_vm
{
	char			arene[MEM_SIZE];
}					t_vm;

typedef struct		s_process
{
	int				reg[REG_NUMBER + 1];
	int				in_stock[4];
	struct			s_process *next;
	int				PC;
	int				cycle;
	char			carry;
	char			live;
	char			instruction;
	char			champion;
}					t_process;

typedef struct		s_lives
{
	long			total_lives;
	long			cycle_lives;
	long			champ_total_lives[CHAMP_MAX_SIZE];
	long			champ_cycle_lives[CHAMP_MAX_SIZE];
	int				last_live;
}					t_lives;

typedef struct		s_datas
{
	t_vm			*arene;
	t_process		*begin_process;
	t_champ			*begin_champ;
	t_lives			*lives;
	int				player_nbr;
	int				nbr_cycles;
	int				start[4];
	int				flag;
}					t_datas;

/*
 ** Prototypes
 */

void				vm_verif_macro(void);
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
