/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:51:15 by youjeon           #+#    #+#             */
/*   Updated: 2022/04/24 17:54:43 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (*str)
	{
		str++;
		length++;
	}
	return (length);
}
