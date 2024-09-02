#include "../include/minishell.h"

void   manage_error(char *msg, t_general *data)
{
    (void)data;
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}