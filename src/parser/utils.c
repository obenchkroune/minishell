#include "minishell.h"

t_node	*create_node(t_node_type type, t_cmd *cmd, t_io *io)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		panic("malloc");
	node->type = type;
	node->cmd = cmd;
	node->io = io;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

t_cmd	*create_cmd(char *path, char **argv)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		panic("malloc");
	cmd->argv = argv;
	cmd->path = path;
	return (cmd);
}

t_io	*create_io(char *file, int fd, t_token_type type)
{
	t_io	*io;

	io = malloc(sizeof(t_io));
	if (!io)
		panic("malloc");
	io->fd = fd;
	io->file = file;
	io->type = type;
	io->next = NULL;
	io->prev = NULL;
	return (io);
}
