_This project has been created as part of the 42 curriculum by marhuber and tzinaliy._

## Description
The point of minishell is to create an imitation of shell inside bash terminal. 
It will show a display prompt waiting for a new command

## Instructions
**run _`make`_**<br>
**then _`./minishell`_**<br>

## Tests & Usefull commands

`printenv`<br>


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
&nbsp;	◦ < should redirect input.<br>
&nbsp;	◦ > should redirect output.<br>
&nbsp;	◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!<br>
&nbsp;	◦ >> should redirect output in append mode.<br>
• Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.<br>
• Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.<br>
• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.<br>
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.<br>
• In interactive mode:<br>
&nbsp;	◦ ctrl-C displays a new prompt on a new line.<br>
&nbsp;	◦ ctrl-D exits the shell.<br>
&nbsp;	◦ ctrl-\ does nothing.<br><br>
This shell will implement the following built-in commands:<br>
&nbsp;	◦ echo with option -n<br>
&nbsp;	◦ cd with only a relative or absolute path<br>
&nbsp;	◦ pwd with no options<br>
&nbsp;	◦ export with no options<br>
&nbsp;	◦ unset with no options<br>
&nbsp;	◦ env with no options or arguments<br>
&nbsp;	◦ exit with no options<br>


## Resources

`man getline` <br>
`man history` <br>
`man signal` <br>
`man sigaction` <br>
`man sigemptyset` <br>
`man signal` <br>
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218<br>
https://en.wikipedia.org/wiki/Abstract_syntax_tree<br>
https://en.wikipedia.org/wiki/Context-free_grammar<br>
https://youtube.com/shorts/mi6DoxNEN6w?si=null<br>
https://github.com/Swoorup/mysh<br>
https://harm-smits.github.io/42docs/projects/minishell<br>
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf<br>
https://dev.to/elipie/intro-to-parsing-lexing-3g01<br>


Other resources <br>
https://gist.github.com/Alinaprotsyuk/3d58f8cd52eb03a11283d64beb0e083e
https://stackoverflow.com/questions/12902627/whats-the-difference-between-stdout-and-stdout-fileno
https://www.youtube.com/watch?v=HosPml1qkrg

## Contribution guidelines
To add/contribute new functionality (obviously there is almost no point to contribute otherwise) you create a new branch and add this new functionality to main by mergining your branch.


How "AI" was used? 
"Ai" was used as a tutor it performed theses tasks ; give advice on data structure choice;
comparison of data structures; code explanations etc.


