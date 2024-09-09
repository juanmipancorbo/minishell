#include "../include/minishell.h"

// inicar estructuras 2 t_red una in otra out. Y asignar a la
// estructura t_cmd


void set_file_descriptor(t_cmd *cmd, char *path, t_tkn_type type)
{
	(void)cmd;
	(void)path;
	if (type == RD_IN)
	{	
		t_red *new_node;
		
		new_node = malloc(sizeof(t_red));
		if(!new_node)
			manage_error(MALLOC_E);
		new_node->name = path;
		new_node->fd =  open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
		// agregar en lista cmd->in_rd
		printf("tipo:%d\n",RD_IN);
	}
	if (type == RD_IN)
	{	
		t_red *new_node;
		
		new_node = malloc(sizeof(t_red));
		if(!new_node)
			manage_error(MALLOC_E);
		new_node->name = path;
		new_node->fd =  open(path, O_RDWR | O_CREAT | O_APPEND, 0777);;
		
		printf("tipo:%d\n",RD_IN);
	}

}