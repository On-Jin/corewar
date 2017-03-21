/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 06:32:43 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/21 16:33:52 by ntoniolo         ###   ########.fr       */
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
# define NC_PUT_NBR 'c'
# define NC_DEBUG_X datas->size_max_x + 2 + 3
# define NC_DEBUG_Y 23
# define NC_W_INF 70
# define ALL 0

/*
** MACROS
*/

/*
** Structures
*/

typedef struct		s_draw
{
	int				x;
	int				y;
	int				max;
	int				count;
	int				cur_champ;
	int				save_pros;
	int				highlight;
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
	const char		*name;
	int				nb_arg;
	int				tab_arg[7];
	int				op_code;
	int				cycle;
	const char		*doc;
	int				have_ocp;
	int				nbr_octet_dir;
	int				mod_carry;
}					t_op;

typedef struct		s_champ
{
	char			champ[CHAMP_MAX_SIZE];
	char			champ_name[PROG_NAME_LENGTH + 1];
	char			voider;
	int				champ_nbr;
	int				champ_size;
	int				champ_position;
}					t_champ;

typedef struct		s_process
{
	int				reg[REG_NUMBER + 1];
	int				in_stock[4];
	int				voider;
	struct			s_process *next;
	int				PC;
	int				cycle;
	char			carry;
	char			live;
	char			instruction;
	char			champion;
	int				voider2;
}					t_process;

typedef struct		s_lives
{
	long			total_lives;
	long			cycle_lives;
	long			champ_total_lives[MAX_PLAYERS];
	long			champ_cycle_lives[MAX_PLAYERS];
	int				last_live;
	int				cycle_last_live;
}					t_lives;

typedef struct		s_ncurses
{
	WINDOW			*win;
	WINDOW			*inf;
	int				key;
	int				size_max_y;
	int				size_max_x;
	int				cur_pros;
	int				cur_menu;
	int				i_print;
	int				wall_cycle;
	int				voider;
	unsigned char	background[MEM_SIZE];
	unsigned char	light[MEM_SIZE];
}					t_nc;
typedef struct		s_inf
{
	long			nbr_process;
	long			total_lives;
	long			cycle_lives;
	long			cycle_last_live;
	int				champion;
	int				cur_process;
}					t_inf;

typedef struct		s_datas
{
	t_process		*begin_process;
	t_champ			*begin_champ;
	t_lives			*lives;
	t_cycle			cycle;
	t_nc			nc;
	t_op			op_tab[17];
	t_inf			inf[5];
	int				player_nbr;
	int				nbr_cycles;
	int				start[4];
	int				flag;

	int				i_debug;
	int				voider;

	char			arene[MEM_SIZE];
}					t_datas;

/*
** Prototypes
*/

# include "prototypes.h"
/*
void				vm_verif_macro(void);
int					vm_create_flags(char **argv, int argc, int *flag);
int					vm_init_champ(t_champ *champs, int argc,
		char **argv, t_datas *datas);

int					vm_ocp_size(char ocp, int nb_arg, int op_flag);
int					vm_havent_ocp(int op_code);
int					vm_have_ocp(int op_code);
*/

/*
** Libft_Prototypes
*/

/*
int					ft_int_error(char *line);
void				ft_void_error(char *line);
char				*ft_itoa_base_unsigned_max(uintmax_t n, int base, char a);
int					ft_gcd(int nbr);
int					ft_square_root(int square);

t_process	*vm_create_process(t_datas *datas, int nbr_champ);
t_process	*vm_copy_process(t_datas *datas, t_process *process, int PC);
void		vm_destroy_process(t_process *process, t_datas *datas);
void		vm_innit_to_0(t_datas *datas, t_champ *champs, t_lives *lives);
int			vm_do_cycles(t_datas *datas, void (**exec)(t_datas *, t_process *),
							void (**create)(t_datas *, t_process *));
int			vm_init_process(t_datas *datas);
void		vm_champ_process(t_datas *datas, int argc, char **argv);
int			vm_champ_number_to_position(int champ_num, t_champ *champ_tab);
int			vm_champ_position_to_number(int champ_pos, t_champ *champ_tab);
int			vm_recup_process_reg(t_process *process, char *arene, int adresse);
int			*vm_recup_all_process(t_process *process, char *arene, int flag);
int			vm_verif_i_code(char code, char a, char b, char c);
int			vm_recup_indirect_num(t_process *process, char *arene, int adresse);
int			vm_recup_arena_num(int size, char *arena, int PC);
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
int			vm_add_valid(int adresse);
void		ncurses_init(t_datas *datas, int height, int width);
void		ncurses_end(t_datas *datas);
void		ncurses_key(t_datas *datas);
void		ncurses_show_arene(t_datas *datas);
*/
#endif
