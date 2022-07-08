#include "minishell.h"

static char	*get_home(t_env_v	**env)
{
	char	*temp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = mini_getenv("HOME", prompt.envp, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(temp);
	}
	free(home);
	home = ft_strjoin(BLUE, pwd);
	free(pwd);
	pwd = ft_strjoin(home, " ");
	free(home);
	home = ft_strjoin(" ", pwd);
	free(pwd);
	pwd = ft_strjoin(home, DEFAULT);
	free(home);
	return (pwd);
}

static char	*get_user(t_env_v	**env)
{
	char	**user;
	char	*temp;
	char	*temp2;

	user = NULL;
	temp2 = NULL;
	exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.envp);
	if (!user)
		user = ft_extend_matrix(user, "guest");
	if (!ft_strncmp(user[0], "root", 4))
		temp2 = ft_strjoin(NULL, RED);
	else if ((int)(user[0][0]) % 5 == 0)
		temp2 = ft_strjoin(NULL, CYAN);
	else if ((int)(user[0][0]) % 5 == 1)
		temp2 = ft_strjoin(NULL, GRAY);
	else if ((int)(user[0][0]) % 5 == 2)
		temp2 = ft_strjoin(NULL, GREEN);
	else if ((int)(user[0][0]) % 5 == 3)
		temp2 = ft_strjoin(NULL, MAGENTA);
	else
		temp2 = ft_strjoin(NULL, YELLOW);
	temp = ft_strjoin(temp2, *user);
	free(temp2);
	ft_free_matrix(&user);
	return (temp);
}

char	*get_prompt(t_env_v	**env)
{
	char	*user;
	char	*home;
	char	*prompt_full;

	user = get_user(t_env_v	**env);
	prompt_full = ft_strjoin(user, "@minishell");
	free(user);
	home = get_home(t_env_v	**env);
	prompt_full = ft_strjoin(prompt_full, home);
	free(home);
	if (!g_status || g_status == -1)
		prompt_full = ft_strjoin(prompt_full, BLUE);
	else
		prompt_full = ft_strjoin(prompt_full, RED);
	prompt_full = ft_strjoin(prompt_full, "$ ");
	prompt_full = ft_strjoin(prompt_full, DEFAULT);
	return (prompt_full);
}