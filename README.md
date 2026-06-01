_This project has been created as part of the 42 curriculum by marhuber and tzinaliy._

## Description
The point of minishell is to create an imitation of shell inside bash terminal. 
It will show a display prompt waiting for a new command

## Instructions
**run _`make`_**
**then _`./minishell`_**


#### Requirements

This program is written in C language and thus needs the **`gcc` compiler** and standard libraries to run

Display a prompt when waiting for a new command.
• Have a working history.<br>
• Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).<br>
• Use at most one global variable to indicate a received signal. Consider the
implications: this approach ensures that your signal handler will not access your
main data structures.<br>
• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).<br>
• Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.<br>
• Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for \$ (dollar sign). <br> <br>
We will implement the following redirections:<br>
◦ < should redirect input.<br>
◦ > should redirect output.<br>
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!<br>
◦ >> should redirect output in append mode.<br>
• Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.<br>
• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.<br>
• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.<br>
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.<br>
• In interactive mode:<br>
◦ ctrl-C displays a new prompt on a new line.<br>
◦ ctrl-D exits the shell.<br>
◦ ctrl-\ does nothing.<br><br>
 This shell will implement the following built-in commands:<br>
◦ echo with option -n<br>
◦ cd with only a relative or absolute path<br>
◦ pwd with no options<br>
◦ export with no options<br>
◦ unset with no options<br>
◦ env with no options or arguments<br>
◦ exit with no options<br>


## Resources

'man getline' <br>
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
https://en.wikipedia.org/wiki/Abstract_syntax_tree
https://en.wikipedia.org/wiki/Context-free_grammar
https://youtube.com/shorts/mi6DoxNEN6w?si=null
https://github.com/Swoorup/mysh
https://harm-smits.github.io/42docs/projects/minishell
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

Other resources <br>
https://gist.github.com/Alinaprotsyuk/3d58f8cd52eb03a11283d64beb0e083e




How "AI" was used? 
"Ai" was used as a tutor it performed theses tasks ; give advice on data structure choice;
comparison of data structures; code explanations etc.


