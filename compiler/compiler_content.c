/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:10:32 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/21 19:10:36 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"


// Découper en 3 - 4 fonction
void		compiler_compile_line(
	char *line, t_instruct *inst)
{
	char	*str;
	char	*str2;
	int		i;
	int		y;
	char	*opcode;
	char	**splited;
	t_op	opecode_config;
	int		tmp;
	int		endlabel;
	char	*arg;

	str = ft_strtrim(line);
	i = 0;
	while (ft_strchr(OPCODE_CHARS, str[i]))
		i++;
	opcode = ft_strsub(str, 0, i);
	str2 = ft_strtrim(str + i);
	opecode_config = get_config(opcode);
	ft_memdel((void**)&opcode);
	if (opecode_config.op_code == 0)
		return ;
	inst->opcode = opecode_config.op_code;
	inst->arg_nbrs = opecode_config.nb_arg;
	i = 0;
	ft_memdel((void**)&str);
	if ((str = ft_strchr(str2, COMMENT_CHAR)))
		*str = 0;
	y = 0;
	splited = ft_strsplit(str2, SEPARATOR_CHAR);
	ft_memdel((void**)&str2);
	while (y < opecode_config.nb_arg)
	{
		tmp = 0;
		arg = ft_strtrim(splited[y]);
		inst->args[y][0] = get_argtype(arg, opecode_config.tab_arg[y]);
		if (inst->args[y][0] == T_REG)
			inst->args[y][1] = 1;
		else if (inst->args[y][0] == T_IND || inst->args[y][0] == T_LABIND)
			inst->args[y][1] = 2;
		else
			inst->args[y][1] = (opecode_config.nbr_octet_dir) ? 2 : 4;
		if (opecode_config.have_bytearg)
		{
			inst->argcode = inst->argcode << 2;
			if (inst->args[y][0] == T_DIR || inst->args[y][0] == T_LABDIR)
				inst->argcode = inst->argcode | 2;
			if (inst->args[y][0] == T_REG)
				inst->argcode = inst->argcode | 1;
			if (inst->args[y][0] == T_IND || inst->args[y][0] == T_LABIND)
				inst->argcode = inst->argcode | 3;
		}
		if (inst->args[y][0] > T_LAB)
			inst->args_labels[y] = extract_str(arg);
		if (inst->args[y][0] == T_DIR)
			tmp = extract_int(arg);
		if (inst->args[y][0] == T_REG)
			tmp = extract_int(arg);
		if (inst->args[y][0] == T_IND)
			tmp = extract_int(arg);
		ft_memdel((void**)&arg);
		ft_memmove(inst->args[y] + 2, &tmp, inst->args[y][1]);
		y++;
	}
	y = (y == 0) ? 1 : y;
	if (splited[y] != 0)
		error("Too many arguments.\n");
	i = y;
	while (i)
	{
		i--;
		ft_memdel((void**)&splited[i]);
	}
	ft_memdel((void**)&splited);
	while (y < 4)
	{
		inst->argcode = inst->argcode << 2;
		y++;
	}
	inst->size = inst->args[0][1] + inst->args[1][1] + inst->args[2][1];
	inst->size++;
	if (inst->argcode)
		inst->size++;
}

t_instruct		*compiler_compile(int fdin)
{
	char		*line;
	char		*lineclr;
	int			endlabel;
	char		*instruct;
	t_instruct	*inst;
	t_instruct	*inst_first;

	inst_first = NULL;
	while (ft_gnl(fdin, &line))
	{
		if (!(*line) || *line == COMMENT_CHAR)
		{
			ft_memdel((void**)&line);
			continue ;
		}
		lineclr = ft_strtrim(line);
		ft_memdel((void**)&line);
		if (!*lineclr || *lineclr == COMMENT_CHAR)
		{
			ft_memdel((void**)&lineclr);
			continue;
		}
		if (!(inst = (ft_memalloc(sizeof(t_instruct)))))
			error("Malloc error\n");
		endlabel = compiler_compile_get_label(lineclr);
		if (endlabel != -1)
			inst->label_name = ft_strsub(lineclr, 0, endlabel);
		line = (endlabel != -1) ? lineclr + endlabel + 1 : lineclr;
		instruct = ft_strtrim(line);
		ft_memdel((void**)&lineclr);
		line = NULL;
		if (*instruct)
			compiler_compile_line(instruct, inst);
		ft_memdel((void**)&instruct);
		instructs_add(&inst_first, inst);
	}
	ft_memdel((void**)&line);
	hydrate_labels(inst_first);
	print_instruts(inst_first);
	return (inst_first);
}
