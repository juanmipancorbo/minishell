#include "../include/minishell.h"

// inicar estructuras 2 t_red una in otra out. Y asignar a la
// estructura t_cmd

static void set_rdin_fd(t_cmd *cmd, char *path)
{
	int fd;

	
	fd = open(path, O_RDWR);
	add_fdNode_back(&cmd->in_rd, create_fd_node(path,fd));
}

static void set_herdoc_fd(t_cmd *cmd, char *path)
{
	int fd;

	fd = open(path, O_RDWR);
	add_fdNode_back(&cmd->in_rd, create_fd_node(path,fd));
	// falta terminar //
}

static void set_rdout_fd(t_cmd *cmd, char *path)
{
	int fd;

	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	add_fdNode_back(&cmd->out_rd, create_fd_node(path,fd));
}

static void set_append_fd(t_cmd *cmd, char *path)
{
	int fd;

	fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0777);
	add_fdNode_back(&cmd->out_rd, create_fd_node(path,fd));
}



void set_file_descriptor(t_cmd *cmd, char *path, t_tkn_type type)
{
	void (*set_fd[4])(t_cmd *cmd, char *path);
	
	set_fd[0] = set_rdin_fd;
	set_fd[1] = set_rdout_fd;
	set_fd[2] = set_append_fd;
	set_fd[3] = set_herdoc_fd;
	set_fd[type-2](cmd, path);
}