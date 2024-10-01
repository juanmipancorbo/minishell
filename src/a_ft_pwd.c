#include "../include/minishell.h"

int	ft_pwd(t_cmd *cmd, t_utils *utils)
{	
	char *pwd;

	(void)cmd;
	pwd =  expand_var("PWD", utils->env_var);
	write(1, pwd, ft_strlen(pwd));
	write(1,"\n",1);
	free(pwd);
	return (EXIT_SUCCESS);
}
