/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 19:32:51 by nazurmen          #+#    #+#             */
/*   Updated: 2020/11/17 19:37:09 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_echo(char **args)
{
	int		i;
	int		flag;

	write(2, "natural\n", 8);
	flag = 0;
	i = 0;
	if (args[i] && ft_strncmp("-n", args[i], 2) == 0)
	{
		i++;
		flag++;
	}
	while (args[i])
	{
		//printf("i----%i\nargs-----%s\n",i, args[i]);
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[++i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
