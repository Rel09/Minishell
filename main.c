/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 03:54:02 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/14 21:43:36 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(char	*input)
{
	t_input	*linkedlist;

	while (true)
	{
		intercept_signals();
		delete_heredocs_files();
		input = readline("Minishell > ");
		if (!input)
			ms_exit(NULL);
		add_history(input);
		if (!check_input(input))
			continue ;
		linkedlist = parse_input(input, NULL);
		if (!linkedlist)
			continue ;
		interactive_sighandlers();
		if (!heredoc_state()->cancel || !argschecker(linkedlist))
			command_handler(linkedlist);
		else
		{
			clean_mess(linkedlist);
			continue ;
		}
		free_input(linkedlist);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_env(env);
	save_std(SAVE_IN | SAVE_OUT);
	read_input(NULL);
	return (0);
}
