/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:46:24 by youjeon           #+#    #+#             */
/*   Updated: 2022/04/22 12:59:32 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_arg
{
	int		infile;
	int		outfile;
	char	**path;
	char	*cmd1;
	char	**cmd_arg1;
	char	*cmd2;
	char	**cmd_arg2;
	int		file_des[2];
	pid_t	pid;
}	t_arg;
