/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 06:32:43 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/22 20:11:30 by ntoniolo         ###   ########.fr       */
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
#include <sys/time.h> //temp
#include <signal.h> //temp
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
# define FLAG_D (1 << 7)


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
	int				tab_arg[3];
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
	char			champ_com[COMMENT_LENGTH + 1];
	char			voider;
	int				champ_nbr;
	int				champ_size;
	int				champ_position;
}					t_champ;

typedef struct		s_process
{
	int				reg[REG_NUMBER + 1];
	int				in_stock[4];
	int				instruc;
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
	int				i_com;
	unsigned char	background[MEM_SIZE];
	unsigned char	light[MEM_SIZE];
	struct timeval	t1;
	struct timeval	t2;
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
	int				dump;

	int				i_debug;
	int				voider;

	char			arene[MEM_SIZE];
}					t_datas;

# include "prototypes.h"
#endif
