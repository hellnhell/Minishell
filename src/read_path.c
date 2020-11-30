/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:04:38 by emartin-          #+#    #+#             */
/*   Updated: 2020/11/30 21:44:26 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		not_command_error(t_tab *t)
{
	reset_std23(t);
	if (t->tokens[0][0] == '/')
		ft_printf("bash: %s : No such file or directory\n", t->tokens[0]);
	else
		ft_printf("bash: %s : command not found\n", t->tokens[0]);
	exit(127); 
}


int		check_path(t_tab *t, char **env)
{
	int		i;
	int		j;
	char	*aux;
	int		status;
	pid_t	pid;
	char	*buff;

	i = 0;
	j = -1;
	buff = malloc(1024);
	getcwd(buff, 1024);
	pid = fork();
	if (pid == 0)
	{	
	//if (!t->tokens[0])
	//	printf("errrrrrroorrrrr\n");
		while(t->path[i] != NULL)
		{ // Esto igual da error porque t->tokens[0] puede no existir
			if (t->tokens[0][0] == '.')
			{
				aux = ft_strjoin_sl2(buff, t->tokens[0]);
				j = execve(aux, t->tokens, t->env);
				free(aux);
				if (j >= 0)
					continue ;
			}
			else if (t->tokens[0][0] == '/')
			{
				j = execve(t->tokens[0], t->tokens, t->env);
				if (j >= 0)
					continue ;
			}
			aux = ft_strjoin_sl(t->path[i], t->tokens[0]);
			j = execve(aux, t->tokens, t->env);
			free(aux);
			i++;
		}
		if (j < 0)
			not_command_error(t);	
	}
	else
	{
		//system("leaks minishell");
		signal(SIGINT, ft_signal_c1);
		signal(SIGQUIT, ft_signal_quit);
		waitpid(pid, &status, 0);
		t->status = (status / 256);
	}
	free(buff);
	//printf("%d\n", status);
	return(0);
}


void	read_path(t_tab *t)
{
	int		i;
	char	*test;
	char	**path;

	i = 0;
	while (t->env[i])
	{
		// Esto puede petar si nos dan una variable de entorno que se llame "PATH="
		if (ft_strncmp("PATH=", t->env[i], 5) == 0)
		{
			/*if (t->z > 0 && t->path != NULL)
			{
				printf("hace un free aquí\n");
				free_matrix(t->path);
			}*/
			path = ft_split(&t->env[i][5], ':');
			ft_allocate_path(t, path);
			ft_cpy_path(t, path);
			free_matrix(path);
			break ;
		}
		i++;
	}
	if (!t->env[i])
	{
		t->path = malloc(sizeof(char *));
		t->path[0] = NULL;
	}
}
