#include "../include/minishell.h"

bool	check_files(char *path)
{
	return (access(path, F_OK));
}

static void	delete_herdocf(void)
{
	if (check_files(HERDOC_F) == 0)
		unlink(HERDOC_F);
}

void	clean_exit(t_cmd *cmd)
{
	delete_herdocf();
	(void)cmd;
}
