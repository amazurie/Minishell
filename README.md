# minishell

Minishell is a vital version of a real shell.
Can only use C
memory leaks = invalid project.

Required:
Command execution (e.g: "ls- la")
Builtins: echo, cd, setenv, unsetenv, env, exit
Manage the errors without using errno.

Allowed functions:
malloc, free, access, open, close, read, write, opendir, readdir, closedir, getcwd, chdir, stat, lstat, fstat, fork, execve, wait, waitpid, wait3, wait4, signal, kill, exit
Must have a Makefile to build the program
