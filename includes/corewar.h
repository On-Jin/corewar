/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 06:32:43 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/06 06:32:46 by gnebie           ###   ########.fr       */
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
** MACROS
*/

/*
** Structures
*/

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
	int				carry;
}					t_process;

typedef struct		s_datas
{
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

/*
** Libft_Prototypes
*/

int					ft_int_error(char *line);
void				ft_void_error(char *line);
char				*ft_itoa_base_unsigned_max(uintmax_t n, int base, char a);


#endif
