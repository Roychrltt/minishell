### Minishell

A lightweight UNIX shell implementation inspired by bash.

## Overview

Minishell is a simplified shell designed to replicate essential behavior of bash, including command parsing, environment variable handling, pipelines, redirections, and built-in commands.

## Features
- Interactive prompt with command history
- Command execution via fork, execve, and related system calls
- Parsing with support for:
  - Quotes (``"`` and ``'``)
  - Pipes (``|``)
  - Redirections (``>``, ``>>``, ``<``, ``<<``)
- Built-in commands:
  - cd
  - echo
  - pwd
  - env
  - export
  - unset
  - exit
- Environment variable expansion
 Signal handling (ctrl-C, ctrl-D, ctrl-\)

## Compilation
``make``

``.minishell``

## Usage
When launched, Minishell displays a prompt and waits for user input:
```
minishell$ echo hello
hello
```

You can use pipelines and redirections:
```
minishell$ ls -l | grep .c > out.txt
```

Here-documents:
```
minishell$ cat << EOF
> hello
> EOF
hello
```

## Signal Behavior
- ``ctrl-C`` prints a new prompt
- ``ctrl-D`` exits the shell
- ``ctrl-/`` is ignored in interactive mode
