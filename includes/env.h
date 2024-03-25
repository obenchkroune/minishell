#ifndef ENV_H

# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*get_env(char *key);
char	**env_tab(t_env *env);
t_env	*set_env(char *key, char *value);
char	**env_tab(t_env *env);
void	free_env(t_env *env);

#endif