#include "../include/minishell.h"

// forma funcion built_in
// int nombre(t_cmd *cmd, t_utils *utils)
int	(*indetyfy_buitin(char *str))(t_cmd *, t_utils *)
{
	int i;
	
	i= 0;
	static void	*built_in[7][2] = {
	{"cd", ft_cd},
	{"echo", ft_echo},
	{"env", ft_env},
	{"exit", ft_exit},
	{"export", ft_export},
	{"pwd", ft_pwd},
	{"unset", ft_unset},
	};

	while ( i < 7)
	{
		if (!ft_strncmp(built_in[i][0], str, ft_strlen(built_in[i][0])))
			return (built_in[i][1]);
		i++;
	}
	return (NULL);
}
