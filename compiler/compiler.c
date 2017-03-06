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

#include "../includes/op.h"
#include "../includes/libft/libft.h"

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

void	write_exec_magic(int fd, header_t *header)
{
	int nbr;
	int revnbr;
	int i;
	int size;

	i = 3;
	nbr = COREWAR_EXEC_MAGIC;
	revnbr = 0;
	while (i >= 0)
	{
		((char*)(&revnbr))[i] = ((char*)(&nbr))[0];
		nbr = nbr >> 8;
		i--;
	}
	//write(fd, &revnbr, 4);
	header->magic = revnbr;
}

void	write_comment(int fdin, header_t *header)
{
	char	*line;
	char	*str;
	t_bool 	have_comment;
	t_bool	have_name;
	int 	len;

	have_comment = FALSE;
	have_name = FALSE;
	while (ft_gnl(fdin, &line))
	{
		if (*line == '\0' || ft_strcmp(line, ".") == 0)
			continue;
		else if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0 && !have_comment)
		{
			have_name = TRUE;
			str = ft_strtrim(line + ft_strlen(NAME_CMD_STRING));
			len = ft_strlen(str);
			if (*str != '"')
				error("Name don't start by '\"'\n");
			if (str[len - 1] != '"')
				error("Name don't end by '\"'\n");
			ft_printf("Hey : %s\n", str);
			if (len > PROG_NAME_LENGTH)
				error("Name too long");
			ft_bzero(&(header->prog_name), PROG_NAME_LENGTH + 1);
			ft_memcpy(&(header->prog_name), str + 1, len - 2);
			free(str);
			if (have_comment && have_name)
				break;
		}
		else if (ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0 && !have_comment)
		{
			have_comment = TRUE;
			str = ft_strtrim(line + ft_strlen(COMMENT_CMD_STRING));
			len = ft_strlen(str);
			if (*str != '"')
				error("Name don't start by '\"'\n");
			if (str[len - 1] != '"')
				error("Name don't end by '\"'\n");
			ft_printf("Hey : %s\n", str);
			if (len > COMMENT_LENGTH)
				error("Name too long");
			ft_bzero(&(header->comment), COMMENT_LENGTH + 1);
			ft_memcpy(&(header->comment), str + 1, len - 2);
			free(str);
			if (have_comment && have_name)
				break;
		}
		else
			error("Error in name/description.\n");
	}
	if (!have_comment || !have_name)
		error("Missing comment or name.\n");
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