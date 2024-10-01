#include "../include/minishell.h"


int	ft_env(t_cmd *cmd, t_utils *utils)
{
	int i;

	i = 0;
	while(utils->env_var[i])
	{
		ft_putendl_fd(utils->env_var[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
