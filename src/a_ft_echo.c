#include "../include/minishell.h"

int	ft_echo(t_cmd *cmd, t_utils *utils)
{
	(void)utils;
	write(1, cmd->args[0], ft_strlen(cmd->args[0]));
	return (EXIT_SUCCESS);
}
