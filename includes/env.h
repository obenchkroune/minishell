#ifndef ENV_H

# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

char	*get_env(char *key);
void	free_env(t_env *env);

#endif