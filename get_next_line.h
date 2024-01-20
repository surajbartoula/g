/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 03:38:19 by sbartoul          #+#    #+#             */
/*   Updated: 2024/01/21 03:38:22 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

int				found_newline(t_list *list);
t_list			*find_last_node(t_list *list);
void			copy_str(t_list *list, char *str);
int				len_to_newline(t_list *list);
void			dealloc(t_list **list, t_list *clean_node, char *str);

char			*get_next_line(int fd);
void			ft_newlist(t_list **list, int fd);
void			ft_addback(t_list **list, char *str);
void			polish_list(t_list **list);

#endif
