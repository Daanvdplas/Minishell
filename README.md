# Minishell
Rebuilding a simple shell program. 

This project was built by [Daan van Der Plas](https://github.com/Daanvdplas) and [Rutger Cappendijk](https://github.com/rutgercap)

## Learning goals

- Parsing input into an abstract syntax tree

- Building and maintaining a large application in a team

- Extensive knowledge of the workings of bash

- Managing forked processes and pipes

- Applying test driven development with the unity tester

### How to run

GNU readline library is required to run this. Correct path to readline must be included in the makefile.

*brew installation:*

```console

brew install readline

```

Then run

```console

brew info readline

```
![compiler path](https://user-images.githubusercontent.com/2053650/150352713-fc5d9da7-046f-46dc-93ff-593e330235fc.png "Compiler path")

Add these to the makefile

![Adjust this](https://user-images.githubusercontent.com/2053650/150352709-ebf59ce0-e609-44da-9351-1c9ffdd1b445.png "Adjust this in makefile")

To run minishell:

```console

make run

```

### Builtin functionality

- Does not interpret unclosed quotes or special characters like \ or ;

- Has a working history

- Searches and launches the right executable (based on PATH)

- Ignores interpretation of string

- Supports the redirections: <, <<, >, >>

- Supports pipes

- Environment variables, expanded through $

- The signals: ctrl-C, ctrl-D and ctrl-\

- Has the following builtin functions:

	- echo with option -n
	- cd with relative or absolute path
	- pwd
	- export
	- unset
	- env
	- exit

#### Sources

Build linux parser:

https://blog.devgenius.io/lets-build-a-linux-shell-part-i-954c95911501

Bash prompts:

https://wiki.archlinux.org/title/Bash/Prompt_customization

Redirects:

https://www.gnu.org/software/bash/manual/html_node/Redirections.html

Bash parser:
https://mywiki.wooledge.org/BashParser
