#include "../include/minishell.h"

void dup_env_variables(t_general *data, char **env)
{
    int i;
    char **new_env;

    i = 0;
    while(env[i++]);
    new_env = malloc(sizeof(char *) * i);
    if (!new_env)
        manage_error(MALLOC_E, data);
    i = 0;
    while(env[i])
    {
        new_env[i] = ft_strdup(env[i]);
        if(!new_env[i])
            manage_error(MALLOC_E,data);
        i++;
    }
    new_env[i] = NULL; 
    data->env_var = new_env;
    return ;
}