#include "../include/minishell.h"

int	ft_cd(t_cmd *cmd, t_utils *utils)
{
	printf("%s\n", cmd->args[1]);
	printf("%s\n", utils->env_var[2]);
	printf("cd\n");
	return (EXIT_SUCCESS);
}
