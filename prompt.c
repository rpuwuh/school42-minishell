#include "minishell.h"

char	*mini_getprompt(t_prompt prompt)
{
	char	*user;
	char	*home;
	char	*prompt_full;

	user = get_user(prompt);
	prompt_full = ft_strjoin(user, "@minishell");
	free(user);
	home = get_home(prompt);
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