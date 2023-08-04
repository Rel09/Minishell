/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:25:08 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/04 01:52:21 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	convert_exit(void)
{
}

/*free what needs to be freed in here when an error occors*/
//	unlink_path(NULL);
// yavais ca entre get_env & temp_env, commented
void	clean_static_memory(void)
{
	rl_clear_history();
	save_std(CLOSE_IN | CLOSE_OUT);
	//need to clean env
}

static void	exit_process_argument(char *arg)
{
	if (is_str_int(arg))
	{
		g_last_result = ft_atoi(arg);
	}
	else
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required", 2);
		g_last_result = 255;
	}
}

/*recreation of exit as a buitin for minishell*/
/*closes the minishell program and free current input used to call it*/
void	ms_exit(t_input *input)
{
	//ft_putstr_fd("exit\n", 2);
	if (!input || get_array_size(input->commands) == 1)
	{
		clean_static_memory();
		free_input(input);
		exit(g_last_result);
	}
	if (get_array_size(input->commands) > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		g_last_result = EXIT_FAILURE;
		return ;
	}
	exit_process_argument(input->commands[1]);
	clean_static_memory();
	free_input(input);
	exit(g_last_result);
}
