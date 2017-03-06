/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 06:32:43 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/06 06:32:46 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** Includes
*/

# include "op.h"

/*
** MACROS
*/

/*
** Structures
*/

typedef struct		s_champ
{
	char			champ[CHAMP_MAX_SIZE]
}					t_champ;

typedef struct		s_vm
{
	char		arene[MEM_SIZE];
}					t_vm;

/*
** Prototypes
*/

#endif
