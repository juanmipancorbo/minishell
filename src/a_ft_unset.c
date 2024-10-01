#include "../include/minishell.h"

int	ft_unset(t_cmd *cmd, t_utils *utils)
{
	(void)utils;
	printf("%s\n", cmd->args[1]);
	printf("%s\n", utils->env_var[2]);
	printf("unset\n");
	return (EXIT_SUCCESS);
}
