/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 04:16:24 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/07 04:16:25 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_verif_champ(char *chmp_info, t_champ *champ)
{
	int		i;
	unsigned char *c;

	c = (unsigned char*)chmp_info;

	i = COREWAR_EXEC_MAGIC;
	if (c[0] == (i >> 24) && c[1] == ((i >> 16) & 0xff)
	&& c[2] == ((i >> 8) & 0xff) && c[3] == (i & 0xff))
		ft_printf("test success\n");
	else
		exit(ft_int_error("magic exec invalide\n"));
	ft_memcpy(champ->champ_name, chmp_info + 4, PROG_NAME_LENGTH);
}

int			vm_create_champ(t_champ *champs, char *entry, int i)
{
	int		fd;
	char	buff[sizeof(header_t) + CHAMP_MAX_SIZE + 1];

	if (1 > (fd = open(entry, O_RDONLY)))
		exit (ft_int_error("Echec de lecture du champion"));
	if (read(fd, &buff, sizeof(header_t) + CHAMP_MAX_SIZE) == -1)
		exit (ft_int_error("Echec de read du champion"));
	buff[sizeof(header_t) + CHAMP_MAX_SIZE] = 0;
	vm_verif_champ(buff, &champs[i]);
	ft_memmove((void *)&champs[i], (void *)(buff + sizeof(header_t)), CHAMP_MAX_SIZE);
	champs[i].champ_nbr = i;
	if (close(fd) == -1)
		exit (ft_int_error("Echec de close du champion"));
	return (0);
}

int			vm_init_champ(t_champ *champs, int argc, char **argv, t_datas *datas)
{
	int		champ_nbr;
	int		i;

	i = datas->player_nbr;
	champ_nbr = 0;
	while (i < argc)
	{
		vm_create_champ(champs, argv[i], champ_nbr);
		++i;
		++champ_nbr;
	}
	return (champ_nbr);
}
