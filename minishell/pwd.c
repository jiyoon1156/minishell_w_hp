/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:52:07 by hpark             #+#    #+#             */
/*   Updated: 2020/07/23 13:52:08 by hpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int fd)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
	{
		ft_putstr_fd("PWD PATH ERROR", 2);
		return (1);
	}
	ft_putstr_fd(path, fd);
	ft_putstr_fd("\n", fd);
	if (fd != -1 && fd != 1)
		close(fd);
	return (0);
}
