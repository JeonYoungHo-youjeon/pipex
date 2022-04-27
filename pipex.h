/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:46:24 by youjeon           #+#    #+#             */
/*   Updated: 2022/04/27 18:36:39 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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
	int		pipe_fds[2];
	pid_t	pid;
}	t_arg;

/* utiles */
size_t	ft_strlcpy(char *dst, const char *src, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	exit_perror(char *message, int code);
void	*ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t n, size_t size);

/* main */
char	**get_path_envp(char *envp[]);
char	*get_cmd_argv(char **path, char *cmd);
int		arg_parse(t_arg *arg, char *av[], char *envp[]);
void	control_fds(int closed, int std_in, int std_out);

#endif
