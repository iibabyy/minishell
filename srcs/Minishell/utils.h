/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:36:24 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/13 04:00:48 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_UTILS_H
# define MSH_UTILS_H

# include "../../includes/minishell.h"
# include "../exec/exec.h"
# include "../lexing/lexing.h"
# include "../parsing/parsing.h"

char		*get_line(void);
int			exec(t_command *command);
char		*type_to_str(int type);
void		print_command(t_command *command);
char		*operator_type_to_str(int type);
void		printTree(t_command *command, int depth, int isRight, int *branch);
t_command	*last_command(t_command *current);
void		print_AST(t_command *command);
void		open_pipes_redirect(t_command *node);
bool		is_only_space(char *str);
void		minishell(void);

#endif