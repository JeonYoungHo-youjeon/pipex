/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:41:15 by youjeon           #+#    #+#             */
/*   Updated: 2022/04/27 18:29:21 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

char	**get_path_envp(char *envp[])
{
	char	*path;

	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (*envp == NULL)
		exit_perror("PATH error");
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*get_cmd_argv(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	fd = access(cmd, X_OK);
	if (fd != -1)
		return (cmd);
	path_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(path_cmd);
			return (tmp);
		}
		close(fd);
		free(tmp);
		i++;
	}
	free(path_cmd);
	return (NULL);
}

int	arg_parse(t_arg *arg, char *av[], char *envp[])
{
	int	result;

	result = 0;
	arg->infile = open(av[1], O_RDONLY);
	if (arg->infile == -1)
		perror("infile");
	arg->outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (arg->outfile == -1)
		exit_perror("outfile");
	arg->path = get_path_envp(envp);
	printf("testlast\n");
	arg->cmd_arg1 = ft_split(av[2], ' ');
	arg->cmd_arg2 = ft_split(av[3], ' ');
	arg->cmd1 = get_cmd_argv(arg->path, arg->cmd_arg1[0]);
	arg->cmd2 = get_cmd_argv(arg->path, arg->cmd_arg2[0]);
	if (arg->cmd1 == NULL || arg->cmd2 == NULL)
	{
		result = 127;
		perror("command not found");
	}
	return (result);
}

void	control_fds(int closed, int std_in, int std_out)
{
	close(closed);
	if (dup2(std_in, STDIN_FILENO) == -1)
		exit_perror("dup2 fail");
	if (dup2(std_out, STDOUT_FILENO) == -1)
		exit_perror("dup2 fail");
	close(std_in);
	close(std_out);
}

int	main(int ac, char *av[], char *envp[])
{
	t_arg	arg;
	int		result;

	if (ac != 5)
		exit_perror("argument error");
	result = arg_parse(&arg, av, envp);
	if (pipe(arg.pipe_fds) < 0)
		exit_perror("pipe error");
	arg.pid = fork();
	if (arg.pid == -1)
		exit_perror("fork error");
	else if (arg.pid == 0)
	{
		control_fds(arg.pipe_fds[0], arg.infile, arg.pipe_fds[1]);
		if (execve(arg.cmd1, arg.cmd_arg1, envp) == -1)
			exit_perror("execve fail");
	}
	else
	{
		control_fds(arg.pipe_fds[1], arg.pipe_fds[0], arg.outfile);
		waitpid(arg.pid, NULL, WNOHANG);
		if (execve(arg.cmd2, arg.cmd_arg2, envp) == -1)
			exit_perror("execve fail");
	}
	return (result);
}
