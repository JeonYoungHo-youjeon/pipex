/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:41:15 by youjeon           #+#    #+#             */
/*   Updated: 2022/04/22 12:59:51 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"



size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	if (len == 0)
	{
		return (src_len);
	}
	while (i < len - 1 && *src)
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = '\0';
	return (src_len);
}

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

char	*ft_strdup(const char *s)
{
	char	*new_mem;
	int		size;
	int		i;

	new_mem = NULL;
	size = ft_strlen(s);
	i = 0;
	new_mem = malloc(size + 1);
	if (!(new_mem))
		return (NULL);
	while (s[i])
	{
		new_mem[i] = s[i];
		i++;
	}
	new_mem[i] = '\0';
	return (new_mem);
}

static size_t	get_word_cnt(char const *str, char c)
{
	size_t	count;
	int		chker;

	count = 0;
	chker = 1;
	while (*str != '\0' && *str == c)
		str++;
	while (*str)
	{
		if (chker == 1 && *str != c)
		{
			count++;
			chker = 0;
		}
		if (*str == c)
			chker = 1;
		str++;
	}
	return (count);
}

static void	*is_free(char **str, int str_index)
{
	int	i;

	i = 0;
	while (i < str_index)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	**set_worddup(char const *s, char c, char **mem)
{
	size_t	word_length;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		word_length = 0;
		while (s[word_length] && s[word_length] != c)
			word_length++;
		mem[i] = (char *)malloc(sizeof(char) * (word_length + 1));
		if (!(mem[i]))
			return (is_free(mem, i));
		ft_strlcpy(mem[i], s, word_length + 1);
		s = s + word_length;
		i++;
	}
	mem[i] = NULL;
	return (mem);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**new_mem;

	new_mem = NULL;
	if (!s)
		return (NULL);
	word_count = get_word_cnt(s, c);
	new_mem = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!(new_mem))
		return (NULL);
	new_mem = set_worddup(s, c, new_mem);
	return (new_mem);
}

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

int	print_std_error(char *message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}

void	exit_perror(char *message)
{	
	perror(message);
	exit(1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_mem;
	size_t	s1_len;
	size_t	s2_len;

	new_mem = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_mem = malloc(s1_len + s2_len + 1);
	if (!(new_mem))
		return (NULL);
	ft_strlcpy(new_mem, s1, s1_len + 1);
	ft_strlcpy(new_mem + s1_len, s2, s2_len + 1);
	return (new_mem);
}

char	**get_path_envp(char *envp[])
{
	char	*path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = *envp + 5;
	printf("%s\n", path);
	return (ft_split(path, ':'));
}

char	*get_cmd_argv(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	path_cmd = ft_strjoin("/", cmd);
	fd = 0;
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

int	main(int ac, char *av[], char *envp[])
{
	//fd를 담아둘 구조체를 하나 선언한다.
	t_arg	arg;

	//argc는 무조건 5개로 고정되어있으니 해당 부분 에러처리 먼저 해준다.
	if (ac != 5)
		print_std_error("argument error");
	
	//infile 과 outfile을 open한다. open이 성공이 아니면(return이 -1 일때) 에러처리 해준다.
	arg.infile = open(av[1], O_RDONLY);
	if (arg.infile == -1)
		exit_perror("infile error");
	arg.outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (arg.infile == -1)
		exit_perror("outfile error");
	
	// 환경변수에서 PATH를 찾아서 PATH= 이후의 글자를 ft_split 으로 : 로 나눠서 저장한다.
	arg.path = get_path_envp(envp);

	// command를 가져온 다음 실행가능한 PATH를 확인한다. 
	arg.cmd_arg1 = ft_split(av[2], ' ');
	arg.cmd_arg2 = ft_split(av[3], ' ');
	if (arg.cmd_arg1 == NULL || arg.cmd_arg2 == NULL)
		print_std_error("cmd missing error");
	arg.cmd1 = get_cmd_argv(arg.path, arg.cmd_arg1[0]);
	arg.cmd2 = get_cmd_argv(arg.path, arg.cmd_arg2[0]);
	if (arg.cmd1 == NULL || arg.cmd2 == NULL)
		print_std_error("path or cmd error");
	printf("%s, %s \n", arg.cmd1, arg.cmd2);
	
}