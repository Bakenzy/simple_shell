# simple_shell
0x16. C - Simple Shell CGroup projectSyscall      
# Simple Shell Project

![Shell Logo](https://example.com/shell-logo.png)

Welcome to the Simple Shell project, a command-line interpreter built in C language. This project challenges you to implement a basic Unix shell with a range of features while adhering to strict coding guidelines and project requirements.

## Table of Contents

- [Introduction](#introduction)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Features](#features)
- [Builtin Commands](#builtin-commands)
- [Contributors](#contributors)
- [License](#license)

## Introduction

This Simple Shell project is a collaborative effort by Bakenne Farouq and Brian Mosagwe. The goal of this project is to create a minimalistic Unix-like command-line interpreter using the C programming language. The shell provides a command prompt where users can enter commands, which are then executed by the shell. It supports various features such as executing external programs, managing environment variables, handling redirection, and more.

## Getting Started

To compile the Simple Shell, make sure you have `gcc` installed on your system. Navigate to the project directory and execute the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell
```

## Usage

After compiling the shell, you can run it by executing the `simple_shell` binary:

```bash
./simple_shell
```

The shell will display a prompt where you can enter commands. You can run simple commands, execute programs, and use various built-in commands.

## Features

- Displays a prompt and waits for user input.
- Supports executing external programs.
- Handles simple command lines with or without arguments.
- Implements built-in commands like `exit`, `env`, `cd`, and more.
- Handles the `PATH` to find executable programs.
- Implements logical operators `&&` and `||`.
- Manages environment variables.
- Supports comments using `#`.
- Provides input from files for batch execution.

## Builtin Commands

- `exit`: Exits the shell.
- `env`: Prints the current environment.
- `cd [DIRECTORY]`: Changes the current directory.
- `alias [name[='value'] ...]`: Manages aliases.
- `setenv VARIABLE VALUE`: Initializes or modifies an environment variable.
- `unsetenv VARIABLE`: Removes an environment variable.

## Contributors

- Bakenne Farouq
- Brian Mosagwe

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).

---

For detailed project requirements and guidelines, please refer to the project's original documentation and resources.

