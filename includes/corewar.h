/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 06:32:43 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/13 19:11:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** Includes
*/

# include "op.h"
# include "libft.h"
# include <ncurses.h>
//# include "tmp.h"



/*
** Define
*/
# define NBR_FONC 17

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
** Ncurses
*/

# define NC_PAUSE 'e'
# define NC_SBS 's'
# define NC_PROC_NEXT '+'
# define NC_PROC_BACK '-'
# define NC_DEBUG_X datas->size_max_x + 2 + 3
# define NC_DEBUG_Y 23

/*
** MACROS
*/

/*
** Structures
*/

typedef struct		s_draw
{
	int				index;
	int				max;
	int				count;
	int				in_champ;
	int				cur_champ;
	int				size_champ;
	int				save_pros;
}					t_draw;

typedef struct		s_cycle
{
	int				cycle;
	int				total_cycle;
	int				cycle_to_die;
	int				check;
}					t_cycle;

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
	t_cycle			cycle;
	int				player_nbr;
	int				nbr_cycles;
	int				start[4];
	int				size_champ[4];
	int				flag;
	int				nbr_process;

	int				key;
	int				size_max_y;
	int				size_max_x;
	int				cur_pros;
	int				i_debug;

	WINDOW			*win;
}					t_datas;

/*
** Prototypes
*/

void				vm_verif_macro(void);
int					vm_create_flags(char **argv, int argc, int *flag);
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
int					ft_gcd(int nbr);
int					ft_square_root(int square);























































t_process	*vm_create_process(t_datas *datas, int nbr_champ);
t_process	*vm_copy_process(t_datas *datas, t_process *process, int PC);
void		vm_destroy_process(t_process *process, t_datas *datas);
void		vm_innit_to_0(t_datas *datas, t_champ *champs, t_vm *arene,
						t_lives *lives);
int			vm_do_cycles(t_datas *datas, void (**exec)(t_datas *, t_process *),
							void (**create)(t_datas *, t_process *));
int			vm_init_process(t_datas *datas);
void		vm_champ_process(t_datas *datas, int argc, char **argv);
int			vm_champ_number_to_position(int champ_num, t_champ *champ_tab);
int			vm_champ_position_to_number(int champ_pos, t_champ *champ_tab);
int			vm_recup_process_reg(t_process *process, t_vm *arene, int adresse);
int			*vm_recup_all_process(t_process *process, t_vm *arene, int flag);
int			vm_verif_i_code(char code, char a, char b, char c);
int			vm_recup_indirect_num(t_process *process, t_vm *arene, int adresse);
int			vm_recup_arena_num(int size, t_vm *arena, int PC);
int			vm_do_cycles(t_datas *datas, void (**exec)(t_datas *, t_process *), void (**create)(t_datas *, t_process *));
void		vm_op_0_exec(t_datas *datas, t_process *process);
void		vm_op_1_exec(t_datas *datas, t_process *process);
void		vm_op_2_exec(t_datas *datas, t_process *process);
void		vm_op_3_exec(t_datas *datas, t_process *process);
void		vm_op_4_exec(t_datas *datas, t_process *process);
void		vm_op_5_exec(t_datas *datas, t_process *process);
void		vm_op_6_exec(t_datas *datas, t_process *process);
void		vm_op_7_exec(t_datas *datas, t_process *process);
void		vm_op_8_exec(t_datas *datas, t_process *process);
void		vm_op_9_exec(t_datas *datas, t_process *process);
void		vm_op_10_exec(t_datas *datas, t_process *process);
void		vm_op_11_exec(t_datas *datas, t_process *process);
void		vm_op_12_exec(t_datas *datas, t_process *process);
void		vm_op_13_exec(t_datas *datas, t_process *process);
void		vm_op_14_exec(t_datas *datas, t_process *process);
void		vm_op_15_exec(t_datas *datas, t_process *process);
void		vm_op_16_exec(t_datas *datas, t_process *process);
void		vm_op_0_create(t_datas *datas, t_process *process);
void		vm_op_1_create(t_datas *datas, t_process *process);
void		vm_op_2_create(t_datas *datas, t_process *process);
void		vm_op_3_create(t_datas *datas, t_process *process);
void		vm_op_4_create(t_datas *datas, t_process *process);
void		vm_op_5_create(t_datas *datas, t_process *process);
void		vm_op_6_create(t_datas *datas, t_process *process);
void		vm_op_7_create(t_datas *datas, t_process *process);
void		vm_op_8_create(t_datas *datas, t_process *process);
void		vm_op_9_create(t_datas *datas, t_process *process);
void		vm_op_10_create(t_datas *datas, t_process *process);
void		vm_op_11_create(t_datas *datas, t_process *process);
void		vm_op_12_create(t_datas *datas, t_process *process);
void		vm_op_13_create(t_datas *datas, t_process *process);
void		vm_op_14_create(t_datas *datas, t_process *process);
void		vm_op_15_create(t_datas *datas, t_process *process);
void		vm_op_16_create(t_datas *datas, t_process *process);

void		ncurses_init(t_datas *datas, int height, int width);
void		ncurses_end(t_datas *datas);
void		ncurses_key(t_datas *datas);
void		ncurses_show_arene(t_datas *datas);

#endif
