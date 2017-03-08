#include "compiler.h"

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