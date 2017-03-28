/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_print_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 13:45:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/28 15:33:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_print_end(char **line, int *fd, int *i)
{
	*i = 0;
	*fd = 0;
	*line = NULL;
}

static void	print_finish(t_datas *datas)
{
	char	*line;
	int		fd;
	int		i;

	init_print_end(&line, &fd, &i);
	werase(datas->nc.win);
	i = 0;
	fd = 0;
	line = NULL;
	fd = open("finish.art", O_RDONLY);
	while (ft_gnl(fd, &line) == 1)
	{
		if (line)
		{
			mvwprintw(datas->nc.win, 22 + i, 20, "%s", line);
			ft_strdel(&line);
		}
		i++;
	}
	wrefresh(datas->nc.win);
	while (getch() != 'q')
		usleep(50000);
	close(fd);
}

static void	print_winner(t_datas *datas, t_nc *nc)
{
	char	*line;
	int		fd;
	int		i;
	char	*winner;

	init_print_end(&line, &fd, &i);
	if (datas->lives->last_live)
		winner = datas->begin_champ[vm_champ_number_to_position(
				datas->lives->last_live, datas->begin_champ)].champ_name;
	else
		winner = datas->begin_champ[datas->player_nbr - 1].champ_name;
	fd = open("crown.art", O_RDONLY);
	while (ft_gnl(fd, &line) == 1)
	{
		if (line)
		{
			mvwprintw(datas->nc.inf, 35 + i, 8, "%s", line);
			ft_strdel(&line);
		}
		i++;
	}
	mvwprintw(nc->inf, 36 + i, 35 - (ft_strlen(winner) / 2), "%s", winner);
	wrefresh(datas->nc.inf);
	close(fd);
}

void		ncurses_print_end(t_datas *datas)
{
	print_winner(datas, &datas->nc);
	print_finish(datas);
}
