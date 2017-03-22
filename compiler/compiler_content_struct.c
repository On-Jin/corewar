#include "compiler.h"

void		print_instruts(t_instruct *instructs)
{
	int		i;
	int		y;
	void	*val;

	while (instructs)
	{
		i = 0;
		ft_printf("Label : \"%s\"\nSize : %i\nCompile :\n%#0hhx ",
			instructs->label_name, instructs->size, instructs->opcode);
		ft_printf("Forced argcode = %x\n", instructs->argcode);
		if (instructs->argcode)
		{
			ft_printf("%#0hhx ", instructs->argcode);
		}
		while (i < instructs->arg_nbrs)
		{
			y = 0;
			val = &(instructs->args[i][2]);
			while (y < instructs->args[i][1])
			{
				ft_printf("%#0hhx ",
					((char *)val)[instructs->args[i][1] - 1 - y]);
				y++;
			}
			i++;
			ft_printf(", ");
		}
		ft_printf("\n\n");
		instructs = instructs->next;
	}
}

void			instructs_add(t_instruct **instructs_list, t_instruct *instruct)
{
	t_instruct	*current;

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

size_t			get_instruct_size(t_instruct *current)
{
	size_t		size;

	size = 0;
	while (current)
	{
		size += current->size;
		current = current->next;
	}
	return (size);
}
