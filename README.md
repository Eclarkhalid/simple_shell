Custom Shell
This is a custom shell implementation that replicates the basic functionalities of the Unix shell. The shell supports executing commands, handling environment variables, and searching for programs in the PATH.

Table of Contents
Resources
Learning Objectives
Description
Usage
Installation
Contributing
Authors
License
Resources
Read or watch:

Unix shell
Thompson shell
Ken Thompson
Everything you need to know to start coding your own shell concept page
Learning Objectives
At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

Understand the design and implementation of the original Unix operating system
Identify the author of the first version of the UNIX shell
Recognize Ken Thompson as the inventor of the B programming language, the direct predecessor to the C programming language
Describe who Ken Thompson is
Understand how a shell works
Define the concepts of pid and ppid
Manipulate the environment of the current process
Distinguish between a function and a system call
Create processes using fork
Identify the three prototypes of main
Explain how the shell uses the PATH to find programs
Execute another program with the execve system call
Suspend the execution of a process until one of its children terminates
Define EOF (end-of-file)
Description
This shell program provides a basic command-line interface where users can execute commands and interact with the system. It supports the execution of external programs found in the directories specified in the PATH environment variable. The shell provides functionality for command execution, process creation, environment variable manipulation, and more.

The shell displays a prompt ($) to indicate that it is ready to accept commands. Users can enter commands, and the shell will execute them by forking a child process and calling execve to replace the child process with the specified command. The shell will wait for the child process to complete before displaying the prompt again.

If a command is not found in the directories specified in the PATH, an appropriate error message will be displayed.
