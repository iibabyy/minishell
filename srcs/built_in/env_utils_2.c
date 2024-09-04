/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 02:13:15 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/04 02:38:20 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

char	*ft_getenv(char *var)
{
	t_env_var	*env;

	env = get_env_struct(var);
	if (env == NULL)
		return (NULL);
	return (env->value);
}
