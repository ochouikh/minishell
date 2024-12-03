# Minishell
this is a simple shell that can run commands and execute them.

## Tables of contents
- [Description](#description)
- [Installation](#installation)
- [Contributor](#contributor)


## Description
Minishell is a simple shell built in C.

It can handle the following built-in commands:
- `cd` : change directory
- `echo` : print a message with option -n to not print a newline
- `exit` : exit the shell
- `env` : print the environment variables
- `export` : set an environment variable
- `unset` : unset an environment variable
- `pwd` : print the current working directory

It has also the following features:
- run any other command available in the PATH
- redirections, pipes, and signals
-  && and || with parenthesis for priorities
- Wildcards * for the current working directory
- A history feature that allows you to navigate through the commands you have entered

## Installation
1. Clone the repository
```bash
git clone git@github.com:ochouikh/minishell.git
cd minishell
```
2. Compile the program
```bash
make
```
3. Run the program
```bash
./minishell
```

## Contributor
* [Mohssine El Aini](https://github.com/mel-aini)
