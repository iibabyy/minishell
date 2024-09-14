/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 04:01:00 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 04:01:01 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../../includes/minishell.h"
# include "../lexing/lexing.h"

char	*list_files(char *str, char **input);
bool	is_valid_name(char *name, char *original, char **input);

#endif