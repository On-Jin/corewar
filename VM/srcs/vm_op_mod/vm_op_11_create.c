/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_11_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:19:49 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/12 14:19:50 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_op_11_create(t_datas *datas, t_process *process)
{
		(void)datas;
	process->cycle = 25;
	process->instruction = 11;
}
