# minishell

Minishell is a vital version of a real shell. <br />

#### Requirements (latest tested):
- GNU make (v3.81) <br />
- GCC (v4.2.1)


#### Project requirement:

Can only use C <br />
memory leaks = invalid project. <br />
Command execution (e.g: "ls -la") <br />
Builtins: echo, cd, setenv, unsetenv, env, exit <br />
Manage the errors without using errno.


#### Allowed functions:

malloc, free, access, open, close, read, write, opendir, readdir, closedir, getcwd, chdir, stat, lstat, fstat, fork, execve, wait, waitpid, wait3, wait4, signal, kill, exit <br />

Must have a Makefile to build the program
