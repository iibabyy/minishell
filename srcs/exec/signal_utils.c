/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdembele <mdembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:48:18 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/06 18:47:38 by mdembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_code(int error_code, bool setter)
{
	static int	code = 0;

	if (setter == false)
		return (code);
	code = error_code;
	return (code);
}
