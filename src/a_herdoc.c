#include "../include/minishell.h"

static void	read_loop(char *str)
{
	char	*line;
	int		fd;

	fd = open(HERDOC_F, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (fd < 0)
		manage_error(ERROR);
	while (1)
	{
		line = readline(">");
		if (!ft_strncmp(line, str, ft_strlen(str)))
		{
			free(line);
			return ;
		}
		if (write(fd, line, ft_strlen(line)) == -1)
			manage_error(ERROR);
		if (write(fd, "\n", 1) == -1)
			manage_error(ERROR);
		free(line);
	}
	close(fd);
}

void	set_herdoc_fd(t_cmd *cmd, char *path)
{
	int	fd;

	read_loop(path);
	fd = open(HERDOC_F, O_RDONLY);
	if (fd < 0)
		manage_error(ERROR);
	add_fdnode_back(&cmd->in_rd, create_fd_node(path, fd));
}
