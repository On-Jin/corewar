#include "compiler.h"

void	invert_byte(unsigned int *val)
{
	int i;
	unsigned int revnbr;
	unsigned int nbr;

	i = 3;
	nbr = *val;
	while (i >= 0)
	{
		((char*)(&revnbr))[i] = ((char*)(&nbr))[0];
		nbr = nbr >> 8;
		i--;
	}
	*val = revnbr;
}

void	write_exec_magic(header_t *header)
{
	header->magic = COREWAR_EXEC_MAGIC;
	invert_byte(&(header->magic));
}

void	write_comment(int fdin, header_t *header)
{
	char	*line;
	char	*linegnl;
	char	*str;
	t_bool 	have_comment;
	t_bool	have_name;
	int 	len;

	have_comment = FALSE;
	have_name = FALSE;
	linegnl = NULL;
	while (ft_gnl(fdin, &linegnl))
	{
		line = ft_strtrim(linegnl);
		ft_memdel((void**)&linegnl);
		if (!line)
			error("Can't read source file\n");
		
		if (*line == '\0' || *line == COMMENT_CHAR) // || ft_strcmp(line, ".") == 0 ???
		{
		}
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
			ft_memdel((void**)&str);
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
			ft_memdel((void**)&str);
			if (have_comment && have_name)
				break;
		}
		else
			error("Error in name/description.\n");
		ft_memdel((void**)&line);
	}
	ft_memdel((void**)&linegnl);
	if (!have_comment || !have_name)
		error("Missing comment or name.\n");
}