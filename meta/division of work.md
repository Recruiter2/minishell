# Tasks to be distributed:

- **Quoting:** It handles single quotes `'`, preventing the interpretation of meta-characters within the quoted sequence. Double quotes `"` prevent the interpretation of meta-characters except for the dollar sign `$`.

- **Environment variables:** Minishell handles the expansion of environment variables (`$` followed by a sequence of characters) to their respective values.
- **Special variables:** It supports the special variable `$?` which expands to the exit status of the most recently executed foreground pipeline.








# tzinaliy

- **Signal handling:** Minishell handles signals such as `ctrl-C` (SIGINT), `ctrl-D` (EOF), and `ctrl-\` (SIGQUIT) according to the specified behavior in the subject.
/*partly done for main need to add signals for heredoc etc.
*/
- **Prompt display:** Minishell displays a prompt when waiting for a new command.
- **Command history:** It has a working history feature that allows navigating and reusing previous commands.
/*
add makefile; add libft; start structureing
add user prompt start the program with gnl getline;
add history
read history (this wasn't asked 🤡🤡 but I did it anyways 🤡🤡)*/



# marhuber

I really want to do these:

- **Command execution:** Minishell can search and launch the appropriate executable based on the PATH variable or using a relative or absolute path.
- **Redirections:** Minishell supports input `<`, output `>` and append output `>>` redirections. It also handles here documents `<<` where input is read until a line containing the specified delimiter.
- **Pipes:** It implements pipes `|` to connect the output of one command to the input of the next command in a pipeline.

Also a preference for

 - **Built-in commands:** It provides several built-in commands, including `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`, with their respective options and arguments.

 Happy to take also other tasks