/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <gnebie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 02:23:35 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/24 16:17:58 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct		s_fd
{
	int					fd_n;
	int					lastbuff;
	void				*tampon;
	struct s_fd			*next;
}					t_fd;

char				*ft_strncpy(char *dst, const char *src, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(char *str);
int					get_next_line(const int fd, char **line);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);

#endif
