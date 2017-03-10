/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 04:16:24 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/09 19:05:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op    op_tab_init[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

static int		vm_size_champ(t_champ *champ, t_datas *datas)
{
	int size;
	int save;
	int cur;

	size = 0;
	cur = (int)champ->champ[size];
	while (cur >= 1 && cur <= 16)
	{
		save = size;
		if (vm_have_ocp(cur))
		{
			size += vm_ocp_size(champ->champ[size + 1], 3,
					op_tab_init[cur - 1].nbr_octet_dir) % MEM_SIZE;
			size += 2;
		}
		else
		{
			size += vm_havent_ocp(cur) % MEM_SIZE;
			size ++;
		}
		if (datas->flag & FLAG_V)
			ft_printf("AFTER Size Op%i [%x] : %i\n", (int)champ->champ[save],
					champ->champ[save + 1], size);
		cur = (int)champ->champ[size];
	}
	return (size);
}

static void		vm_verif_champ(char *chmp_info, t_champ *champ)
{
	int		i;
	unsigned char *c;

	c = (unsigned char*)chmp_info;
	i = COREWAR_EXEC_MAGIC;
	if (c[0] == (i >> 24) && c[1] == ((i >> 16) & 0xff)
			&& c[2] == ((i >> 8) & 0xff) && c[3] == (i & 0xff))
		;
	else
		exit(ft_int_error("magic exec invalide"));
	ft_memcpy(champ->champ_name, chmp_info + 4, PROG_NAME_LENGTH);
}

static int			vm_create_champ(t_champ *champs, char *entry, int i,
		t_datas *datas)
{
	int		fd;
	char	buff[sizeof(header_t) + CHAMP_MAX_SIZE + 1];

	if (1 > (fd = open(entry, O_RDONLY)))
		exit (ft_int_error("Echec de lecture du champion"));
	if (read(fd, &buff, sizeof(header_t) + CHAMP_MAX_SIZE) == -1)
		exit (ft_int_error("Echec de read du champion"));
	buff[sizeof(header_t) + CHAMP_MAX_SIZE] = 0;
	vm_verif_champ(buff, &champs[i]);
	ft_memmove((void *)&champs[i], (void *)(buff + sizeof(header_t)),
			CHAMP_MAX_SIZE);
	champs[i].champ_nbr = i;
	champs[i].champ_size = vm_size_champ(&champs[i], datas);
	if (close(fd) == -1)
		exit (ft_int_error("Echec de close du champion"));
	return (0);
}

int				vm_init_champ(t_champ *champs, int argc, char **argv,
		t_datas *datas)
{
	int		champ_nbr;
	int		i;

	i = datas->player_nbr;
	champ_nbr = 0;
	while (i < argc)
	{
		vm_create_champ(champs, argv[i], champ_nbr, datas);
		if (datas->flag & FLAG_V)
			ft_printf("champ_size %d, champ nbr %d\n", champs[i - 1].champ_size,
					champs[i - 1].champ_nbr);
		++i;
		++champ_nbr;
	}
	return (champ_nbr);
}
