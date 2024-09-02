#include "../include/minishell.h"

void manage_error(char *msg, t_general *data)
{
    printf("%s\n", msg);
    (void)data;
    exit(EXIT_FAILURE);
}