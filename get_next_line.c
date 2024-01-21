/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 03:38:07 by sbartoul          #+#    #+#             */
/*   Updated: 2024/01/22 01:57:26 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

void	fillstr_list(t_list **list, char *str)
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
		fillstr_list(list, str);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*string;
	int				str_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &string, 0) < 0)
		return (NULL);
	ft_newlist(list, fd);
	if (!list)
		return (0);
	str_len = len_to_newline(list);
	string = malloc(str_len + 1);
	if (!string)
		return (0);
	copy_str(list, string);
	ft_freelist(&list);
	return (string);
}
