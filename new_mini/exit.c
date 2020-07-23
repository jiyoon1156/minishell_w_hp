/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:36:45 by jhur              #+#    #+#             */
/*   Updated: 2020/07/23 14:36:46 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(char **info)
{
    if (ft_cnt(info) > 2)
        ft_putstr_fd("too many arguments\n", 2);
    else
        exit(0);
}
