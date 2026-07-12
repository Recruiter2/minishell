#include "../includes/minishell.h"

int is_redir(t_token_type t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT || t == T_REDIR_APPEND || t == T_HEREDOC);
}
