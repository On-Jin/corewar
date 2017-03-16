/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_copy_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 05:15:52 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/16 23:59:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process		*vm_copy_process(t_datas *datas, t_process *process, int PC)
{
	t_process		*new;
	t_process		*tmp;

	new = vm_create_process(datas, process->champion);
	tmp = new->next;
	ft_memmove((void *)new, (void *)process, sizeof(process->reg));
	new->next = tmp;
	new->PC = PC;
	new->live = 1;
	new->carry = process->carry;
	return (new);
}
