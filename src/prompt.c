/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:22:13 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/09 00:36:39 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_get_home(t_env_v	**env)
{
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = ft_env_get_value(*env, "HOME");
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
	free(home);
	pwd = ft_strjoin(BLUE, pwd);
	pwd = ft_strjoin(pwd, " ");
	pwd = ft_strjoin(" ", pwd);
	pwd = ft_strjoin(pwd, RESETCOLOR);
	return (pwd);
}

static char	*ft_get_user(t_env_v	**env)
{
	char	*user;
	char	*temp;

	user = NULL;
	temp = NULL;
	user = ft_env_get_value(*env, "HOME");
	if (!user)
		user = ft_strjoin(NULL, "guest");
	temp = ft_strjoin(NULL, BLUE);
	temp = ft_strjoin(temp, user);
	free(user);
	return (temp);
}

char	*ft_get_prompt(t_env_v	**env)
{
	char	*user;
	char	*home;
	char	*prompt_full;

	user = ft_get_user(env);
	prompt_full = ft_strjoin(user, "@minishell");
	free(user);
	home = ft_get_home(env);
	prompt_full = ft_strjoin(prompt_full, home);
	free(home);
	if (!g_status || g_status == -1)
		prompt_full = ft_strjoin(prompt_full, BLUE);
	else
		prompt_full = ft_strjoin(prompt_full, RED);
	prompt_full = ft_strjoin(prompt_full, "$ ");
	prompt_full = ft_strjoin(prompt_full, RESETCOLOR);
	return (prompt_full);
}
