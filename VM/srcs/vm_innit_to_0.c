/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_innit_to_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:12:17 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/19 21:31:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	innit_op_tab(t_datas *datas)
{
	static t_op op_tab_init[17] =
	{
		{0, 0, {0}, 0, 1, 0, 0, 0, 0},
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 0},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 1},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 0},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 1},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 1},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
			"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 1},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
			"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 1},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
			"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 1},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 0},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
			"load index", 1, 1, 0},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
			"store index", 1, 1, 0},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 0},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 1},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
			"long load index", 1, 1, 1},
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 0},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 0}
	};
	ft_memcpy((void*)&datas->op_tab[0], (void*)&op_tab_init[0], sizeof(t_op) * 17);
}

static void	vm_innit_inf(t_datas *datas)
{
	int i;

	i = 0;
	while (i <= datas->player_nbr)
	{
		datas->inf[i].nbr_process = 0;
		datas->inf[i].total_lives = 0;
		datas->inf[i].cycle_lives = 0;
		datas->inf[i].cycle_last_live = 0;
		datas->inf[i].champion = i + 1;
		i++;
	}
}

void		vm_innit_to_0(t_datas *datas, t_champ *champs, t_lives *lives)
{
	ft_bzero((void *)datas, MEM_SIZE);
	ft_bzero((void *)champs, sizeof(t_champ) * (MAX_PLAYERS + 1));
	ft_bzero((void *)lives, sizeof(t_lives));
	ft_bzero((void *)datas->arene, MEM_SIZE);
	datas->lives = lives;
	datas->begin_champ = champs;
	datas->nbr_cycles = CYCLE_TO_DIE;
	datas->nbr_process = 0;
	datas->i_debug = 0;
	vm_innit_inf(datas);
	innit_op_tab(datas);
}
