/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:22:13 by dmillan           #+#    #+#             */
/*   Updated: 2022/09/03 19:39:56 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_append_free_secondstr(char *s1, char *s2)
{
	char	*res;

	res = ft_append(s1, s2);
	free (s2);
	return (res);
}

static char	*ft_get_home(t_env_v	**env)
{
	char	*pwd;
	char	*home;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = 0;
	if (ft_env_get_value(*env, "HOME"))
		home = ft_strdup(ft_env_get_value(*env, "HOME"));
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		tmp = pwd;
		pwd = ft_append("~", pwd + ft_strlen(home));
		free (tmp);
	}
	if (home)
		free(home);
	home = 0;
	pwd = ft_append_free_secondstr(BLUE, pwd);
	pwd = ft_strjoin(pwd, " ");
	pwd = ft_append_free_secondstr(" ", pwd);
	pwd = ft_strjoin(pwd, RESETCOLOR);
	return (pwd);
}

static char	*ft_get_user(t_env_v	**env)
{
	char	*user;

	user = NULL;
	user = ft_env_get_value(*env, "USER");
	if (!user)
		user = ft_strdup("guest");
	user = ft_append(BLUE, user);
	return (user);
}

char	*ft_get_prompt(t_env_v	**env)
{
	char	*user;
	char	*home;
	char	*prompt_full;

	user = ft_get_user(env);
	prompt_full = ft_append(user, "@minishell");
	free(user);
	user = 0;
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
