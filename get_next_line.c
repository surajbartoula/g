/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 03:38:07 by sbartoul          #+#    #+#             */
/*   Updated: 2024/01/21 03:38:10 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*str;

	str = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!str || !clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		++i;
	while (last_node->content[i] && last_node->content[++i])
		str[k++] = last_node->content[i];
	str[k] = '\0';
	clean_node->content = str;
	clean_node->next = NULL;
	dealloc(list, clean_node, str);
}

void	ft_addback(t_list **list, char *str)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = str;
	new_node->next = NULL;
}

void	ft_newlist(t_list **list, int fd)
{
	int		count;
	char	*str;

	while (!found_newline(*list))
	{
		str = malloc(BUFFER_SIZE + 1);
		if (!str)
			return ;
		count = read(fd, str, BUFFER_SIZE);
		if (!count)
		{
			free(str);
			return ;
		}
		str[count] = '\0';
		ft_addback(list, str);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*string;
	int				str_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &string, 0) < 0)
		return (NULL);
	ft_newlist(&list, fd);
	if (!list)
		return (0);
	str_len = len_to_newline(list);
	string = malloc(str_len + 1);
	if (!string)
		return (0);
	copy_str(list, string);
	polish_list(&list);
	return (string);
}
