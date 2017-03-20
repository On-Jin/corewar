/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 09:32:30 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/20 17:58:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

//# include "corewar.h"

/*
** Libft
*/

int			ft_int_error(const char *line);
void		ft_void_error(char *line);
char		*ft_itoa_base_unsigned_max(uintmax_t n, int base, char a);
int			ft_gcd(int nbr);
int			ft_square_root(int square);

/*
** Fonctions
*/
void		vm_put_nbr_in_arene(int number, int adress, char *arene, int size);
int			vm_verif_datas(t_datas *datas, t_process *process);
int			vm_op_jump(t_datas *datas, t_process *process, unsigned char size);
void		vm_verif_macro(void);
int			vm_create_flags(char **argv, int argc, int *flag);
int			vm_init_champ(t_champ *champs, int argc, char **argv, t_datas *datas);

int			vm_ocp_size(char ocp, int nb_arg, int op_flag);
int			vm_havent_ocp(int op_code);
int			vm_have_ocp(int op_code);


t_process	*vm_create_process(t_datas *datas, int nbr_champ);
t_process	*vm_copy_process(t_datas *datas, t_process *process, int PC);
void		vm_destroy_process(t_process *process, t_datas *datas);
void		vm_innit_to_0(t_datas *datas, t_champ *champs,
						t_lives *lives);
int			vm_do_cycles(t_datas *datas, void (**exec)(t_datas *, t_process *));
int			vm_init_process(t_datas *datas);

void		start_op_code(t_datas *datas, t_process *pros, int op_code);

void		vm_champ_process(t_datas *datas, int argc, char **argv);
int			vm_champ_number_to_position(int champ_num, t_champ *champ_tab);
int			vm_champ_position_to_number(int champ_pos, t_champ *champ_tab);

int			vm_recup_process_reg(t_process *process, char *arene, int adresse, int *result);
int			vm_recup_all_process(t_process *process, char *arene, int flag);
int			vm_verif_i_code(char code, char a, char b, char c);
int			vm_recup_indirect_num(t_process *process, char *arene, int adresse);
int			vm_recup_arena_num(int size, char *arena, int PC);

void		vm_op_0_exec(t_datas *datas, t_process *process);
void		vm_op_1_exec(t_datas *datas, t_process *process);
void		vm_op_2_exec(t_datas *datas, t_process *process);
void		vm_op_3_exec(t_datas *datas, t_process *process);
void		vm_op_4_exec(t_datas *datas, t_process *process);
void		vm_op_5_exec(t_datas *datas, t_process *process);
void		vm_op_6_exec(t_datas *datas, t_process *process);
void		vm_op_7_exec(t_datas *datas, t_process *process);
void		vm_op_8_exec(t_datas *datas, t_process *process);
void		vm_op_9_exec(t_datas *datas, t_process *process);
void		vm_op_10_exec(t_datas *datas, t_process *process);
void		vm_op_11_exec(t_datas *datas, t_process *process);
void		vm_op_12_exec(t_datas *datas, t_process *process);
void		vm_op_13_exec(t_datas *datas, t_process *process);
void		vm_op_14_exec(t_datas *datas, t_process *process);
void		vm_op_15_exec(t_datas *datas, t_process *process);
void		vm_op_16_exec(t_datas *datas, t_process *process);
void		vm_op_0_create(t_datas *datas, t_process *process);
void		vm_op_1_create(t_datas *datas, t_process *process);
void		vm_op_2_create(t_datas *datas, t_process *process);
void		vm_op_3_create(t_datas *datas, t_process *process);
void		vm_op_4_create(t_datas *datas, t_process *process);
void		vm_op_5_create(t_datas *datas, t_process *process);
void		vm_op_6_create(t_datas *datas, t_process *process);
void		vm_op_7_create(t_datas *datas, t_process *process);
void		vm_op_8_create(t_datas *datas, t_process *process);
void		vm_op_9_create(t_datas *datas, t_process *process);
void		vm_op_10_create(t_datas *datas, t_process *process);
void		vm_op_11_create(t_datas *datas, t_process *process);
void		vm_op_12_create(t_datas *datas, t_process *process);
void		vm_op_13_create(t_datas *datas, t_process *process);
void		vm_op_14_create(t_datas *datas, t_process *process);
void		vm_op_15_create(t_datas *datas, t_process *process);
void		vm_op_16_create(t_datas *datas, t_process *process);
int			vm_add_valid(int adresse);

void		ncurses_init(t_datas *datas, int height, int width);
void		ncurses_end(t_datas *datas);
void		ncurses_loop_arene(t_datas *datas, t_draw *d);
void		ncurses_key(t_datas *datas);
void		ncurses_light(t_datas *datas);
void		ncurses_base(t_datas *datas);
void		ncurses_put_background(t_datas *datas, int PC, char champion, int size);
void		ncurses_find_pc(t_datas *datas, t_draw *d);


void		print_kirby(t_datas *datas, t_nc *nc);
void		print_cycle(t_datas *datas, t_nc *nc);
void		print_main_menu(t_datas *datas, t_nc *nc);
void		print_process(t_datas *datas, t_nc *nc);

#endif
