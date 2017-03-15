#include "compiler.h"


t_op    op_tab[17] =
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



t_op 	get_config(char *name)
{
	int i;

	i = 0;
	//ft_printf("name = '%s'\n", name);
	while(op_tab[i].name)
	{
		if (ft_strcmp(op_tab[i].name, name) == 0)
			return (op_tab[i]);
		i++;
	}
	ft_printf("'%s'\n", name);
	error("Unknow instruct\n");
	return (op_tab[0]);
}

int 		compiler_compile_get_label(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if(!ft_strchr(LABEL_CHARS, line[i]))
		{
			if (line[i] == LABEL_CHAR)
				return (i);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}


int		get_argtype(char *str, int conf)
{
	int type = T_UNK;
	if (*str == DIRECT_CHAR)
		type = T_DIR;
	if (*str == 'r') // registre
		type = T_REG;
	if (*str == '-' || ft_isdigit(*str)) // indirect
		type = T_IND;
	if (*str == DIRECT_CHAR && str[1] == LABEL_CHAR)
		type = T_LAB;
	if (type == T_UNK)
	{
		ft_printf("'%s'\n", str);
		error("Error : Unknow argtype.\n");
	}
	//ft_printf("\n%s\n%b\n%b\n%b\n", str, T_DIR, conf, (T_DIR & conf));
	if (type != T_LAB && (type & conf) == 0)
		error("Error : argtype\n");
	if (type == T_LAB && (T_DIR & conf) == 0)
		error("Error : argtype label\n");
	return type;
	return (0);
}


t_instruct *newinstruct()
{
	return (ft_memalloc(sizeof(t_instruct)));
}

char *extract_label_name(char *str)
{
	int end = 0;
	int start = 0;

	while (str[start] && !ft_strchr(LABEL_CHARS, str[start]))
		start++;
	end = start;
	while (str[end] && ft_strchr(LABEL_CHARS, str[start]))
		end++;
	//printf("======>%s start'%d' end'%d' et %s\n", str, start, end, ft_strsub(str, start, end - start) );
	return ft_strsub(str, start, end - start);
}

int   extract_direct(char *str)
{
	int start = 0;

	while (!(ft_isdigit(str[start]) || str[start] == '-'))
		start++;
	//ft_printf("-->%s\n", str + start);
	return (ft_atoi(str + start));
}

int  extract_registre(char *str)
{
	return extract_direct(str);
}

int extract_indirect(char *str)
{
	return extract_direct(str);
}

void	compiler_compile_line(char *line, t_instruct *inst)
{
	char *str;
	char *str2;
	int i;
	int y;
	char *opcode;
	char **splited;
	t_op opecode_config;
	int tmp;
	int endlabel;

	str = ft_strtrim(line);
	i = 0;
	ft_printf("=======>%s\n", str);
	while (ft_strchr(OPCODE_CHARS, str[i]))
		i++;
	opcode = ft_strsub(str, 0, i);
	str2 = ft_strtrim(str + i);
	opecode_config = get_config(opcode);
	inst->opcode = opecode_config.op_code;
	inst->arg_nbrs = opecode_config.nb_arg;
	y = 0;
	//ft_printf("=-->\"%s\"<--=\n", str2);
	splited = ft_strsplit(str2, SEPARATOR_CHAR);
	while (y < opecode_config.nb_arg)
	{
		tmp = 0;
		// opcode
		//ft_printf("%d…\n", y);
		inst->args[y][0] = get_argtype(splited[y], opecode_config.tab_arg[y]);
		if (inst->args[y][0] == REG_CODE)
			inst->args[y][1] = 1;
		else
			inst->args[y][1] = (opecode_config.nbr_octet_dir) ? 2 : 4;
		//  argcode
		if (opecode_config.have_bytearg)
		{
			inst->argcode = inst->argcode << 2;
			if (inst->args[y][0] == DIR_CODE || inst->args[y][0] == T_LAB)
				inst->argcode = inst->argcode | 2;
			if (inst->args[y][0] == REG_CODE)
				inst->argcode = inst->argcode | 1;
			if (inst->args[y][0] == IND_CODE)
				inst->argcode = inst->argcode | 3;
		}
		// Extract arg value
		if (inst->args[y][0] == T_LAB)
			inst->args_labels[y] = extract_label_name(splited[y]);
		if (inst->args[y][0] == DIR_CODE)
		{
			tmp = extract_direct(splited[y]);
		}
		if (inst->args[y][0] == REG_CODE)
			tmp = extract_registre(splited[y]);
		if (inst->args[y][0] == IND_CODE)
			tmp = extract_indirect(splited[y]);
		ft_memmove(inst->args[y] + 2, &tmp, inst->args[y][1]); 
		y++;
	}
	if (splited[y] != 0)
		error("Too many arguments.\n");
	while (y < 4)
	{
		inst->argcode = inst->argcode << 2;
		y++;
	}
	
	inst->size = inst->args[0][1] + inst->args[1][1] + inst->args[2][1];
	inst->size++; // opcode
	if (inst->argcode)
		inst->size++;
	free(str);
}

void		print_instruts(t_instruct *instructs)
{
	int i;
	int y;
	void *val;

	while (instructs)
	{
		i = 0;
		//ft_printf("Label : \"%s\"\nSize : %i\nCompile :\n%#0hhx ", instructs->label_name, instructs->size, instructs->opcode);
		if (instructs->argcode)
		{
			//ft_printf("%#0hhx ", instructs->argcode);
		}
		while (i <  instructs->arg_nbrs)
		{
			y = 0;
			val = &(instructs->args[i][2]);
			while (y < instructs->args[i][1])
			{
				//ft_printf("%#0hhx ", ((char *)val)[instructs->args[i][1] - 1 - y]);
				y++;
			}
			i++;
			//ft_printf(", ");
		}
		//ft_printf("\n\n");
		instructs = instructs->next;
	}
}


size_t			get_label_position(t_instruct *first, char *labelname)
{
	t_instruct *current;
	int 		count;
	t_bool		finded;

	current = first;
	finded = FALSE;
	count = 0;
	while (current)
	{
		//ft_printf("labelname >>> %s\n", current->label_name);
		if (ft_strcmp(current->label_name, labelname) == 0)
		{
			finded = TRUE;
			break ;
		}
		count += current->size;
		current = current->next;
	}
	//ft_printf("Label position : %i\n", count);
	if (!finded)
		error("Label not exist\n");
	return (count);
}

size_t			get_rquest_label_position(t_instruct *first, t_instruct *tofind, int argnbr)
{
	t_instruct *current;
	int 		count;
	t_bool		finded;

	current = first;
	finded = FALSE;
	count = 0;
	while (current)
	{
		if (current == tofind)
		{
			finded = TRUE;
			break ;
		}
		count += current->size;
		current = current->next;
	}
	//ft_printf("Label rquest position : %i\n", count);
	if (!finded)
		error("Unknow error\n");
	return (count);
}

size_t			get_relative(t_instruct *first, t_instruct *tofind, int argnbr, char *labelname)
{
	return (get_label_position(first, labelname) - get_rquest_label_position(first, tofind, argnbr));
}

void		hydrate_labels(t_instruct *first)
{
	t_instruct *current;
	int pos;
	int i;

	current = first;
	while (current)
	{
		i = 0;
		while (i < 3)
		{
			if (current->args_labels[i])
			{
				pos = get_relative(first, current, i, current->args_labels[i]);
				ft_memmove(current->args[i] + 2, &pos, current->args[i][1]); 
			}
			i++;
		}
		current = current->next;
	}
}

void		instructs_add(t_instruct **instructs_list, t_instruct *instruct)
{
	t_instruct *current;

	current = *instructs_list;
	if (!current)
	{
		*instructs_list = instruct;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = instruct;
}

size_t		get_instruct_size(t_instruct *current)
{
	size_t size;

	size = 0;
	while (current)
	{
		size += current->size;
		current = current->next;
	}
	return (size);
}

t_instruct *compiler_compile(int fdin)
{
	char *line;
	char *lineclr;
	int 	endlabel;
	char *instruct;
	t_instruct *inst;
	t_instruct *inst_first;

	inst_first = NULL;
	while(ft_gnl(fdin, &line))
	{
		if (!(*line))
			continue ;
		lineclr = ft_strtrim(line);
		free(line);
		if (!(inst = newinstruct()))
			error("Malloc error\n");
		endlabel = compiler_compile_get_label(lineclr);
		if (endlabel != -1)
			inst->label_name = ft_strsub(lineclr, 0, endlabel);
		line = (endlabel != -1) ? lineclr + endlabel + 1 : lineclr;
		instruct = ft_strtrim(line);
		if (instruct == NULL)
		{
			free(instruct);
			ft_gnl(fdin, &instruct);
		}
		compiler_compile_line(instruct, inst);
		instructs_add(&inst_first, inst);
		//error("end ! :)");
		// Ignorer les \n
		// Ignorer les #
	}
	hydrate_labels(inst_first);
	print_instruts(inst_first);
	return (inst_first);
	//return (unsigned int)get_instruct_size(inst_first);
	// Go write

}

/*
Syntaxes possible :
entry:
	st		r1, 6
*/
