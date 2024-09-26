#include "../include/minishell.h"

int ft_pwd(t_cmd *cmd, t_utils *utils)
{
	printf("%s\n", cmd->args[1]);
	printf("%s\n", utils->env_var[2]);
	printf("pwd\n");
	return (EXIT_SUCCESS);
}