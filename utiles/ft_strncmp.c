/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:52:58 by youjeon           #+#    #+#             */
/*   Updated: 2022/04/24 17:54:46 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*ptr_s1 == *ptr_s2)
		{
			ptr_s1++;
			ptr_s2++;
			n--;
		}
		else
		{
			return (*ptr_s1 - *ptr_s2);
		}
		if (!(*ptr_s1) && !(*ptr_s2))
			break ;
	}
	return (0);
}
