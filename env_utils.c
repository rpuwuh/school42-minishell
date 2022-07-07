/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmillan <dmillan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 00:03:20 by dmillan           #+#    #+#             */
/*   Updated: 2022/07/08 00:32:16 by dmillan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_env_v	*env_create(void)
{
	t_env_v	*env_empty;

	env_empty = malloc(sizeof(t_env_v));
	env_empty->name = NULL;
	env_empty->value = NULL;
	env_empty->next = NULL;
	return (env_empty);
}

void	env_add(t_env_v **env_v, char *name, char *value, int export)
{
	t_env_v	*env_new;

	env_new = env_init();
	env_new->name = name;
	env_new->value = value;
	env_new->export = export;
	ft_lstadd_back(env_v, env_new);
}

void	env_free(t_env_v **env_v)
{
	t_env_v	*env_next;

	while (*env_v != NULL)
	{
		env_next = (*env_v)->next;
		free((*env_v)->name);
		free((*env_v)->value);
		free(*env_v);
		*env_v = env_next;
	}
	*env_v = NULL;
}                                                                                                                                                                

void	env_replace(t_env_v **env_v, char *name, char *value, int export)
{
	t_env_v	*tmp;

	tmp = *env_v;
	if (tmp != NULL && ft_strcmp(tmp->name, name) == 0)
	{
		free(tmp->value);
		tmp->value = value;
		tmp->export = export;
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return ;
	free(tmp->value);
	free(name);
	tmp->value = value;
	tmp->export = export;
}