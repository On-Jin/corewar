/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_show_arene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 09:42:01 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/10 21:37:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

typedef struct	s_curs_win
{
	WINDOW		*win;
	int			width;
	int			height;
}				t_curs_win;

typedef struct 	s_draw
{
	t_curs_win	win;

	char		buff[MEM_SIZE * 4];
	int			index;
	int			min;
	int			max;
	int			count;
	int			in_champ;
	int			cur_champ;
	int			size_champ;
	int			save_pros;
}				t_draw;

void	size_draw_champ(t_datas *datas, t_draw *d);
void	find_pc_pros(t_datas *datas, t_vm *arene, t_draw *d);

void		vm_show_arene_start(t_datas *datas, int large_size)
{
	int		i;

	i = 1;
	large_size = large_size * 3;
	while (i <= large_size)
	{
		waddch(datas->win, '*');
		++i;
	}
	waddstr(datas->win, "\n| ");
}

void		ft_putbuffer_pros(t_datas *datas, t_vm *arene, t_draw *d, char *str)
{
	int i;

	i = 0;
	wattron(datas->win, A_REVERSE);
	waddch(datas->win, str[i]);
	i++;
	waddch(datas->win, str[i]);
	i++;
	wattroff(datas->win, A_REVERSE);
	find_pc_pros(datas, arene, d);
}

int			ft_square_root(int square)
{
	int		i;

	i = 1;
	while (i < square)
	{
		if (i * i == square)
			return (i);
		if (i * i > square)
			return (i - 1);
		++i;
	}
	return (0);
}

int			ft_gcd(int nbr)
{
	int		i;

	if (nbr < 1)
		return (-1);
	i = ft_square_root(nbr);
	while (nbr % i)
		--i;
	return (i);
}

void		vm_show_arene_element(t_datas *datas, t_vm *arene, t_draw *d,  char elem)
{
	char		line[3];

	line[2] = 0;
	line[1] = (unsigned char)elem % 16;
	line[0] = ((unsigned char)elem / 16) % 16;
	line[0] += (line[0] >= 10) ? ('a' - 10) : ('0');
	line[1] += (line[1] >= 10) ? ('a' - 10) : ('0');
	if (d->count == datas->start[d->cur_champ])
	{
		d->in_champ = 1;
		wattron(datas->win, COLOR_PAIR(d->cur_champ + 1));
	}
	if (d->count == d->size_champ + datas->start[d->cur_champ])
 	{
		d->cur_champ++;
		size_draw_champ(datas, d);
		d->in_champ = 0;
		wattroff(datas->win, COLOR_PAIR(d->cur_champ));
	}
	if (d->count == d->save_pros)
		ft_putbuffer_pros(datas, arene, d, line);
	else
	{
		waddch(datas->win, line[0]);
		waddch(datas->win, line[1]);
	}
	d->count += 1;
	waddch(datas->win, ' ');
}


void		init_draw(t_draw *d)
{
	ft_bzero((void *)d->buff, MEM_SIZE * 4);
	d->win.width = 64 * 3 + 2;
	d->win.height = 64 + 2;
	d->index = 0;
	d->min = MEM_SIZE * 8;
	d->max = 0;
	d->count = 0;
	d->in_champ = 0;
	d->cur_champ = 0;
	d->size_champ = 0;
	d->save_pros = 0;
}

void		find_pc_pros(t_datas *datas, t_vm *arene, t_draw *d)
{
	t_process *pros;
if (arene)
	;
	d->min = MEM_SIZE * 8;
	pros = datas->begin_process;
	while (pros)
	{
		if (pros->PC < d->min && pros->PC > d->max)
		{
			d->min = pros->PC;
			d->save_pros = pros->PC;
		}
		pros = pros->next;
	}
	if (d->save_pros >= 0)
		d->max = d->save_pros;
}

void	size_draw_champ(t_datas *datas, t_draw *d)
{
	d->size_champ = (datas->size_champ[d->cur_champ]);
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wrefresh(local_win);
	delwin(local_win);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
//	box(local_win, 0 , 0);
	wrefresh(local_win);
	return local_win;
}

void        vm_show_arene(t_datas *datas, t_vm *arene)
{
	t_draw	d;
	int		i;
	int		j;
	char	*line;
	init_draw(&d);

	initscr();
	start_color();
	init_pair(0, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	noecho();
	datas->win = create_newwin(64 + 2, 64 * 3 + 4, 0, 0);
	line = arene->arene;
	size_draw_champ(datas, &d);
	find_pc_pros(datas, arene, &d);
	i = 0;
	j = ft_gcd(MEM_SIZE); //racine carree;

	line = (char *)arene->arene;
	vm_show_arene_start(datas, j);
	while (i < MEM_SIZE)
	{
		vm_show_arene_element(datas, arene, &d, line[i]);
		++i;
		if (i % j == 0 && i < MEM_SIZE)
			waddstr(datas->win, "\n| ");
	}
	destroy_win(datas->win);
	usleep(10000);
	endwin();
}
