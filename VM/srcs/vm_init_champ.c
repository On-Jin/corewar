/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 04:16:24 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/23 15:00:46 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			vm_size_champ(t_champ *champ, t_datas *datas)
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
					datas->op_tab[cur].nbr_octet_dir) % MEM_SIZE;
			size += 2;
		}
		else
			size += (vm_havent_ocp(cur) % MEM_SIZE) + 1;
		if (datas->flag & FLAG_V)
			ft_printf("AFTER Size Op%i [%x] : %i\n", (int)champ->champ[save],
					champ->champ[save + 1], size);
		cur = (int)champ->champ[size];
	}
	return (size);
}

int				vm_inv_octets(unsigned int champion)
{
	char	c[4];
	int		i;

	i = 3;
	while (champion)
	{
		c[i] = champion & 0xff;
		champion >>= 8;
		--i;
	}
	return (*(int *)c);
}

static void			vm_verif_champ(char *chmp_info, t_champ *champ, int j)
{
	int				i;
	unsigned char	*c;
	header_t			*champion;

	c = (unsigned char*)chmp_info;
	i = COREWAR_EXEC_MAGIC;
	if (c[0] == (i >> 24) && c[1] == ((i >> 16) & 0xff)
			&& c[2] == ((i >> 8) & 0xff) && c[3] == (i & 0xff))
		;
	else
		exit(ft_int_error("magic exec invalide"));
	champion = (header_t *)&chmp_info[0];
	if (vm_inv_octets(champion->prog_size) != j - sizeof(header_t) ||
		j - sizeof(header_t) > CHAMP_MAX_SIZE)
	{
		ft_printf("sizes give %#x size find %#x\n",
							vm_inv_octets(champion->prog_size),
							j - sizeof(header_t));
		exit(ft_int_error("chamion size incorrect"));
	}
	ft_memcpy(champ->champ_name, chmp_info + 4, PROG_NAME_LENGTH);
}

static void			vm_create_champ(t_champ *champs, char *entry, int i,
		t_datas *datas)
{
	int					fd;
	int					j;
	char				buff[sizeof(header_t) + CHAMP_MAX_SIZE + 1];

	if (1 > (fd = open(entry, O_RDONLY)))
		exit(ft_int_error("Echec de lecture du champion"));
	if ((j = read(fd, &buff, sizeof(header_t) + CHAMP_MAX_SIZE + 1)) == -1
		|| j < (int)sizeof(header_t) + 1)
		exit(ft_int_error("Echec de read du champion"));
	buff[sizeof(header_t) + CHAMP_MAX_SIZE] = 0;
	vm_verif_champ(buff, &champs[i], j);
	ft_memcpy((void *)&champs[i], (void *)(buff + sizeof(header_t)),
			j - sizeof(header_t));
	champs[i].champ_nbr = -(i + 1);
	champs[i].champ_size = vm_size_champ(&champs[i], datas);
	if (close(fd) == -1)
		exit(ft_int_error("Echec de close du champion"));
	ft_memcpy(champs[i].champ_com, &buff[4 + PROG_NAME_LENGTH + 8],
														COMMENT_LENGTH);
}

int					vm_init_champ(t_champ *champs, int argc, char **argv,
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
		if (champ_nbr > MAX_PLAYERS)
			exit(ft_int_error("Too many champs"));
	}
	return (champ_nbr);
}
