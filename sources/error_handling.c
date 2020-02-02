/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:40:37 by merras            #+#    #+#             */
/*   Updated: 2019/10/27 15:46:15 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcline.h"

char	*ft_strerror(int err)
{
	if (err == N_TRM || err == N_TTY)
		return (err == N_TRM ? N_TRM_T : N_TTY_T);
	if (err == A_TRM || err == S_TRM)
		return (err == A_TRM ? A_TRM_T : S_TRM_T);
	return (NULL);
}

int		ft_perror(char *command, char *arg, int err)
{
	if (command)
		ft_putstr_fd(command, 2);
	ft_putstr_fd(ft_strerror(err), 2);
	if (arg)
		ft_putendl_fd(arg, 2);
	else
		ft_putchar_fd('\n', 2);
	return (err);
}