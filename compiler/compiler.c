/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:06:53 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/05 14:07:19 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

void error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(0);
}

char *get_output_path(char *name)
{
	char	*output_path;
	char	*tmp;

	tmp = ft_strrchr(name, '.');
	if (!tmp)
		return (ft_strdup(".cor"));
	*tmp = '\0';
	return (ft_strjoin_multi(FALSE, name, ".cor", NULL));
}

int main(int argc, char **argv)
{
	char	*output_path;
	int		fdin;
	int		fdout;
	header_t header;

	if (argc != 2)
		error("Usage : ./asm mychampion.s\n");
	fdin = open(argv[1], O_RDONLY);
	output_path = get_output_path(argv[1]);
	fdout = open(output_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	
	write_exec_magic(fdin, &header);
	write_comment(fdin, &header);
	write(fdout, &header, sizeof(header_t));
	//ft_putstr_fd("Hey !\n", fd);
	exit(0);
	return (0);
}